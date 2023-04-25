#ifndef TFPF_MERSENNE_TWISTER_INCLUDE_MT19937_H_
#define TFPF_MERSENNE_TWISTER_INCLUDE_MT19937_H_

#include <inttypes.h>
#include <stddef.h>

/******************************************************************************
 * Seed 32-bit MT19937. If this function is not called, the initial state is
 * the same as if it were seeded with 5489.
 *
 * @param seed 32-bit number. If this is 0, MT19937 will be seeded with the sum
 *     of the Unix time and the process ID.
 *****************************************************************************/
void mt19937_seed(uint32_t seed);

/******************************************************************************
 * Seed 64-bit MT19937. If this function is not called, the initial state is
 * the same as if it were seeded with 5489.
 *
 * @param seed 64-bit number. If this is 0, MT19937 will be seeded with the sum
 *     of the Unix time and the process ID.
 *****************************************************************************/
void mt19937_64_seed(uint64_t seed);

/******************************************************************************
 * Generate a pseudorandom number.
 *
 * @return Pseudorandom 32-bit number.
 *****************************************************************************/
uint32_t mt19937_rand(void);

/******************************************************************************
 * Generate a pseudorandom number.
 *
 * @return Pseudorandom 64-bit number.
 *****************************************************************************/
uint64_t mt19937_64_rand(void);

/******************************************************************************
 * Choose a pseudorandom residue of the given modulus.
 *
 * @param modulus 32-bit number. Must not be 0.
 *
 * @return Pseudorandom integer from 0 (inclusive) to `modulus` (exclusive).
 *****************************************************************************/
uint32_t mt19937_rand_integer(uint32_t modulus);

/******************************************************************************
 * Choose a pseudorandom residue of the given modulus.
 *
 * @param modulus 64-bit number. Must not be 0.
 *
 * @return Pseudorandom integer from 0 (inclusive) to `modulus` (exclusive).
 *****************************************************************************/
uint64_t mt19937_64_rand_integer(uint64_t modulus);

/******************************************************************************
 * Choose a pseudorandom number in the unit interval using 32-bit MT19937.
 *
 * @return Pseudorandom real from 0 (inclusive) to 1 (inclusive), subject to
 *     the limitations of the return type.
 *****************************************************************************/
double mt19937_rand_real(void);

/******************************************************************************
 * Choose a pseudorandom number in the unit interval using 64-bit MT19937.
 *
 * @return Pseudorandom real from 0 (inclusive) to 1 (inclusive), subject to
 *     the limitations of the return type.
 *****************************************************************************/
double mt19937_64_rand_real(void);

/******************************************************************************
 * Shuffle an array in place.
 *
 * @param items Array to shuffle.
 * @param num_of_items Number of elements in the array. Must not be 0.
 * @param size_of_item Size of each element of the array in bytes.
 *****************************************************************************/
void mt19937_rand_shuffle(void *items, uint32_t num_of_items, size_t size_of_item);

#endif  // TFPF_MERSENNE_TWISTER_INCLUDE_MT19937_H_
