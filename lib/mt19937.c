#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "mt19937.h"

#define MT19937_STATE_LENGTH 624
#define MT19937_STATE_MIDDLE 397
#define MT19937_UPPER_MASK 0x80000000U
#define MT19937_LOWER_MASK 0x7FFFFFFFU
#define MT19937_TWIST_MASK 0x9908B0DFU
#define MT19937_MULTIPLIER 0x00010DCDU
#define MT19937_TEMPER_B 0x9D2C5680U
#define MT19937_TEMPER_C 0xEFC60000U
#define MT19937_TEMPER_D 0xFFFFFFFFU
#define MT19937_TEMPER_I 18
#define MT19937_TEMPER_S 7
#define MT19937_TEMPER_T 15
#define MT19937_TEMPER_U 11

static struct
{
    uint32_t state[MT19937_STATE_LENGTH];
    int index;
}
mt19937;

/******************************************************************************
 * Seed MT19937. This function must be called before any other function
 * included from this file.
 *
 * @param seed 32-bit number. If this is 0, MT19937 will be seeded with the
 *     sum of the Unix time and the process ID.
 *****************************************************************************/
void mt19937_seed(uint32_t seed)
{
    if(seed == 0)
    {
        seed = time(NULL) + getpid();
    }
    mt19937.state[0] = seed;
    for(int i = 1; i < MT19937_STATE_LENGTH; ++i)
    {
        // Overflow is okay. We only want the bottom 32 bits, and unsigned
        // overflow is defined behaviour.
        mt19937.state[i] = MT19937_MULTIPLIER * mt19937.state[i - 1];
    }
    mt19937.index = MT19937_STATE_LENGTH;
}

/******************************************************************************
 * Generate a pseudorandom number.
 *
 * @return Pseudorandom 32-bit number.
 *****************************************************************************/
uint32_t mt19937_rand(void)
{
    // Twist.
    if(mt19937.index == MT19937_STATE_LENGTH)
    {
        mt19937.index = 0;
        uint32_t twist[] = {0, MT19937_TWIST_MASK};
        for(int i = 0; i < MT19937_STATE_LENGTH - MT19937_STATE_MIDDLE; ++i)
        {
            uint32_t masked = (MT19937_UPPER_MASK & mt19937.state[i]) | (MT19937_LOWER_MASK & mt19937.state[i + 1]);
            uint32_t masked_twisted = (masked >> 1) ^ twist[masked & 1];
            mt19937.state[i] = mt19937.state[i + MT19937_STATE_MIDDLE] ^ masked_twisted;
        }
        for(int i = MT19937_STATE_LENGTH - MT19937_STATE_MIDDLE; i < MT19937_STATE_LENGTH - 1; ++i)
        {
            uint32_t masked = (MT19937_UPPER_MASK & mt19937.state[i]) | (MT19937_LOWER_MASK & mt19937.state[i + 1]);
            uint32_t masked_twisted = (masked >> 1) ^ twist[masked & 1];
            mt19937.state[i] = mt19937.state[i + MT19937_STATE_MIDDLE - MT19937_STATE_LENGTH] ^ masked_twisted;
        }
        uint32_t masked = (MT19937_UPPER_MASK & mt19937.state[MT19937_STATE_LENGTH - 1]) | (MT19937_LOWER_MASK & mt19937.state[0]);
        uint32_t masked_twisted = (masked >> 1) ^ twist[masked & 1];
        mt19937.state[MT19937_STATE_LENGTH - 1] = mt19937.state[MT19937_STATE_MIDDLE - 1] ^ masked_twisted;
    }

    // Generate.
    uint32_t curr = mt19937.state[mt19937.index++];
    curr ^= (curr >> MT19937_TEMPER_U) & MT19937_TEMPER_D;
    curr ^= (curr << MT19937_TEMPER_S) & MT19937_TEMPER_B;
    curr ^= (curr << MT19937_TEMPER_T) & MT19937_TEMPER_C;
    curr ^= curr >> MT19937_TEMPER_I;
    return curr;
}

/******************************************************************************
 * Test MT19937. The results of this implementation must match those of the one
 * given in the original paper.
 *
 * Makoto Matsumoto and Takuji Nishimura, "Mersenne Twister: A
 * 623-dimensionally Equidistributed Uniform Pseudo-random Number Generator",
 * in ACM Transactions on Modeling and Computer Simulation, vol. 8, no. 1,
 * pp. 3-30, January 1998, doi:10.1145/272991.272995.
 *
 * @return `true` if the results match, else `false`.
 *****************************************************************************/
bool mt19937_test(void)
{
    uint32_t const expected[][2] =
    {
        {    1, 3510405877}, {    2, 4290933890}, {    4,  564929546}, {    8,  268830360}, {   16, 1452005258},
        {   32,  675678546}, {   64, 1413475797}, {  128,  979144237}, {  256, 2950091998}, {  512, 3769042770},
        { 1024, 1198529401}, { 2048, 1984791300}, { 4096, 1074066123}, { 8192, 1445832134}, {16384, 2454186801}
    };
    mt19937_seed(4357);
    for(uint32_t i = 1, j = 0; i <= 16384; ++i)
    {
        uint32_t r = mt19937_rand();
        if(i == expected[j][0])
        {
            if(r != expected[j][1])
            {
                return false;
            }
            ++j;
        }
    }
    return true;
}

/******************************************************************************
 * Choose a pseudorandom residue of the given modulus.
 *
 * @param modulus 32-bit number. Must not be 0.
 *
 * @return Pseudorandom integer from 0 (inclusive) to `modulus` (exclusive).
 *****************************************************************************/
uint32_t mt19937_rand_integer(uint32_t modulus)
{
    uint32_t upper = 0xFFFFFFFFU - 0xFFFFFFFFU % modulus;
    uint32_t r;
    do
    {
        r = mt19937_rand();
    }
    while(r >= upper);
    return r % modulus;
}

/******************************************************************************
 * Choose a pseudorandom number in the unit interval.
 *
 * @return Pseudorandom real from 0 (inclusive) to 1 (inclusive), subject to
 *     the limitations of the return type.
 *****************************************************************************/
double mt19937_rand_real(void)
{
    return (double)mt19937_rand() / 0xFFFFFFFFU;
}

/******************************************************************************
 * Shuffle an array in place.
 *
 * @param items Array to shuffle.
 * @param items_length Number of elements in the array. Must not be 0.
 * @param item_size Size of each element of the array in bytes.
 *****************************************************************************/
void mt19937_rand_shuffle(void *items, uint32_t items_length, size_t item_size)
{
    char *temp = malloc(item_size);
    char *items_ = (char *)items;
    for(uint32_t i = items_length - 1; i > 0; --i)
    {
        uint32_t j = mt19937_rand_integer(i + 1);
        if(i != j)
        {
            char *items_i = items_ + i * item_size;
            char *items_j = items_ + j * item_size;
            memcpy(temp, items_i, item_size);
            memcpy(items_i, items_j, item_size);
            memcpy(items_j, temp, item_size);
        }
    }
    free(temp);
}
