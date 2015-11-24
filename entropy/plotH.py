# -*- coding: utf-8 -*-
"""
Created on Tue Nov 24 20:42:51 2015

@author: Wasit
"""
import numpy as np
from matplotlib import pyplot as plt
plt.cla()
p=np.random.rand(4)
p=p/np.linalg.norm(p)
H=-1.0*np.dot(p,np.log2(p))

plt.bar(np.arange(p.size),p)
x1,x2,y1,y2 = plt.axis()
plt.axis((x1,x2,0,1))
plt.title(r"$H=\sum p_i \log(p_i)=%0.2E$"%H)