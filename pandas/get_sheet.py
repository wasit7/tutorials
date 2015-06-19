# -*- coding: utf-8 -*-
"""
Created on Wed May 27 16:22:02 2015

@author: Wasit
"""
import pandas as pd
from matplotlib import pyplot as plt
xl = pd.ExcelFile('AG-RW-CM51-57.xlsx')
#xl.sheet_names  # see all sheet names
table1=xl.parse(xl.sheet_names[0])  # read a specific sheet to DataFrame
table1.convert_objects(convert_numeric=True)
plt.plot(table1.Day[1:500],table1.Sum[1:500])