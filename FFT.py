# -*- coding: utf-8 -*-
"""
Created on Tue May 19 13:43:54 2015

@author: Wasit
"""

import numpy as np
from matplotlib import pyplot as plt
f1=1.0
f2=4.0
t=np.linspace(0,1,100)#sampling rate 100Hz, signal=1Hz
f=10*np.sin(f1*2*np.pi*t-0.5)+np.sin(f2*2*np.pi*t)
fre=np.fft.fft(f)
plt.plot(np.arange(100),np.absolute(fre))
#plt.plot(np.arange(100),fre.real,'b')#real
#plt.plot(np.arange(100),fre.imag,'r')#real