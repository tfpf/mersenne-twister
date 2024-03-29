from setuptools import Extension, find_packages, setup

ext_modules = [Extension(
    name='mt19937',
    sources=['lib/pymt19937.c', 'lib/mt19937.c'],
    include_dirs=['include'],
    extra_compile_args=['-O3'],
    py_limited_api=True,
)]
kwargs = dict(
    package_dir={'': 'lib'},
    ext_modules=ext_modules,
)
setup(**kwargs)
