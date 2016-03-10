# -*- coding: utf-8 -*-
"""
Created on Tue Sep 15 20:25:53 2015

@author: Wasit
"""
import numpy as np
import pandas as pd
#read questioniar csv file
xl_advisor = pd.ExcelFile("cs401.xlsx")
df_ad = xl_advisor.parse(xl_advisor.sheet_names[0])
df_ad_header=list(df_ad.columns.values)
xl_date = pd.ExcelFile("examdate.xlsx")
df_date = xl_date.parse(xl_date.sheet_names[0])
df_date_header=list(df_date.columns.values)

#Assigned students to advisors
advisors={'name':[]}
for ad in df_ad[df_ad_header[7]]:
    if ad not in advisors['name']:
        advisors['name'].append(ad)
advisors['name'].sort()
advisors['normal']=np.zeros(len(advisors['name']))
advisors['special']=np.zeros(len(advisors['name']))
matching={}
for record in df_ad.values:
    for student_id in record[1:4]:
        #if id is not Nan
        if student_id==student_id:
            #if special sudent
            if str(int(student_id))[2:6] =='0965':
                advisors['special'][advisors['name'].index(record[7])]+=1
            else:
                advisors['normal'][advisors['name'].index(record[7])]+=1



#check available dates for advisors
advisor_date={'name':[]}

for ad in df_ad[df_ad_header[7]]:
    if ad not in advisor_date['name']:
        advisor_date['name'].append(ad)
advisor_date['name'].sort()
for i in range(1,43):
    date_key=df_date_header[i]
    advisor_date["%02d"%i+date_key]=np.empty(len(advisor_date['name']))
    advisor_date["%02d"%i+date_key][:]=np.NAN
df_advisor_date = pd.DataFrame(advisor_date)

for i in range(1,43):
    date_key=df_date_header[i]
    busy_students = df_date.dropna(subset=[date_key])[df_date_header[-1]]
    for student in busy_students:
        if student == student:
            
            ix=np.where(np.sum(df_ad[df_ad_header[1:4]].isin([student]),axis=1))
            the_advisor=df_ad[df_ad_header[7]][ix[0][0]]
            advisor_name=df_advisor_date['name'][df_advisor_date['name'].isin([the_advisor])]
            print "%f, %s"%(student,advisor_name)
            if df_advisor_date[df_advisor_date["name"].isin(advisor_name)]["%02d"%i+date_key].isnull().values.any():
                df_advisor_date.loc[df_advisor_date["name"].isin(advisor_name),"%02d"%i+date_key]="%d"%student
            else:
                df_advisor_date.loc[df_advisor_date["name"].isin(advisor_name),"%02d"%i+date_key]+="\n%d"%student

writer = pd.ExcelWriter('cs401_out.xlsx')
df_ad.to_excel(writer,'Sheet1')
pd.DataFrame(advisors).to_excel(writer,'advisors')
pd.DataFrame(df_advisor_date).to_excel(writer,'date')
writer.save()