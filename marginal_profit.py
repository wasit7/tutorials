# -*- coding: utf-8 -*-
"""
Created on Wed May 20 21:45:44 2015

@author: Wasit
"""

#xy=20*x+1000
#y=20+1000/x
import numpy as np
from matplotlib import pyplot as plt

x=np.arange(10,50)
y=20+1000./x
plt.plot(x,y)
plt.grid()