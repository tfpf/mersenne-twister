from distutils.core import Extension
from distutils.core import setup

setup(
    name='mt19937',
    ext_modules=[Extension('mt19937', sources=['lib/pymt19937.c'])],
)
