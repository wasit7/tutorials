# -*- coding: utf-8 -*-
"""
Created on Sat May 09 17:02:55 2015

@author: Wasit
"""
#rectangle
class rectangle:
    def  __init__(self,pos=(0,0),shape=(0,0)):
        self.pos=pos
        self.shape=shape
    def __del__(self):
        del self.pos
        del self.shape
    def show(self):
        print "pos=%s, shape=%s"%(self.pos,self.shape)
    def getArea(self):
        self.show()
        return self.shape[0]*self.shape[1]
    def circumstance(self):
        return self.secretFuntion(self.shape[0],self.shape[0])
    def secretFuntion(self,w,h):
        return 2*(w+h)
        
if __name__=='main':
    r=rectangle
    r.show()
    print r.circumstance()
