* Makoto Matsumoto and Takuji Nishimura, "Mersenne Twister: A 623-dimensionally Equidistributed Uniform Pseudo-random
  Number Generator", in ACM Transactions on Modeling and Computer Simulation, vol. 8, no. 1, pp. 3-30, 1998,
  doi:10.1145/272991.272995.
* Makoto Matsumoto and Takuji Nishimura, "Mersenne Twister with improved initialization" [source code],
  http://www.math.sci.hiroshima-u.ac.jp/m-mat/MT/MT2002/emt19937ar.html, 2002.
* Christian Stigen Larsen, "A fast Mersenne Twister in C++" [source code],
  https://github.com/cslarsen/mersenne-twister, 2017.

# Mersenne Twister (MT19937): Pseudorandom Number Generators
This package provides high-performance 32- and 64-bit global-state (thread-unsafe) and thread-safe uniform pseudorandom
number generators and some utility functions for C. These are intended as replacements for the `rand` family of
functions of the C standard library. An object-oriented C++ API and a module-based Python API are also provided.

The behaviour of this implementation matches the required behaviour of an MT19937 implementation as set down by the C++
standard. However, it is faster than GCC's and Clang's implementations. In theory, its speed is on par with that of C.
S. Larsen's implementation (which is … extremely fast:sweat_smile:). In practice, it is a couple of nanoseconds
slower—since it is meant to be used as a shared object, each function has some lookup overhead.

See [`doc`](doc) for the documentation of this package. [`examples`](examples) contains usage examples. For performance
analysis, go to [`benchmarks`](benchmarks).

## Installation Requirements
These are the versions I have tested the installation with. Older versions may also work. You may not need all of
these, depending on how and what you are installing.
* cURL ≥ 7.68.0
* GCC ≥ 9.4.0 or Clang ≥ 12.0.0
* Git ≥ 2.30.2
* GNU Make ≥ 4.2.1
* Python ≥ 3.8 and its C headers and library
* pip ≥ 23.0

Any compiler other than GCC and Clang should also be okay, because the code is reasonably standard-compliant. For
instance, it doesn't even assume that the `time` function from `stdlib.h` returns an integer. It converts the return
value into an integer, because the return type of `time` is implementation-defined. (Nevertheless, consider creating an
issue if you encounter compiler errors.)

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
    mt19937_init32(NULL);
    for(int i = 0; i < 10; ++i)
    {
        printf("%lu\n", mt19937_rand32(NULL));
    }

    // 64-bit MT19937.
    mt19937_init64(NULL);
    for(int i = 0; i < 10; ++i)
    {
        printf("%llu\n", mt19937_rand64(NULL));
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
```
pip install .
```

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
