# -*- coding: utf-8 -*-
"""
Created on Fri Aug 21 14:43:33 2015

@author: Wasit

to compile
    run setup.py build_ext --inplace
    or python setup.py build_ext --inplace

to run demo_python
    %timeit -n100 dp.primes(100)

to run demo_cython
    %timeit -n100 dc.primes(100)
"""
from distutils.core import setup
from Cython.Build import cythonize

setup(
    ext_modules=cythonize("demo_cython.pyx"),
)