# -*- coding: utf-8 -*-
"""
Created on Tue Jul 14 23:05:26 2015

@author: Wasit
"""

import random
y=-1
x=random.randint(0,32)
while x!=y:
    y=int(raw_input("guess a number:"))
    if y<x:
        print y," is LESS than the corrected number"
    if x<y:
        print y," is LARGER than the corrected number"

print y," is correct!"