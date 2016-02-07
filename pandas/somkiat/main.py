# -*- coding: utf-8 -*-
"""
Created on Fri Feb 05 10:52:38 2016

@author: Wasit
"""

import pandas as pd
from matplotlib import pyplot as plt
df = pd.read_csv('data/Track1.txt', 
                 skiprows=1,names=['carID','na1','lat','long','na2','date','time'],
                     sep=' | - |,', engine='python')
df[['lat','long']]=df[['lat','long']].astype(float)
df=df[10<df.lat]
df_car0=df[df.carID==df.carID.loc[1] ]
##df_car1=df[df.carID==013950009319790 ]
df_car1=df[df.carID==df.carID.loc[6] ]


fig,ax=plt.subplots()
df_car0.plot( x='lat', y='long',ax=ax);
df_car1.plot( x='lat', y='long',ax=ax);