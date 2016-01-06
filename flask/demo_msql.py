# -*- coding: utf-8 -*-
"""
Created on Tue Dec 29 18:20:36 2015

@author: Wasit
"""
import MySQLdb
db = MySQLdb.connect(host='104.197.28.33',
                     user='root', 
                     passwd='nosql',
                     db='testdb')
c = db.cursor()

"""
c.execute('''
		CREATE TABLE IF NOT EXISTS weather (
			time DATETIME, 
			temp real, 
			humi real, 
			israin BOOLEAN
			)
	''')
 """
 
c.execute("SELECT VERSION()")
data = c.fetchone()
print "Database version : %s " % data
db.close()