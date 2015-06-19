# -*- coding: utf-8 -*-
"""
Created on Fri May 01 20:53:42 2015

@author: Wasit
"""

from matplotlib import pyplot as plt
import numpy as np

A=np.array([[2,1],[1,-1]])
b=np.array([[5],[1]])
x=np.dot(np.linalg.inv(A),b)
