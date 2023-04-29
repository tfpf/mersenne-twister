* All members of `struct mt19937_t` (32-bit MT19937) and `struct mt19937_64_t` (64-bit MT19937) objects should be
  considered private.
* The entities documented below are macros, but written to behave like functions. Hence, I document them as if they are
  functions.
* The last argument of each of the macros is `mt`, which denotes the 32- or 64-bit MT19937 object to use.
  * **This is an optional argument.** If it is not provided, the internal 32- or 64-bit MT19937 object is used.
  * For instance, `mt19937_rand();` and `mt19937_rand(foo);` are both valid invocations of `mt19937_rand`—the former
    generates a pseudorandom number using the internal 32-bit MT19937 object, and the latter does so using `foo`.
  * The internal 32- and 64-bit MT19937 objects are initialised by default as if they were seeded with 5489.
* Further arguments beyond `mt`, if given, are ignored without warnings.

---

```C
void mt19937_seed(uint32_t seed, struct mt19937_t *mt);
```
Seed 32-bit MT19937.
* `seed` 32-bit number. If this is 0, it will be seeded with the sum of the Unix time and the process ID.
* `mt` MT19937 object to seed. Optional. If not provided, the internal 32-bit MT19937 object is seeded.

```C
void mt19937_64_seed(uint64_t seed, struct mt19937_64_t *mt);
```
Seed 64-bit MT19937.
* `seed` 64-bit number. If this is 0, it will be seeded with the sum of the Unix time and the process ID.
* `mt` MT19937 object to seed. Optional. If not provided, the internal 64-bit MT19937 object is seeded.

---

```C
uint32_t mt19937_rand(struct mt19937_t *mt);
```
Generate a pseudorandom number.
* `mt` MT19937 object to use. Optional. If not provided, the internal 32-bit MT19937 object is used.
* → Uniform pseudorandom 32-bit number.

```C
uint64_t mt19937_64_rand(struct mt19937_64_t *mt);
```
Generate a pseudorandom number.
* `mt` MT19937 object to use. Optional. If not provided, the internal 64-bit MT19937 object is used.
* → Uniform pseudorandom 64-bit number.

---

```C
uint32_t mt19937_rand_integer(uint32_t modulus, struct mt19937_t *mt);
```
Generate a pseudorandom residue.
* `modulus` 32-bit number. Must not be 0.
* `mt` MT19937 object to use. Optional. If not provided, the internal 32-bit MT19937 object is used.
* → Uniform pseudorandom 32-bit number from 0 (inclusive) to `modulus` (exclusive).

```C
uint64_t mt19937_64_rand_integer(uint64_t modulus, struct mt19937_64_t *mt);
```
Generate a pseudorandom residue.
* `modulus` 64-bit number. Must not be 0.
* `mt` MT19937 object to use. Optional. If not provided, the internal 64-bit MT19937 object is used.
* → Uniform pseudorandom 64-bit number from 0 (inclusive) to `modulus` (exclusive).

---

```C
double mt19937_rand_real(struct mt19937_t *mt);
```
Generate a pseudorandom fraction.
* `mt` MT19937 object to use. Optional. If not provided, the internal 32-bit MT19937 object is used.
* → Uniform pseudorandom number from 0 (inclusive) to 1 (inclusive).

```C
double long mt19937_64_rand_real(struct mt19937_64_t *mt);
```
Generate a pseudorandom fraction.
* `mt` MT19937 object to use. Optional. If not provided, the internal 64-bit MT19937 object is used.
* → Uniform pseudorandom number from 0 (inclusive) to 1 (inclusive).

---

```C
void mt19937_rand_shuffle(void *items, uint32_t num_of_items, size_t size_of_item, struct mt19937_t *mt);
```
Pseudorandomly shuffle an array in place.
* `items` Array to shuffle.
* `num_of_items` Number of elements in the array. Must not be 0.
* `size_of_item` Size of each element of the array in bytes.
* `mt` MT19937 object to use. Optional. If not provided, the internal 32-bit MT19937 object is used.
