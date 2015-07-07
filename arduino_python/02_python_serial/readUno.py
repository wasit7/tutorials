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
endTime = datetime.datetime.now() + datetime.timedelta(seconds=60)
while True:
    if datetime.datetime.now() >= endTime:
        break
    m = re.match(r"(?P<tag>\w+) (?P<value>\w+)",ser.readline())
    print m.group('tag')+'\t'+m.group('value')
ser.close()   