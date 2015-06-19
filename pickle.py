# -*- coding: utf-8 -*-
"""
Created on Wed May 06 11:07:57 2015

@author: Wasit
"""

import pickle
class rectangular():
    def __init__(self,x,y,width,height):
        self.x=x
        self.y=y
        self.width=width
        self.height=height
    def __str__(self):
        return "x:%.2f,y:%.2f,width:%.2f,hieght:%.2f"\
        %(self.x,self.y,self.width,self.height)

if __name__ == '__main__':
    rec=rectangular(2,3,4,5)
    pickleFile = open('rec.pic', 'wb')
    pickle.dump(rec, pickleFile, pickle.HIGHEST_PROTOCOL)
    pickleFile.close()