#ifndef MERSENNE_TWISTER_SUDOKU_SOLVER_MT19937_H
#define MERSENNE_TWISTER_SUDOKU_SOLVER_MT19937_H

#include <inttypes.h>
#include <stdbool.h>

#define MT19937_STATE_LENGTH 624
#define MT19937_STATE_MIDDLE 397
#define MT19937_UPPER_MASK 0x80000000U
#define MT19937_LOWER_MASK 0x7FFFFFFFU

struct
{
    uint32_t state[MT19937_STATE_LENGTH];
    int index;
}
mt19937;

/******************************************************************************
 * Seed MT19937.
 *
 * @param seed 32-bit number. Must not be 0.
 *****************************************************************************/
void mt19937_seed(uint32_t seed)
{
    mt19937.state[0] = seed;
    for(int i = 1; i < MT19937_STATE_LENGTH; ++i)
    {
        // Overflow is okay. We only want the bottom 32 bits, and unsigned
        // overflow is defined behaviour.
        mt19937.state[i] = 69069U * mt19937.state[i - 1];
    }
    mt19937.index = MT19937_STATE_LENGTH;
}

/******************************************************************************
 * Generate a pseudorandom number using MT19937. Seed it using `mt19937_seed`
 * before calling this function.
 *
 * @return Pseudorandom 32-bit number.
 *****************************************************************************/
uint32_t mt19937_rand(void)
{
    // Twist.
    if(mt19937.index == MT19937_STATE_LENGTH)
    {
        mt19937.index = 0;
        uint32_t twist[] = {0, 0x9908B0DFU};
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
    curr ^= curr >> 11;
    curr ^= (curr << 7) & 0x9D2C5680U;
    curr ^= (curr << 15) & 0xEFC60000U;
    curr ^= curr >> 18;
    return curr;
}

/******************************************************************************
 * Test MT19937. The results of this implementation must match those of the one
 * given in the original paper.
 *
 * Makoto Matsumoto and Takuji Nishimura, "Mersenne twister: A
 * 623-dimensionally Equidistributed Uniform Pseudo-random Number Generator",
 * in ACM Transactions on Modeling and Computer Simulation, vol. 8, no. 1,
 * pp. 3-30, January 1998, doi:10.1145/272991.272995.
 *
 * @return `true` if the results match, else `false`.
 *****************************************************************************/
bool mt19937_test(void)
{
    uint32_t expected[][2] =
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

#endif // MERSENNE_TWISTER_SUDOKU_SOLVER_MT19937_H
