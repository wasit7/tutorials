# -*- coding: utf-8 -*-
"""
Created on Wed Jul 08 14:20:27 2015

@author: Wasit
"""

import time

import numpy as np

from bokeh.plotting import *

import serial
import re
import datetime

#ser = serial.Serial('/dev/tty.usbserial', 9600)
#ser = serial.Serial('COM7', 9600)
#ser = serial.Serial(0)  # open first serial port
Ncolumn=3
total_tick=64
total_time=30 #[s]
ser=None
#finding an enabled port
for i in xrange(20):
    try:
       ser = serial.Serial(i,115200,timeout=None)
       break
    except:
       print "port COM%d is disabled"%(i+1)
print "Connecting to port: "+ser.name 
#set total recording time
endTime = datetime.datetime.now() + datetime.timedelta(seconds=total_time)

#initial plotting
table=np.zeros(shape=(total_tick,Ncolumn))



#output_server("line_animate",url='http://172.16.155.70:5006/')
output_server("line_animate")
p = figure()
x=table[:,0]
y=table[:,1]
p.line(x, y, color="#3333ee", name="line1")

show(p)

#get renderer from object by tag name
renderer = p.select(dict(name="line1"))
#data from object
ds = renderer[0].data_source

while True:
    if datetime.datetime.now() >= endTime:
        break
    
    try:
        record=re.split(',',ser.readline())
        record = map(int, record)
        #print record
        table=np.roll(table, 1, axis=0)
        table[0,:]=record
        
        ds.data["x"]=table[:,0]
        ds.data["y"]=table[:,1]
        cursession().store_objects(ds)
        #time.sleep(0.01)        
    except:
        pass    
ser.close()
