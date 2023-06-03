#! /usr/bin/env python3

import mt19937

mt19937.seed64(1)
for _ in range(4):
    print(mt19937.rand64(), end=' ')
for _ in range(4):
    print(mt19937.real64(), end=' ')
print()
