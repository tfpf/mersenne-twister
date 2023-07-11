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

See [`doc`](doc) for the documentation of this package. [`examples`](examples) contains usage examples and a randomised
sudoku generator and solver which uses MT19937. For performance analysis, go to [`benchmarks`](benchmarks).

## Installation Requirements
These are the versions I have tested the installation with. Older versions may also work. You may not need all of
these, depending on how and what you are installing.
* cURL ≥ 7.68.0
* GCC ≥ 9.4.0 or Clang ≥ 12.0.0
* Git ≥ 2.30.2
* GNU Make ≥ 4.2.1
* CPython ≥ 3.8 and its C headers and library
* pip ≥ 23.0

On Windows, these are available natively via [MSYS2](https://www.msys2.org) and in a Linux environment via
[WSL](https://learn.microsoft.com/en-us/windows/wsl/about).

Any compiler other than GCC and Clang should also be okay, because the code is reasonably standard-compliant. For
instance, it doesn't even assume that the `time` function from `stdlib.h` returns an integer. It converts the return
value into an integer, because the return type of `time` is implementation-defined. (Nevertheless, consider creating an
issue if you encounter compiler errors.)

The installation commands mentioned below must be entered in
* the terminal if you are on Linux, or
* the MSYS2 terminal or WSL terminal if you are on Windows.

## Install for C (and C++)
```sh
curl https://raw.githubusercontent.com/tfpf/mersenne-twister/main/install.sh | sh
```

Alternatively:
```sh
git clone https://github.com/tfpf/mersenne-twister.git
cd mersenne-twister
./install.sh
```
You can change `Prefix` in [`Makefile`](Makefile) to change the installation location, but then you may additionally
have to configure the search paths of your compiler and linker.

### Quick Start
Put the following code in a file `example.c`:
```C
#include <mt19937.h>
#include <stdio.h>

int main(void)
{
    // 32-bit MT19937.
    mt19937_init32(NULL);
    for(int i = 0; i < 10; ++i)
    {
        long unsigned r = mt19937_rand32(NULL);
        printf("%lu\n", r);
    }

    // 64-bit MT19937.
    mt19937_init64(NULL);
    for(int i = 0; i < 10; ++i)
    {
        long long unsigned r = mt19937_rand64(NULL);
        printf("%llu\n", r);
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

## Install for Python
```
pip install git+https://github.com/tfpf/mersenne-twister.git
```

Alternatively:
```sh
git clone https://github.com/tfpf/mersenne-twister.git
cd mersenne-twister
pip install .
```

This does not currently work on Windows because of issues with MSYS2.
