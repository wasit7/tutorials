# -*- coding: utf-8 -*-
"""
Created on Mon Jul 13 22:07:27 2015

@author: Wasit
"""
from turtle import *
def branch(size):
    if size<2:
        return
    else:
        forward(size*0.4)
        init_pos=pos()
        init_head=heading()
        
        left(15)
        forward(size*0.5)
        branch(size*0.5)
        
        penup()
        setpos(init_pos)
        setheading(init_head)
        pendown()
        
        right(20)
        forward(size*0.5)
        branch(size*0.5)
        
        penup()
        setpos(init_pos)
        setheading(init_head)
        pendown()

size=128
penup()
setpos((0,-size))
setheading(90)
pendown()
branch(size)
setpos((0,-size))