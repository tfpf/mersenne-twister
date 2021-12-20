#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////
// Function
// Read a sudoku problem into a two-dimensional array. Zeros are used to
// represent blank cells. The format of the input file is the same as that
// output by the program `generate_sudoku.py'.
//
// Args:
//     fname: char const * (name of the input file to read the problem from)
//     table: int [][] (sudoku table)
//
// Returns:
//     bool (`true' for success, `false' for failure)
///////////////////////////////////////////////////////////////////////////////
bool read_sudoku(char const *fname, int table[][9])
{
    FILE *fptr = fopen(fname, "r");
    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            char c;
            if(fscanf(fptr, " %c", &c) == 0 || (c != '-' && (c < '1' || c > '9')))
            {
                printf("%c\n", c);
                return false;
            }

            if(c == '-')
            {
                table[i][j] = 0;
            }
            else
            {
                table[i][j] = c - '0';
            }
        }
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////////
// Function
// Check whether there are any empty cells.
//
// Args:
//     table: int [][] (sudoku table)
//
// Returns:
//     bool (`true' if there is at least one empty cell, else `false')
///////////////////////////////////////////////////////////////////////////////
bool is_solved(int table[][9])
{
    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            if(table[i][j] == 0)
            {
                return false;
            }
        }
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////////
// Function
// Display the sudoku table. Adacent blocks have different background colours.
// This is accomplished using an ANSI colour code.
//
// Args:
//     table: int [][] (sudoku table)
///////////////////////////////////////////////////////////////////////////////
void show(int table[][9])
{
    for(int i = 0; i < 9; ++i)
    {
        printf("    ");
        for(int j = 0; j < 9; ++j)
        {
            if((i / 3 + j / 3) % 2 == 0)
            {
                printf("\033[100m");
            }
            printf("%d", table[i][j]);
            if(j % 3 == 2)
            {
                printf("\033[0m");
            }
            printf("  ");
        }
        printf("\n");
    }
}

