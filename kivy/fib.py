# -*- coding: utf-8 -*-
"""
Created on Fri Apr 22 17:59:04 2016

@author: Wasit
"""

def fib(x):
    if x==1:
        return 1
    else:
        return x*fib(x-1)

if __name__ == "__main__":
    print fib(4)