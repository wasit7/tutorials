# -*- coding: utf-8 -*-
"""
Created on Tue Sep 15 11:21:08 2015

@author: Wasit
"""

from matplotlib import pyplot as plt
import numpy as np
import time
beta=0.5
g=9.8
dt=1e-3
Sx=0
Sy=0
Vx=0
Vy=50

fig = plt.figure()
ax = fig.gca()
#ax.set_autoscale_on(False)
for i in xrange(200):
    Vx=Vx+beta*(2-Sx)
    Vy=Vy+beta*(2-Sy)
    Sx=Sx+Vx*dt
    Sy=Sy+Vy*dt
    plt.plot(Sx,Sy,'ko')
    plt.draw()
    time.sleep(0.05)
    