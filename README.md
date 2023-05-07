Makoto Matsumoto and Takuji Nishimura, "Mersenne Twister: A 623-dimensionally Equidistributed Uniform Pseudo-random
Number Generator", in ACM Transactions on Modeling and Computer Simulation, vol. 8, no. 1, pp. 3-30, January 1998,
doi:10.1145/272991.272995.

# Mersenne Twister (MT19937): Pseudorandom Number Generators
This package provides 32- and 64-bit global-state (non-reentrant) and reentrant uniform pseudorandom number generators
and some utility functions for C and C++. These are intended as replacements for the `rand` family of functions of the
C standard library. The behaviours of these implementations are consistent with those of `std::mt19937` and
`std::mt19937_64` of the C++ standard library.

See [`doc`](doc) for the documentation of this package. See [`examples`](examples) for usage examples.

## Installation Requirements
These are the versions I have tested the installation with. Older versions may also work.
* cURL ≥ 7.74.0
* GCC ≥ 10.2.1 or Clang ≥ 13.0.1
* Git ≥ 2.30.2
* GNU Make ≥ 4.3

## Install for C (and C++)
The fastest way to install this is to run the following command in a terminal window.
```sh
curl https://raw.githubusercontent.com/tfpf/mersenne-twister/main/install.sh | sh
```
This may prompt you for the superuser's password, and will create `/usr/include/mt19937.h` and
`/usr/lib/libmt19937.so`, which should be enough on most Linux systems. **Be sure that you don't already have those two
files (perhaps from some other package) to avoid breaking your system.**

Alternatively, download/clone this repository and run
```sh
sudo make install
```
from the topmost directory of the repository. The above comments apply to this mode of installation as well. You can
change `Prefix` in [`Makefile`](Makefile) to install it elsewhere, but then you may additionally have to configure the
search paths of your compiler and linker.

### Demo
To see it in action, put the following code in a file `example.c`:
```C
#include <mt19937.h>
#include <stdio.h>

int main(void)
{
    // 32-bit MT19937.
    mt19937_seed(0);
    for(int i = 0; i < 10; ++i)
    {
        printf("%lu\n", mt19937_rand());
    }

    // 64-bit MT19937.
    mt19937_64_seed(0);
    for(int i = 0; i < 10; ++i)
    {
        printf("%llu\n", mt19937_64_rand());
    }
}
```
compile it with
```sh
gcc -o example example.c -lmt19937
```
and run it using
```sh
./example
```
to see some random numbers.

### Uninstall
```sh
sudo make uninstall
```
**Do not run this command if you already had the files `/usr/include/mt19937.h` and `/usr/lib/libmt19937.so` before
installing this package.**

## Install for Python
You must have Python development tools installed if you want to install the Python API of this package.
```
python3 setup.py install --user
```
I plan to move from Setuptools to pip once I figure out how to.:sweat_smile:

### Uninstall
```
pip uninstall mt19937
```

# Sudoku Generator and Solver
I just wanted to rewrite an old C program of mine using a better style, and then verify that it worked correctly.

To use the sudoku generator and solver, install this package first. (See the previous section.)

## Compile
```sh
make
```

## Generate
```sh
./solve_sudoku 12
```
will write a sudoku puzzle of difficulty level 12 to standard output. Copy it to a file, say, `sudoku.txt`.
Alternatively, directly write the output to `sudoku.txt`.
```sh
./solve_sudoku 12 | tee sudoku.txt
```
A puzzle of difficulty level 0 (the minimum) is a solved puzzle, while one of difficulty level 20 (the maximum) is an
empty puzzle.

## Solve
```sh
./solve_sudoku sudoku.txt
```
will display the solution.

The solver will read from standard input if you don't provide any command line arguments. Interestingly, this means you
can pipe the output of the generator to the solver
```sh
./solve_sudoku 12 | ./solve_sudoku
```
though that is probably of no use, since it doesn't show the puzzle first.

The solver is rather primitive. If it cannot fill any cell in the puzzle after multiple attempts, it makes a random
guess (using MT19937). If, as a result of this, the puzzle becomes unsolvable, it bins everything and starts a fresh
attempt. This has a rather hilarious consequence: the solver can solve even an empty puzzle! Indeed, that's how the
generator works: it solves an empty puzzle and then removes some of the numbers!
