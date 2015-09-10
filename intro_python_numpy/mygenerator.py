# -*- coding: utf-8 -*-
"""
Created on Thu Sep 10 17:04:30 2015

@author: Wasit
"""

def inc(n):
    x=0
    while x<n:
        yield x
        x=x+1

def poly(x):
    return (x,x**2,x**3,x**4)