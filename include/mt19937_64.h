#ifndef MERSENNE_TWISTER_SUDOKU_SOLVER_INCLUDE_MT19937_64_H_
#define MERSENNE_TWISTER_SUDOKU_SOLVER_INCLUDE_MT19937_64_H_

#include <inttypes.h>

void mt19937_64_seed(uint64_t seed);
uint64_t mt19937_64_rand(void);
uint64_t mt19937_64_rand_integer(uint64_t modulus);
double mt19937_64_rand_real(void);

#endif  // MERSENNE_TWISTER_SUDOKU_SOLVER_INCLUDE_MT19937_64_H_
