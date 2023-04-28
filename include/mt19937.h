#ifndef TFPF_MERSENNE_TWISTER_INCLUDE_MT19937_H_
#define TFPF_MERSENNE_TWISTER_INCLUDE_MT19937_H_

#include <inttypes.h>
#include <stddef.h>

struct mt19937_t
{
    uint32_t state[624];
    int index;
};
struct mt19937_64_t
{
    uint64_t state[312];
    int index;
};

void mt19937_seed(uint32_t seed);
void mt19937_64_seed(uint64_t seed);
uint32_t mt19937_rand(void);
uint64_t mt19937_64_rand(void);
uint32_t mt19937_rand_integer(uint32_t modulus);
uint64_t mt19937_64_rand_integer(uint64_t modulus);
double mt19937_rand_real(void);
double mt19937_64_rand_real(void);
void mt19937_rand_shuffle(void *items, uint32_t num_of_items, size_t size_of_item);

#endif  // TFPF_MERSENNE_TWISTER_INCLUDE_MT19937_H_
