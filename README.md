Makoto Matsumoto and Takuji Nishimura, "Mersenne Twister: A 623-dimensionally Equidistributed Uniform Pseudo-random
Number Generator", in ACM Transactions on Modeling and Computer Simulation, vol. 8, no. 1, pp. 3-30, January 1998,
doi:10.1145/272991.272995.

# Mersenne Twister
This package provides Mersenne Twister implementations and some utility functions, which are intended as replacements
for the `rand` family of functions.

See [`include/mt19937.h`](include/mt19937.h) for the documentation of all available functions.

## Usage
### Without Installation
Download [`include/mt19937.h`](include/mt19937.h), [`lib/mt19937.c`](lib/mt19937.c) and
[`lib/mt19937_common.c`](lib/mt19937_common.c). Place them in the same directory. Create a file `example.c` in that
directory with the following contents.

```C
#include <stdio.h>

#include "mt19937.h"

int main(void)
{
    // Seed the 32-bit PRNG. Optional.
    mt19937_seed(0);
    for(int i = 0; i < 10; ++i)
    {
        // Generate a random 32-bit number.
        printf("%lu\n", mt19937_rand());
    }

    // Seed the 64-bit PRNG. Optional.
    mt19937_64_seed(0);
    for(int i = 0; i < 10; ++i)
    {
        // Generate a random 64-bit number.
        printf("%llu\n", mt19937_64_rand());
    }
}
```

Compile the program using
```
gcc -o example example.c mt19937.c
```
and run it with
```
./example
```
to see some random numbers.

### With Installation
```
sudo make install
```
This will create `/usr/include/mt19937.h` and `/usr/lib/libmt19937.so`. **Be sure that you don't already have those two
files (perhaps from some other package) to avoid breaking your system.** On most Linux systems, you will then be able
to compile the above program with just
```
gcc -o example example.c -lmt19937
```
without having `mt19937.h`, `mt19937.c` and `mt19937_common.c` in the working directory.

# Sudoku Generator and Solver
I just wanted to rewrite an old C program of mine using a better style, and then verify that it worked correctly.

## Compile
```
make
```

## Generate
```
./solve_sudoku 12
```
will write a sudoku puzzle of difficulty level 12 to standard output. Copy it to a file, say, `sudoku.txt`.
Alternatively, directly write the output to `sudoku.txt`.
```
./solve_sudoku 12 | tee sudoku.txt
```
A puzzle of difficulty level 0 (the minimum) is a solved puzzle, while one of difficulty level 20 (the maximum) is an
empty puzzle.

## Solve
```
./solve_sudoku sudoku.txt
```
will display the solution.

The solver will read from standard input if you don't provide any command line arguments. Interestingly, this means you
can pipe the output of the generator to the solver
```
./solve_sudoku 12 | ./solve_sudoku
```
though that is probably of no use, since it doesn't show the puzzle first.

The solver is rather primitive. If it cannot fill any cell in the puzzle after multiple attempts, it makes a random
guess (using MT19937). If, as a result of this, the puzzle becomes unsolvable, it bins everything and starts a fresh
attempt. This has a rather hilarious consequence: the solver can solve even an empty puzzle! Indeed, that's how the
generator works: it solves an empty puzzle and then removes some of the numbers!
