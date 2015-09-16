# -*- coding: utf-8 -*-
"""
Created on Tue Sep 15 20:25:53 2015

@author: Wasit
"""
import numpy as np
import pandas as pd
df = pd.read_csv('cs401.csv',delimiter=",",parse_dates=True,
                 infer_datetime_format=True,dayfirst=False,encoding='utf8')

myheader=list(df.columns.values)


advisors={'name':[]}
for ad in df[myheader[7]]:
    if ad not in advisors['name']:
        advisors['name'].append(ad)
advisors['name'].sort()
advisors['normal']=np.zeros(len(advisors['name']))
advisors['special']=np.zeros(len(advisors['name']))
matching={}
for record in df.values:
    for student_id in record[1:3]:
        #if id is not Nan
        if student_id==student_id:
            #if special sudent
            if str(int(student_id))[2:6] =='0965':
                advisors['special'][advisors['name'].index(record[7])]+=1
            else:
                advisors['normal'][advisors['name'].index(record[7])]+=1
writer = pd.ExcelWriter('cs401_out.xlsx')
df.to_excel(writer,'Sheet1')
pd.DataFrame(advisors).to_excel(writer,'advisors')
writer.save()