#ifndef TFPF_MERSENNE_TWISTER_EXAMPLES_SUDOKU_INCLUDE_SUDOKU_UTILS_H_
#define TFPF_MERSENNE_TWISTER_EXAMPLES_SUDOKU_INCLUDE_SUDOKU_UTILS_H_

#include <stdbool.h>

bool read_sudoku(char const *fname, int table[][9]);
int number_of_empty_cells(int const table[][9]);
void write_sudoku(int const table[][9]);
bool allowed_in_row(int const table[][9], int row, int num);
bool allowed_in_col(int const table[][9], int col, int num);
bool allowed_in_block(int const table[][9], int row, int col, int num);
bool allowed_at_position(int const table[][9], int row, int col, int num);
void select_allowed(int table[][9], int row, int col, bool assign_random);
void select_possible_in_row(int table[][9], int row, int num);
void select_possible_in_col(int table[][9], int col, int num);
void select_possible_in_block(int table[][9], int row, int col, int num);
void select_possible(int table[][9], int num);
void single_pass(int table[][9], bool assign_random);
void solve_sudoku(int table[][9]);
void generate_sudoku(int table[][9], double difficulty);
bool validate_sudoku(int const table[][9], bool initial);

#endif  // TFPF_MERSENNE_TWISTER_EXAMPLES_SUDOKU_INCLUDE_SUDOKU_UTILS_H_
