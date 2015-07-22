# -*- coding: utf-8 -*-
"""
Created on Wed Jul 22 21:54:48 2015

@author: Wasit
"""

import time
from bokeh import plotting as bp
from bokeh import models as bm
N = 4000

x = 50
y = 50
vx=0
vy=-50
dt=0.1
bp.output_server("scatter_animate")

p = bp.figure()
p.scatter([x], [y], radius=10, fill_color='#770000', 
          fill_alpha=0.6, line_color=None, name="scatter1")
p.x_range = bm.Range1d(-100, 100)
p.y_range = bm.Range1d(-100, 100)
bp.show(p)  # open a browser

renderer = p.select(dict(name="scatter1"))
ds = renderer[0].data_source
while True:
    x=x+dt*vx
    y=y+dt*vy
    vx=vx-dt*x
    vy=vy-dt*y
    ds.data["x"]=[x]
    ds.data["y"]=[y]
    bp.cursession().store_objects(ds)
    #time.sleep(0.005)   