#! /usr/bin/env python3

import timeit


def benchmark(stmt, number=1):
    delay = timeit.timeit(stmt=stmt, setup='import mt19937', number=number) * 10 ** 9 / number
    print(f'{stmt:>20} {delay:8.1f} ns')


def main():
    """Main function."""
    benchmark('mt19937.init32()', 0x10000)
    benchmark('mt19937.init64()', 0x10000)
    benchmark('mt19937.rand32()', 0x27000)
    benchmark('mt19937.rand64()', 0x27000)
    benchmark('mt19937.real32()', 0x27000)
    benchmark('mt19937.real64()', 0x27000)


if __name__ == '__main__':
    main()
