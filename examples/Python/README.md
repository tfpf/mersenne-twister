The functions provided for Python all use the internal MT19937 objects, mainly because I don't know Python well enough
to implement C structures in it. See the documentation for other justifications.

There should be no reason to use this in Python, because the Python standard library makes available the `random`
module. But if you really want to, go right ahead.
