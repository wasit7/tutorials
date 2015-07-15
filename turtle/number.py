# -*- coding: utf-8 -*-
"""
Created on Tue Jul 14 13:18:19 2015

@author: Wasit
"""

import numpy as np
x = np.random.randint(0,9)
while x!=ux:
    ux=int(raw_input("please enter your number: "))
    if ux < x:
        print "less"
    if x < ux:
        print "more"

print "Hooley you got the number!"