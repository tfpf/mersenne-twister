#! /usr/bin/env python3

import mt19937

mt19937.seed32(1)
for _ in range(4):
    print(mt19937.rand32(), end=' ')
for _ in range(4):
    print(mt19937.real32(), end=' ')
print()
