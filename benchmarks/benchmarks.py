#! /usr/bin/env python3

import math
import mt19937
import time
import timeit


def benchmark(stmt, number, passes=32):
    delay = math.inf
    for _ in range(passes):
        delay_ = timeit.timeit(stmt=stmt, number=number, timer=time.perf_counter_ns)
        delay = min(delay, delay_)
    result = delay / number
    print(f'{stmt.__name__:>20} {result:8.2f} ns')


def main():
    """Main function."""
    benchmark(mt19937.init32, 0x1000)
    benchmark(mt19937.init64, 0x1000)
    benchmark(mt19937.rand32, 0xFFF0)
    benchmark(mt19937.rand64, 0xFFF0)
    benchmark(mt19937.real32, 0xFFF0)
    benchmark(mt19937.real64, 0xFFF0)


if __name__ == '__main__':
    main()
