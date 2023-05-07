from setuptools import Extension
from setuptools import setup

setup(
    name='mt19937',
    author='Vishal Pankaj Chandratreya',
    version='0.0.1',
    url='https://github.com/tfpf/mersenne-twister',
    ext_modules=[Extension('mt19937', sources=['lib/pymt19937.c'])],
)
