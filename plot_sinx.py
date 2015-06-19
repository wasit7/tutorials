# -*- coding: utf-8 -*-
"""
Created on Fri May 01 20:34:39 2015

@author: Wasit
"""

from matplotlib import pyplot as plt
import numpy as np

x=np.linspace(0,7,100)
y=np.sin(x)
plt.plot(x,y)
