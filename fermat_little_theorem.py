# -*- coding: utf-8 -*-
"""
To test Fermat little theorem
Created on Mon Oct 27 15:38:06 2014

@author: Wasit

"""


pmax=1000
p=2
a=2
while p<pmax:
    if ((a**p-a)%p)==0:
        print("%3d "%p)
    p=p+1