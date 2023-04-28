```C
void mt19937_seed(uint32_t seed);
```
Seed 32-bit MT19937. If this function is not called, its initial state is the same as if it were seeded with 5489.
* `seed` 32-bit number. If this is 0, MT19937 will be seeded with the sum of the Unix time and the process ID.

```C
void mt19937_64_seed(uint64_t seed);
```
Seed 64-bit MT19937. If this function is not called, its initial state is the same as if it were seeded with 5489.
* `seed` 64-bit number. If this is 0, MT19937 will be seeded with the sum of the Unix time and the process ID.

```C
uint32_t mt19937_rand(void);
```
* → Pseudorandom 32-bit number.

```C
uint64_t mt19937_64_rand(void);
```
* → Pseudorandom 64-bit number.

```C
uint32_t mt19937_rand_integer(uint32_t modulus);
```
* `modulus` 32-bit number. Must not be 0.
* → Pseudorandom 32-bit number from 0 (inclusive) to `modulus` (exclusive).

```C
uint64_t mt19937_64_rand_integer(uint64_t modulus);
```
* `modulus` 64-bit number. Must not be 0.
* → Pseudorandom 64-bit number from 0 (inclusive) to `modulus` (exclusive).

```C
double mt19937_rand_real(void);
```
Generate a pseudorandom number in the unit interval using 32-bit MT19937.
* → Pseudorandom number from 0 (inclusive) to 1 (inclusive).

```C
double mt19937_64_rand_real(void);
```
Generate a pseudorandom number in the unit interval using 64-bit MT19937.
* → Pseudorandom number from 0 (inclusive) to 1 (inclusive).

```C
void mt19937_rand_shuffle(void *items, uint32_t num_of_items, size_t size_of_item);
```
Pseudorandomly shuffle an array in place. Uses 32-bit MT19937 internally.
* `items` Array to shuffle.
* `num_of_items` Number of elements in the array. Must not be 0.
* `size_of_item` Size of each element of the array in bytes.
