#define _POSIX_C_SOURCE 199309L

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mt19937.h"
#include "sudoku_utils.h"

#define REPORT_RUNNING_TIME(function_call, delay_micro) \
int long delay_micro; \
{ \
    struct timespec begin, end; \
    clock_gettime(CLOCK_REALTIME, &begin); \
    function_call; \
    clock_gettime(CLOCK_REALTIME, &end); \
    delay_micro = (int long)(end.tv_sec - begin.tv_sec) * 1000000 + (end.tv_nsec - begin.tv_nsec) / 1000; \
}

/******************************************************************************
 * Main function.
 *****************************************************************************/
int main(int const argc, char const *argv[])
{
    if(!mt19937_test())
    {
        fprintf(stderr, "Warning: pseudorandom number generator not working as expected.\n");
    }

    mt19937_seed(0);

    // Generate a puzzle if the first argument is a number.
    int table[9][9] = {{0}};
    char const *fname = NULL;
    if(argc >= 2)
    {
        char *endptr;
        double difficulty = strtod(argv[1], &endptr);
        if(*endptr == '\0')
        {
            generate_sudoku(table, difficulty);
            return EXIT_SUCCESS;
        }
        fname = argv[1];
    }

    // Solve the given puzzle if the first argument is a file name (or isn't
    // provided).
    if(!read_sudoku(fname, table))
    {
        fprintf(stderr, "Could not read the puzzle.\n");
        return EXIT_FAILURE;
    }
    if(!validate_sudoku(table, true))
    {
        fprintf(stderr, "The puzzle is malformed.\n");
        return EXIT_FAILURE;
    }

    REPORT_RUNNING_TIME(solve_sudoku(table), delay_micro)
    write_sudoku(table);
    if(!validate_sudoku(table, false))
    {
        fprintf(stderr, "Could not find the solution.\n");
        return EXIT_FAILURE;
    }
    printf("Solved in %ld μs (real time).\n", delay_micro);
    return EXIT_SUCCESS;
}
