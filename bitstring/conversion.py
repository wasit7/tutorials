# -*- coding: utf-8 -*-
"""
Created on Wed Sep 30 11:04:28 2015

@author: Wasit
"""

from bitstring import Bits

a = Bits(bin='00000011')
b = Bits(bin='11110000')
print a.int
print b.int
