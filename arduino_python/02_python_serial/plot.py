# -*- coding: utf-8 -*-
"""
Created on Tue Jul 07 13:58:49 2015

@author: Wasit
"""

import serial
import re
import datetime
from matplotlib import pyplot as plt
import numpy as np
#ser = serial.Serial('/dev/tty.usbserial', 9600)
#ser = serial.Serial('COM7', 9600)
#ser = serial.Serial(0)  # open first serial port
Ncolumn=3
sample_rate=10 #[Hz]
total_time=500 #[sec]

#finding an enabled port
for i in xrange(20):
    try:
       ser = serial.Serial(i,9600,timeout=0, rtscts=1)
       break
    except:
       print "port COM%d is disabled"%(i+1)
print "Connecting to port: "+ser.name 
#set total recording time
endTime = datetime.datetime.now() + datetime.timedelta(seconds=total_time)
total_tick=256

#initial plotting
table=np.zeros(shape=(total_tick,Ncolumn))
plt.figure(1)

while True:
    if datetime.datetime.now() >= endTime:
        break
    record=re.split(',',ser.readline())
    try:
        record = map(int, record)
        table=np.roll(table, 1, axis=0)
        table[0,:]=record
        #print table
        plt.clf()
        #plt.plot(table[:,0],table[:,1],'x')
        plt.plot(table[:,1],"bo-",lw=2)
        plt.ylim((0, 1024) )
        plt.gca().invert_xaxis()
        plt.draw()
    except:
        pass    
    
    
ser.close()