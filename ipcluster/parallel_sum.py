# -*- coding: utf-8 -*-
"""
Created on Wed Oct 14 17:33:19 2015

@author: Wasit
"""

import numpy as np
from IPython import parallel
c=parallel.Client()
dview=c.direct_view()
dview.block=True

x=np.arange(1e6)

dview.scatter('x',x)
#dview.execute('import numpy as np')
#dview.execute('y=np.sum(x)')
dview.run('kernel.py')
ys=dview.gather('y')
total=np.sum(ys)
print total