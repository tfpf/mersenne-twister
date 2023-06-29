#ifndef TFPF_MERSENNE_TWISTER_INCLUDE_MT19937_H_
#define TFPF_MERSENNE_TWISTER_INCLUDE_MT19937_H_ "1.1.0"

// In a C++ program, only C++ headers (which may not place the types in the
// global namespace) should be included to avoid pollution.
#ifdef __cplusplus
#include <cinttypes>
#include <cstddef>
#define uint32_t std::uint32_t
#define uint64_t std::uint64_t
#define int32_t std::int32_t
#define int64_t std::int64_t
#define size_t std::size_t
#else
#include <inttypes.h>
#include <stddef.h>
#endif

#if !(defined UINT32_MAX && defined UINT64_MAX && defined INT32_MAX && defined INT64_MAX)
#error "This compiler does not support 32- and 64-bit unsigned and signed integers."
#endif

// Forward declarations.
struct mt19937_32_t;
struct mt19937_64_t;
#ifdef __cplusplus
extern "C"
{
#endif
uint32_t mt19937_seed32(uint32_t seed, struct mt19937_32_t *mt);
uint64_t mt19937_seed64(uint64_t seed, struct mt19937_64_t *mt);
uint32_t mt19937_init32(struct mt19937_32_t *mt);
uint64_t mt19937_init64(struct mt19937_64_t *mt);
uint32_t mt19937_rand32(struct mt19937_32_t *mt);
uint64_t mt19937_rand64(struct mt19937_64_t *mt);
uint32_t mt19937_uint32(uint32_t modulus, struct mt19937_32_t *mt);
uint64_t mt19937_uint64(uint64_t modulus, struct mt19937_64_t *mt);
int32_t mt19937_span32(int32_t left, int32_t right, struct mt19937_32_t *mt);
int64_t mt19937_span64(int64_t left, int64_t right, struct mt19937_64_t *mt);
double mt19937_real32(struct mt19937_32_t *mt);
double long mt19937_real64(struct mt19937_64_t *mt);
void mt19937_shuf32(void *items, uint32_t num_of_items, size_t size_of_item, struct mt19937_32_t *mt);
void mt19937_shuf64(void *items, uint64_t num_of_items, size_t size_of_item, struct mt19937_64_t *mt);
void mt19937_drop32(int long long count, struct mt19937_32_t *mt);
void mt19937_drop64(int long long count, struct mt19937_64_t *mt);
#ifdef __cplusplus
}
#endif

// Wrap all functions in a namespace using variadic templates.
#ifdef __cplusplus
namespace mt19937
{
    template<typename... T> uint32_t seed32(T... args) { return mt19937_seed32(args..., NULL); }
    template<typename... T> uint32_t init32(T... args) { return mt19937_init32(args..., NULL); }
    template<typename... T> uint32_t rand32(T... args) { return mt19937_rand32(args..., NULL); }
    template<typename... T> uint32_t uint32(T... args) { return mt19937_uint32(args..., NULL); }
    template<typename... T> int32_t  span32(T... args) { return mt19937_span32(args..., NULL); }
    template<typename... T> double   real32(T... args) { return mt19937_real32(args..., NULL); }
    template<typename... T> void     shuf32(T... args) {        mt19937_shuf32(args..., NULL); }
    template<typename... T> void     drop32(T... args) {        mt19937_drop32(args..., NULL); }

    template<typename... T> uint64_t seed64(T... args) { return mt19937_seed64(args..., NULL); }
    template<typename... T> uint64_t init64(T... args) { return mt19937_init64(args..., NULL); }
    template<typename... T> uint64_t rand64(T... args) { return mt19937_rand64(args..., NULL); }
    template<typename... T> uint64_t uint64(T... args) { return mt19937_uint64(args..., NULL); }
    template<typename... T> int64_t  span64(T... args) { return mt19937_span64(args..., NULL); }
    template<typename... T> double   real64(T... args) { return mt19937_real64(args..., NULL); }
    template<typename... T> void     shuf64(T... args) {        mt19937_shuf64(args..., NULL); }
    template<typename... T> void     drop64(T... args) {        mt19937_drop64(args..., NULL); }
};
#endif

// Object definitions.
struct mt19937_32_t
{
    uint32_t state[624];
    uint32_t value[624];
    int index;
#ifdef __cplusplus
    template<typename... T> uint32_t seed32(T... args) { return mt19937_seed32(args..., this); }
    template<typename... T> uint32_t init32(T... args) { return mt19937_init32(args..., this); }
    template<typename... T> uint32_t rand32(T... args) { return mt19937_rand32(args..., this); }
    template<typename... T> uint32_t uint32(T... args) { return mt19937_uint32(args..., this); }
    template<typename... T> int32_t  span32(T... args) { return mt19937_span32(args..., this); }
    template<typename... T> double   real32(T... args) { return mt19937_real32(args..., this); }
    template<typename... T> void     shuf32(T... args) {        mt19937_shuf32(args..., this); }
    template<typename... T> void     drop32(T... args) {        mt19937_drop32(args..., this); }
    mt19937_32_t(uint32_t seed=5489) { this->seed32(seed); }
    mt19937_32_t(std::nullptr_t _) { this->init32(); }
#endif
};
struct mt19937_64_t
{
    uint64_t state[312];
    uint64_t value[312];
    int index;
#ifdef __cplusplus
    template<typename... T> uint64_t seed64(T... args) { return mt19937_seed64(args..., this); }
    template<typename... T> uint64_t init64(T... args) { return mt19937_init64(args..., this); }
    template<typename... T> uint64_t rand64(T... args) { return mt19937_rand64(args..., this); }
    template<typename... T> uint64_t uint64(T... args) { return mt19937_uint64(args..., this); }
    template<typename... T> int64_t  span64(T... args) { return mt19937_span64(args..., this); }
    template<typename... T> double   real64(T... args) { return mt19937_real64(args..., this); }
    template<typename... T> void     shuf64(T... args) {        mt19937_shuf64(args..., this); }
    template<typename... T> void     drop64(T... args) {        mt19937_drop64(args..., this); }
    mt19937_64_t(uint64_t seed=5489) { this->seed64(seed); }
    mt19937_64_t(std::nullptr_t _) { this->init64(); }
#endif
};

#ifdef __cplusplus
#undef uint32_t
#undef uint64_t
#undef int32_t
#undef int64_t
#undef size_t
#endif

#endif  // TFPF_MERSENNE_TWISTER_INCLUDE_MT19937_H_
