# -*- coding: utf-8 -*-
"""
Created on Tue Jul 07 13:58:49 2015

@author: Wasit
"""

import serial
import re
import datetime
#ser = serial.Serial('/dev/tty.usbserial', 9600)
#ser = serial.Serial('COM7', 9600)
#ser = serial.Serial(0)  # open first serial port
ser=None
for i in xrange(10):
    try:
       ser = serial.Serial(i)
       break
    except:
       print "port COM%d is disabled"%(i+1)
print "Connecting to port: "+ser.name 
endTime = datetime.datetime.now() + datetime.timedelta(seconds=5)
while True:
    if datetime.datetime.now() >= endTime:
        break
    record=re.split(',',ser.readline())
    record = map(int, record)
    print record
ser.close()