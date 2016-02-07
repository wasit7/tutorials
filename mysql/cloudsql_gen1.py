# -*- coding: utf-8 -*-
"""
Created on Tue Jan 05 12:44:14 2016

@author: Wasit
"""
import MySQLdb
import os
env = os.getenv('SERVER_SOFTWARE')
if (env and env.startswith('Google App Engine/')):
  # Connecting from App Engine
  db = MySQLdb.connect(
    unix_socket='/cloudsql/scituweather:sqldb',
    db='weather',
    user='root')
else:
  # Connecting from an external network.
  # Make sure your network is whitelisted
  db = MySQLdb.connect(
    host='173.194.246.163',
    db='weather',
    port=3306,
    user='root')

cursor=db.cursor()
cursor.execute ("""SELECT * FROM `weather` ORDER BY time DESC LIMIT 0 , 10 ;""")
for row in cursor.fetchall ():
    print row
db.close()
