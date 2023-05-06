#ifndef TFPF_MERSENNE_TWISTER_INCLUDE_MT19937_H_
#define TFPF_MERSENNE_TWISTER_INCLUDE_MT19937_H_

#include <inttypes.h>
#include <stddef.h>

struct mt19937_32_t
{
    uint32_t state[624];
    int index;
};
struct mt19937_64_t
{
    uint64_t state[312];
    int index;
};

#ifdef __cplusplus
extern "C"
{
#endif
void mt19937_seed32(uint32_t seed, struct mt19937_32_t *mt);
void mt19937_seed64(uint64_t seed, struct mt19937_64_t *mt);
uint32_t mt19937_rand32(struct mt19937_32_t *mt);
uint64_t mt19937_rand64(struct mt19937_64_t *mt);
uint32_t mt19937_uint32(uint32_t modulus, struct mt19937_32_t *mt);
uint64_t mt19937_uint64(uint64_t modulus, struct mt19937_64_t *mt);
double mt19937_real32(struct mt19937_32_t *mt);
double long mt19937_real64(struct mt19937_64_t *mt);
void mt19937_shuffle32(void *items, uint32_t num_of_items, size_t size_of_item, struct mt19937_32_t *mt);
#ifdef __cplusplus
}
#endif

// Macro which expands to its first argument. Used to emulate macros with
// default arguments. See below: wherever it is used, the end result is that it
// is replaced by the argument if provided, else `NULL`.
#define GET_OR_NULL(arg, ...) arg

#define mt19937_seed32(seed, ...) mt19937_seed32(seed, GET_OR_NULL(__VA_ARGS__ __VA_OPT__(,) NULL))
#define mt19937_seed64(seed, ...) mt19937_seed64(seed, GET_OR_NULL(__VA_ARGS__ __VA_OPT__(,) NULL))
#define mt19937_rand32(...) mt19937_rand32(GET_OR_NULL(__VA_ARGS__ __VA_OPT__(,) NULL))
#define mt19937_rand64(...) mt19937_rand64(GET_OR_NULL(__VA_ARGS__ __VA_OPT__(,) NULL))
#define mt19937_uint32(modulus, ...) mt19937_uint32(modulus, GET_OR_NULL(__VA_ARGS__ __VA_OPT__(,) NULL))
#define mt19937_uint64(modulus, ...) mt19937_uint64(modulus, GET_OR_NULL(__VA_ARGS__ __VA_OPT__(,) NULL))
#define mt19937_real32(...) mt19937_real32(GET_OR_NULL(__VA_ARGS__ __VA_OPT__(,) NULL))
#define mt19937_real64(...) mt19937_real64(GET_OR_NULL(__VA_ARGS__ __VA_OPT__(,) NULL))
#define mt19937_shuffle32(items, num_of_items, size_of_item, ...) mt19937_shuffle32(items, num_of_items, size_of_item, GET_OR_NULL(__VA_ARGS__ __VA_OPT__(,) NULL))

#endif  // TFPF_MERSENNE_TWISTER_INCLUDE_MT19937_H_
