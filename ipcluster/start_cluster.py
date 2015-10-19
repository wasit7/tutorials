# -*- coding: utf-8 -*-
"""
Created on Wed Oct 14 17:10:12 2015

@author: Wasit
"""
from IPython import parallel
c=parallel.Client()
dview=c.direct_view()
dview.block=True

