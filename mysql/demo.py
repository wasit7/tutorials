# -*- coding: utf-8 -*-
"""
Created on Wed Dec 30 22:09:44 2015

@author: Nun
edited by Wasit
"""
from datetime import datetime
import pytz
import random

#if using additinal connector
#import mysql.connector
#conn = mysql.connector.Connect(host='146.148.37.209	',user='root',password='',database='testdb')

#if using >>conda install mysql-python
import MySQLdb
#db = MySQLdb.connect(host= "146.148.37.209",user="root",passwd="",db="weather")
db = MySQLdb.connect(host= "173.194.246.163",user="root",passwd="",db="weather")

c = db.cursor()

#c.execute("""drop table if exists weather""")

#conn.commit()

c.execute("""create table if not exists weather (
        		time DATETIME NOT NULL PRIMARY KEY, 
			temp real NOT NULL, 
			humi real NOT NULL, 
			israin BOOLEAN NOT NULL)""")

cmd="insert into weather values ('%s', %.1f, %.1f, 0)"%(
datetime.now(pytz.timezone('Asia/Bangkok')).isoformat(),
random.randint(30,40),
random.randint(70,100))
print cmd
c.execute(cmd)

db.commit()

c.execute ("""select * from weather""")

for row in c:
        print (row)

c.close()