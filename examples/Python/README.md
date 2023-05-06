No reentrant implementations are provided for Python, mainly because I don't know Python well enough to implement C
structures in it, but also because the CPython implementation has a global interpreter lock. From the Python bytecode
disassembly, it looks like a C function call corresponds to a single Python bytecode instruction, so there are no race
conditions to worry about.

There should be no reason to use this in Python, because the Python standard library makes available the `random`
module. But if you really want to, go right ahead.
