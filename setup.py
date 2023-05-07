from setuptools import Extension, find_packages, setup

ext_modules = [Extension(
    name='mt19937',
    sources=['./lib/pymt19937.c'],
    include_dirs=['./include'],
    py_limited_api=True,
)]
kwargs = dict(
    packages=find_packages(where='./lib'),
    package_dir={'': './lib'},
    ext_modules=ext_modules,
)
setup(**kwargs)
