#define _POSIX_C_SOURCE 199309L

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

///////////////////////////////////////////////////////////////////////////////
// Function
// Read a sudoku puzzle into a two-dimensional array. Zeros are used to
// represent blank cells. The format of the input file is the same as that
// output by the program `generate_sudoku.py'.
//
// Args:
//     fname: char const * (name of the input file to read the puzzle from)
//     table: int [][] (sudoku table)
//
// Returns:
//     bool (`true' for success, `false' for failure)
///////////////////////////////////////////////////////////////////////////////
bool read_sudoku(char const *fname, int table[][9])
{
    FILE *fptr = fopen(fname, "r");
    if(fptr == NULL)
    {
        return false;
    }

    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            char c;
            if(fscanf(fptr, " %c", &c) == 0 || (c != '-' && (c < '1' || c > '9')))
            {
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
// Count the empty cells (i.e. the positions filled with zeros).
//
// Args:
//     table: int [][] (sudoku table)
//
// Returns:
//     int
///////////////////////////////////////////////////////////////////////////////
int number_of_empty_cells(int table[][9])
{
    int zeros = 0;
    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            if(table[i][j] == 0)
            {
                ++zeros;
            }
        }
    }

    return zeros;
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
        for(int j = 0; j < 9; ++j)
        {
            printf("  ");
            bool colour = !((i / 3 + j / 3) % 2);
            if(colour && j % 3 == 0)
            {
                printf("\033[37;100m");
            }
            printf("%d", table[i][j]);
            if(colour && j % 3 == 2)
            {
                printf("\033[0m");
            }
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
//     row: int (a number from 0 to 8)
//     num: int (a number from 0 to 8)
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
//     col: int (a number from 0 to 8)
//     num: int (a number from 0 to 8)
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
//     row: int (a number from 0 to 8)
//     col: int (a number from 0 to 8)
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
//     row: int (a number from 0 to 8)
//     col: int (a number from 0 to 8)
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
// number is allowed, assign it at that position. Otherwise, do nothing.
// (Alternatively, assign a number at that position randomly, if told to do
// so.) At the time of calling this function, it must be true that
// `table[row][col] == 0'.
//
// Args:
//     table: int [][] (sudoku table)
//     row: int (a number from 0 to 8)
//     col: int (a number from 0 to 8)
//     assign_random: bool (whether to assign `table[row][col]' randomly)
///////////////////////////////////////////////////////////////////////////////
void select_allowed(int table[][9], int row, int col, bool assign_random)
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

    if(count_allowed == 1 || (count_allowed >= 1 && assign_random))
    {
        // GCC emits a superfluous warning for this line when compiling with
        // optimisations and warnings enabled.
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
        table[row][col] = allowed;
        #pragma GCC diagnostic pop
    }
}

///////////////////////////////////////////////////////////////////////////////
// Function
// Check how many positions the given number can be placed at in the given row.
// If there is only one position, assign it at there. Otherwise, do nothing.
//
// Args:
//     table: int [][] (sudoku table)
//     row: int (a number from 0 to 8)
//     num: int (a number from 0 to 8)
///////////////////////////////////////////////////////////////////////////////
void select_possible_in_row(int table[][9], int row, int num)
{
    if(!allowed_in_row(table, row, num))
    {
        return;
    }

    int possible_col;
    int count_possible = 0;
    for(int j = 0; j < 9; ++j)
    {
        if(table[row][j] == 0 && allowed_in_col(table, j, num) && allowed_in_block(table, row, j, num))
        {
            possible_col = j;
            ++count_possible;
        }
    }

    if(count_possible == 1)
    {
        table[row][possible_col] = num;
    }
}

///////////////////////////////////////////////////////////////////////////////
// Function
// Check how many positions the given number can be placed at in the given
// column. If there is only one position, assign it at there. Otherwise, do
// nothing.
//
// Args:
//     table: int [][] (sudoku table)
//     col: int (a number from 0 to 8)
//     num: int (a number from 0 to 8)
///////////////////////////////////////////////////////////////////////////////
void select_possible_in_col(int table[][9], int col, int num)
{
    if(!allowed_in_col(table, col, num))
    {
        return;
    }

    int possible_row;
    int count_possible = 0;
    for(int i = 0; i < 9; ++i)
    {
        if(table[i][col] == 0 && allowed_in_row(table, i, num) && allowed_in_block(table, i, col, num))
        {
            possible_row = i;
            ++count_possible;
        }
    }

    if(count_possible == 1)
    {
        table[possible_row][col] = num;
    }
}

///////////////////////////////////////////////////////////////////////////////
// Function
// Check how many positions the given number can be placed at in the given
// block. If there is only one position, assign it at there. Otherwise, do
// nothing.
//
// Args:
//     table: int [][] (sudoku table)
//     row: int (0, 3 or 6)
//     col: int (0, 3 or 6)
//     num: int (a number from 1 to 9)
///////////////////////////////////////////////////////////////////////////////
void select_possible_in_block(int table[][9], int row, int col, int num)
{
    if(!allowed_in_block(table, row, col, num))
    {
        return;
    }

    int possible_row, possible_col;
    int count_possible = 0;
    for(int i = row; i < row + 3; ++i)
    {
        for(int j = col; j < col + 3; ++j)
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
    for(int i = 0; i < 9; ++i)
    {
        select_possible_in_row(table, i, num);
    }

    for(int j = 0; j < 9; ++j)
    {
        select_possible_in_col(table, j, num);
    }

    for(int i = 0; i < 9; i += 3)
    {
        for(int j = 0; j < 9; j += 3)
        {
            select_possible_in_block(table, i, j, num);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Function
// Do one pass of the table, filling cells wherever possible.
//
// Args:
//     table: int [][] (sudoku table)
//     assign_random: bool (whether to fill a cell randomly)
///////////////////////////////////////////////////////////////////////////////
void single_pass(int table[][9], bool assign_random)
{
    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            if(table[i][j] == 0)
            {
                // At most one cell shall be filled randomly per function call.
                select_allowed(table, i, j, assign_random);
                assign_random = false;
            }
        }
    }

    for(int num = 1; num <= 9; ++num)
    {
        select_possible(table, num);
    }
}

///////////////////////////////////////////////////////////////////////////////
// Function
// Solve the sudoku puzzle.
//
// Args:
//     table: int [][] (sudoku table)
///////////////////////////////////////////////////////////////////////////////
void solve(int table[][9])
{
    int prev_zeros = 81;
    while(true)
    {
        int zeros = number_of_empty_cells(table);
        if(zeros == 0)
        {
            break;
        }

        // If no cells could be filled in an iteration, ask for a number to
        // be filled in randomly.
        bool assign_random = (zeros == prev_zeros);

        single_pass(table, assign_random);
        prev_zeros = zeros;
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

    struct timespec begin, end;
    clock_gettime(CLOCK_REALTIME, &begin);
    solve(table);
    clock_gettime(CLOCK_REALTIME, &end);
    int long delay_micro = (int long)(end.tv_sec - begin.tv_sec) * 1000000 + (end.tv_nsec - begin.tv_nsec) / 1000;

    show(table);
    printf("Solved in %ld μs (real time).\n", delay_micro);

    return EXIT_SUCCESS;
}
