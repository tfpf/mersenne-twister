These are all macros, not functions. However, they are written to behave like functions, so I document them as if they
are functions.

In each of the following, `mt` is an optional argument, denoting the MT19937 object to use. If it is not provided, an
internal MT19937 object will be used instead.

---

```C
void mt19937_seed(uint32_t seed, struct mt19937_t *mt);
```
Seed 32-bit MT19937. If this function is not called, its initial state is the same as if it were seeded with 5489.
* `seed` 32-bit number. If this is 0, MT19937 will be seeded with the sum of the Unix time and the process ID.
* `mt` MT19937 object to seed.

```C
void mt19937_64_seed(uint64_t seed, struct mt19937_64_t *mt);
```
Seed 64-bit MT19937. If this function is not called, its initial state is the same as if it were seeded with 5489.
* `seed` 64-bit number. If this is 0, MT19937 will be seeded with the sum of the Unix time and the process ID.
* `mt` MT19937 object to seed.

---

```C
uint32_t mt19937_rand(struct mt19937_t *mt);
```
Generate a pseudorandom number.
* `mt` MT19937 object to use for generation.
* → Uniform pseudorandom 32-bit number.

```C
uint64_t mt19937_64_rand(struct mt19937_64_t *mt);
```
Generate a pseudorandom number.
* `mt` MT19937 object to use for generation.
* → Uniform pseudorandom 64-bit number.

---

```C
uint32_t mt19937_rand_integer(uint32_t modulus, struct mt19937_t *mt);
```
Generate a pseudorandom number.
* `modulus` 32-bit number. Must not be 0.
* `mt` MT19937 object to use for generation.
* → Uniform pseudorandom 32-bit number from 0 (inclusive) to `modulus` (exclusive).

```C
uint64_t mt19937_64_rand_integer(uint64_t modulus, struct mt19937_64_t *mt);
```
Generate a pseudorandom number.
* `modulus` 64-bit number. Must not be 0.
* `mt` MT19937 object to use for generation.
* → Uniform pseudorandom 64-bit number from 0 (inclusive) to `modulus` (exclusive).

---

```C
double mt19937_rand_real(struct mt19937_t *mt);
```
Generate a pseudorandom number.
* `mt` MT19937 object to use for generation.
* → Uniform pseudorandom number from 0 (inclusive) to 1 (inclusive).

```C
double mt19937_64_rand_real_(struct mt19937_64_t *mt);
```
Generate a pseudorandom number.
* `mt` MT19937 object to use for generation.
* → Uniform pseudorandom number from 0 (inclusive) to 1 (inclusive).

---

```C
void mt19937_rand_shuffle(void *items, uint32_t num_of_items, size_t size_of_item, struct mt19937_t *mt);
```
Pseudorandomly shuffle an array in place.
* `items` Array to shuffle.
* `num_of_items` Number of elements in the array. Must not be 0.
* `size_of_item` Size of each element of the array in bytes.
* `mt` MT19937 object to use for shuffling.
