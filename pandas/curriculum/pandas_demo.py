# -*- coding: utf-8 -*-
"""
Created on Wed Sep 16 17:09:51 2015

@author: Wasit
"""

import pandas as pd
#from matplotlib import pyplot as plt
xl = pd.ExcelFile('cs401.xlsx')
#xl.sheet_names  # see all sheet names
df=xl.parse(xl.sheet_names[0])  # read a specific sheet to DataFrame
#table1.convert_objects(convert_numeric=True)
#plt.plot(table1.Day[1:500],table1.Sum[1:500])

headers = list(df.columns.values)
advisors = { "name" : []}

for name in df[headers[7]]:
    if not name in advisors["name"]:
        advisors["name"].append(name)

print advisors["name"]
print len(advisors["name"])

df_out = pd.DataFrame(advisors)
writer = pd.ExcelWriter("output.xlsx")
df_out.to_excel(writer, "sheetname")

df.index = df[headers[7]]
dfstack=pd.DataFrame(df.stack())
dfstack.to_excel(writer, "stack")

writer.save()

