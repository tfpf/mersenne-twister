#ifndef MERSENNE_TWISTER_SUDOKU_SOLVER_INCLUDE_MT19937_H_
#define MERSENNE_TWISTER_SUDOKU_SOLVER_INCLUDE_MT19937_H_

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

void mt19937_seed(uint32_t seed);
uint32_t mt19937_rand(void);
bool mt19937_test(void);
uint32_t mt19937_rand_integer(uint32_t modulus);
double mt19937_rand_real(void);
void mt19937_rand_shuffle(void *items, uint32_t items_length, size_t item_size);

#endif  // MERSENNE_TWISTER_SUDOKU_SOLVER_INCLUDE_MT19937_H_