///////////////////////////////////////////////////////////////////////////////
// Function
// Check whether the number given may be placed in the given row.
//
// Args:
//     table: int [][] (sudoku table)
//     row: int (a number from 1 to 9)
//     num: int (a number from 1 to 9)
//
// Returns:
//     bool (`true' if `num' may appear at row index `row', else `false')
///////////////////////////////////////////////////////////////////////////////
bool allowed_in_row(int table[][9], int row, int num)
{
    for(int j = 0; j < 9; ++j)
    {
        if(table[row][j] == num)
        {
            return false;
        }
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////////
// Function
// Check whether the number given may be placed in the given column.
//
// Args:
//     table: int [][] (sudoku table)
//     col: int (a number from 1 to 9)
//     num: int (a number from 1 to 9)
//
// Returns:
//     bool (`true' if `num' may appear at column index `col', else `false')
///////////////////////////////////////////////////////////////////////////////
bool allowed_in_col(int table[][9], int col, int num)
{
    for(int i = 0; i < 9; ++i)
    {
        if(table[i][col] == num)
        {
            return false;
        }
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////////
// Function
// Check whether the number given may be placed in the indicated block.
//
// Args:
//     table: int [][] (sudoku table)
//     row: int (a number from 1 to 9)
//     col: int (a number from 1 to 9)
//     num: int (a number from 1 to 9)
//
// Returns:
//     bool (`true' if `num' may appear in the block indicated, else `false')
///////////////////////////////////////////////////////////////////////////////
bool allowed_in_block(int table[][9], int row, int col, int num)
{
    // Find out where the block indicated by `row' and `col' begins.
    int block_row_start = row - row % 3;
    int block_col_start = col - col % 3;

    for(int i = block_row_start; i < block_row_start + 3; ++i)
    {
        for(int j = block_col_start; j < block_col_start + 3; ++j)
        {
            if(i != row && j != col && table[i][j] == num)
            {
                return false;
            }
        }
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////////
// Function
// Check whether the number given may be placed at the given position. At the
// time of calling this function, it must be true that `table[row][col] == 0'.
//
// Args:
//     table: int [][] (sudoku table)
//     row: int (a number from 1 to 9)
//     col: int (a number from 1 to 9)
//     num: int (a number from 1 to 9)
//
// Returns:
//     bool (`true' if `table[row][col]' can be assigned `num', else `false')
///////////////////////////////////////////////////////////////////////////////
bool allowed_at_position(int table[][9], int row, int col, int num)
{
    return allowed_in_row(table, row, num)
           && allowed_in_col(table, col, num)
           && allowed_in_block(table, row, col, num);
}

///////////////////////////////////////////////////////////////////////////////
// Function
// Check how many numbers are allowed at the given position. If only a single
// number is allowed, assign it at that position. Otherwise, do nothing. At the
// time of calling this function, it must be true that `table[row][col] == 0'.
//
// Args:
//     table: int [][] (sudoku table)
//     row: int (a number from 1 to 9)
//     col: int (a number from 1 to 9)
///////////////////////////////////////////////////////////////////////////////
void select_allowed(int table[][9], int row, int col)
{
    int allowed;
    int count_allowed = 0;
    for(int num = 1; num <= 9; ++num)
    {
        if(allowed_at_position(table, row, col, num))
        {
            allowed = num;
            ++count_allowed;
        }
    }

    if(count_allowed == 1)
    {
        table[row][col] = allowed;
    }
}

///////////////////////////////////////////////////////////////////////////////
// Function
// Check how many possible positions the given number may be placed at. If only
// a single position is present in a row or column or block, assign it at
// that/those position/positions. Otherwise, do nothing.
//
// Args:
//     table: int [][] (sudoku table)
//     num: int (a number from 1 to 9)
///////////////////////////////////////////////////////////////////////////////
void select_possible(int table[][9], int num)
{
    // Possibilities in each row.
    for(int i = 0; i < 9; ++i)
    {
        if(!allowed_in_row(table, i, num))
        {
            continue;
        }

        int possible_row, possible_col;
        int count_possible = 0;
        for(int j = 0; j < 9; ++j)
        {
            if(table[i][j] == 0 && allowed_at_position(table, i, j, num))
            {
                possible_row = i;
                possible_col = j;
                ++count_possible;
            }
        }

        if(count_possible == 1)
        {
            table[possible_row][possible_col] = num;
        }
    }

    // Possibilities in each column.
    for(int j = 0; j < 9; ++j)
    {
        if(!allowed_in_col(table, j, num))
        {
            continue;
        }

        int possible_row, possible_col;
        int count_possible = 0;
        for(int i = 0; i < 9; ++i)
        {
            if(table[i][j] == 0 && allowed_at_position(table, i, j, num))
            {
                possible_row = i;
                possible_col = j;
                ++count_possible;
            }
        }

        if(count_possible == 1)
        {
            table[possible_row][possible_col] = num;
        }
    }

    // Possibilities in each block.
    for(int block_row_start = 0; block_row_start < 9; block_row_start += 3)
    {
        for(int block_col_start = 0; block_col_start < 9; block_col_start += 3)
        {
            if(!allowed_in_block(table, block_row_start, block_col_start, num))
            {
                continue;
            }

            int possible_row, possible_col;
            int count_possible = 0;
            for(int i = block_row_start; i < block_row_start + 3; ++i)
            {
                for(int j = block_col_start; j < block_col_start + 3; ++j)
                {
                    if(table[i][j] == 0 && allowed_at_position(table, i, j, num))
                    {
                        possible_row = i;
                        possible_col = j;
                        ++count_possible;
                    }
                }
            }

            if(count_possible == 1)
            {
                table[possible_row][possible_col] = num;
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Function
// Do one pass of the table, filling cells wherever possible.
//
// Args:
//     table: int [][] (sudoku table)
///////////////////////////////////////////////////////////////////////////////
void single_pass(int table[][9])
{
    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            if(table[i][j] == 0)
            {
                select_allowed(table, i, j);
            }
        }
    }

    for(int num = 1; num <= 9; ++num)
    {
        select_possible(table, num);
    }
}

///////////////////////////////////////////////////////////////////////////////
// Main function.
///////////////////////////////////////////////////////////////////////////////
int main(int const argc, char const *argv[])
{
    if(argc < 2)
    {
        printf("Usage:\n");
        printf("\t%s <input file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int table[9][9];
    if(!read_sudoku(argv[1], table))
    {
        printf("Could not read the file %s.\n", argv[1]);
        return EXIT_FAILURE;
    }

    for(int i = 0; i < 200; ++i)
    {
        single_pass(table);
    }

    show(table);

    return EXIT_SUCCESS;
}

