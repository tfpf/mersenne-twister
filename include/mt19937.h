#ifndef TFPF_MERSENNE_TWISTER_INCLUDE_MT19937_H_
#define TFPF_MERSENNE_TWISTER_INCLUDE_MT19937_H_ "0.0.1"

#include <inttypes.h>
#include <stddef.h>

struct mt19937_32_t
{
    uint32_t state[624];
    uint32_t value[624];
    int index;
};
struct mt19937_64_t
{
    uint64_t state[312];
    uint64_t value[312];
    int index;
};

#ifdef __cplusplus
extern "C"
{
#endif
void mt19937_seed32(uint32_t seed, struct mt19937_32_t *mt);
void mt19937_seed64(uint64_t seed, struct mt19937_64_t *mt);
void mt19937_init32(struct mt19937_32_t *mt);
void mt19937_init64(struct mt19937_64_t *mt);
uint32_t mt19937_rand32(struct mt19937_32_t *mt);
uint64_t mt19937_rand64(struct mt19937_64_t *mt);
uint32_t mt19937_uint32(uint32_t modulus, struct mt19937_32_t *mt);
uint64_t mt19937_uint64(uint64_t modulus, struct mt19937_64_t *mt);
int32_t mt19937_span32(int32_t left, int32_t right, struct mt19937_32_t *mt);
int64_t mt19937_span64(int64_t left, int64_t right, struct mt19937_64_t *mt);
double mt19937_real32(struct mt19937_32_t *mt);
double long mt19937_real64(struct mt19937_64_t *mt);
void mt19937_shuffle32(void *items, uint32_t num_of_items, size_t size_of_item, struct mt19937_32_t *mt);
void mt19937_shuffle64(void *items, uint64_t num_of_items, size_t size_of_item, struct mt19937_64_t *mt);
void mt19937_drop32(int long long count, struct mt19937_32_t *mt);
void mt19937_drop64(int long long count, struct mt19937_64_t *mt);
#ifdef __cplusplus
}
#endif

// If this macro is not defined, define a getter macro and use it to emulate
// macros with default arguments. (Wherever the getter macro is used below, the
// end result is that it is replaced with the first of the provided arguments
// if any, else `NULL`.) On the other hand, if it is defined, skip these macro
// definitions. (This will make error messages clearer, ensuring that the
// programmer remembers to pass the last argument to the above functions.)
// Needless to say, this macro is meant for development purposes, and not for
// end users of this library.
#ifndef TFPF_MERSENNE_TWISTER_INCLUDE_MT19937_H_SKIP_MACRO_DEFINITIONS
#define GET_OR_NULL(arg, ...) arg
#define mt19937_seed32(seed, ...) mt19937_seed32(seed, GET_OR_NULL(__VA_ARGS__ __VA_OPT__(,) NULL))
#define mt19937_seed64(seed, ...) mt19937_seed64(seed, GET_OR_NULL(__VA_ARGS__ __VA_OPT__(,) NULL))
#define mt19937_init32(...) mt19937_init32(GET_OR_NULL(__VA_ARGS__ __VA_OPT__(,) NULL))
#define mt19937_init64(...) mt19937_init64(GET_OR_NULL(__VA_ARGS__ __VA_OPT__(,) NULL))
#define mt19937_rand32(...) mt19937_rand32(GET_OR_NULL(__VA_ARGS__ __VA_OPT__(,) NULL))
#define mt19937_rand64(...) mt19937_rand64(GET_OR_NULL(__VA_ARGS__ __VA_OPT__(,) NULL))
#define mt19937_uint32(modulus, ...) mt19937_uint32(modulus, GET_OR_NULL(__VA_ARGS__ __VA_OPT__(,) NULL))
#define mt19937_uint64(modulus, ...) mt19937_uint64(modulus, GET_OR_NULL(__VA_ARGS__ __VA_OPT__(,) NULL))
#define mt19937_span32(left, right, ...) mt19937_span32(left, right, GET_OR_NULL(__VA_ARGS__ __VA_OPT__(,) NULL))
#define mt19937_span64(left, right, ...) mt19937_span64(left, right, GET_OR_NULL(__VA_ARGS__ __VA_OPT__(,) NULL))
#define mt19937_real32(...) mt19937_real32(GET_OR_NULL(__VA_ARGS__ __VA_OPT__(,) NULL))
#define mt19937_real64(...) mt19937_real64(GET_OR_NULL(__VA_ARGS__ __VA_OPT__(,) NULL))
#define mt19937_shuffle32(items, num_of_items, size_of_item, ...) mt19937_shuffle32(items, num_of_items, size_of_item, GET_OR_NULL(__VA_ARGS__ __VA_OPT__(,) NULL))
#define mt19937_shuffle64(items, num_of_items, size_of_item, ...) mt19937_shuffle64(items, num_of_items, size_of_item, GET_OR_NULL(__VA_ARGS__ __VA_OPT__(,) NULL))
#define mt19937_drop32(count, ...) mt19937_drop32(count, GET_OR_NULL(__VA_ARGS__ __VA_OPT__(,) NULL))
#define mt19937_drop64(count, ...) mt19937_drop64(count, GET_OR_NULL(__VA_ARGS__ __VA_OPT__(,) NULL))
#endif  // TFPF_MERSENNE_TWISTER_INCLUDE_MT19937_H_SKIP_MACRO_DEFINITIONS

#endif  // TFPF_MERSENNE_TWISTER_INCLUDE_MT19937_H_
