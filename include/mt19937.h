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

// Macro which expands to its first argument. Used to emulate macros with
// default arguments. See below: wherever it is used, the end result is that it
// is replaced by the argument if provided, else `NULL`.
#define GET_OR_NULL(arg, ...) arg

#define mt19937_seed(seed, ...)  \
mt19937_seed(seed, GET_OR_NULL(__VA_ARGS__ __VA_OPT__(,) NULL))
void mt19937_seed(uint32_t seed, struct mt19937_t *mt);

#define mt19937_64_seed(seed, ...)  \
mt19937_64_seed(seed, GET_OR_NULL(__VA_ARGS__ __VA_OPT__(,) NULL))
void mt19937_64_seed(uint64_t seed, struct mt19937_64_t *mt);

#define mt19937_rand(...)  \
mt19937_rand(GET_OR_NULL(__VA_ARGS__ __VA_OPT__(,) NULL))
uint32_t mt19937_rand(struct mt19937_t *mt);

#define mt19937_64_rand(...)  \
mt19937_64_rand(GET_OR_NULL(__VA_ARGS__ __VA_OPT__(,) NULL))
uint64_t mt19937_64_rand(struct mt19937_64_t *mt);

#define mt19937_rand_integer(modulus, ...)  \
mt19937_rand_integer(modulus, GET_OR_NULL(__VA_ARGS__ __VA_OPT__(,) NULL))
uint32_t mt19937_rand_integer(uint32_t modulus, struct mt19937_t *mt);

#define mt19937_64_rand_integer(modulus, ...)  \
mt19937_64_rand_integer(modulus, GET_OR_NULL(__VA_ARGS__ __VA_OPT__(,) NULL))
uint64_t mt19937_64_rand_integer(uint64_t modulus, struct mt19937_64_t *mt);

#define mt19937_rand_real(...)  \
mt19937_rand_real(GET_OR_NULL(__VA_ARGS__ __VA_OPT__(,) NULL))
double mt19937_rand_real(struct mt19937_t *mt);

#define mt19937_64_rand_real(...)  \
mt19937_64_rand_real(GET_OR_NULL(__VA_ARGS__ __VA_OPT__(,) NULL))
double mt19937_64_rand_real(struct mt19937_64_t *mt);

#define mt19937_rand_shuffle(items, num_of_items, size_of_item, ...)  \
mt19937_rand_shuffle(items, num_of_items, size_of_item, GET_OR_NULL(__VA_ARGS__ __VA_OPT__(,) NULL))
void mt19937_rand_shuffle(void *items, uint32_t num_of_items, size_t size_of_item, struct mt19937_t *mt);

#endif  // TFPF_MERSENNE_TWISTER_INCLUDE_MT19937_H_
