No reentrant implementations are provided for Python, mainly because I don't know Python well enough to implement C
structures in it, but also because the CPython implementation has a global interpreter lock, which makes reentrancy not
as important as it is for C and C++.
