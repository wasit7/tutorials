# -*- coding: utf-8 -*-
"""
Created on Mon Jul 13 21:29:15 2015

@author: Wasit
"""
from turtle import *
def leaf(size):
    init_pos=pos()
    init_head=heading()
    forward(size*0.5)
    left(30)
    for i in range(3):
        forward(size*0.5)
        right(120)
    setpos(init_pos)
    setheading(init_head)
    
def branch(size):
    init_pos=pos()
    init_head=heading()
    forward(size*0.75)
    left(45)
    for i in range(3):
        leaf(size*0.25)
        right(45)
    setpos(init_pos)
    setheading(init_head)

def tree(size):
    left(90)
    init_pos=pos()
    init_head=heading()
    forward(size*0.5)
    left(45)
    for i in range(3):
        branch(size*0.5)
        right(45)
    setpos(init_pos)
    setheading(init_head)

color('brown', 'green')
begin_fill()
tree(200)
end_fill()