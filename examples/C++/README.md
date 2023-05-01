Enter the command
```sh
make -B
```
to compile each of these example programs. Doing so will also display the compile command used.

There should be no reason to use this in C++, because the C++ standard library makes available `std::mt19937` and
`std::mt19937_64` via `#include <random>`. But if you really want to, go right ahead.
