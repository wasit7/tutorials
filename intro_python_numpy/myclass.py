# -*- coding: utf-8 -*-
"""
Created on Thu Sep 10 17:33:33 2015

@author: Wasit
"""

class Rect:
    def __init__(self, x,y,w,h):
        self.x=x
        self.y=y
        self.w=w
        self.h=h
    def __str__(self):
        return "x:%d y:%d w:%d h:%d"%(self.x,self.y,self.w,self.h)
        
        
if __name__ == "__main__":
    import myclass as mc
    obj=mc.Rect(1,2,3,4)
    print obj
    
    obj2=mc.Rect(6,7,8,9)
    print obj2