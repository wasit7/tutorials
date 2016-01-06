import os
'''
import sys
sys.path.insert(1,
	os.path.join(os.path.abspath('.'),'lib')
	)
'''

from flask import Flask,request
from datetime import datetime
import pytz
import random
import MySQLdb

app = Flask(__name__)
def connectSQL():
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
	    port=3306,
	    db='weather',
	    user='root')
	return db

@app.route('/',methods=['GET'])
def index():
	global tz
	temp=float(request.args.get('temp'))
	humi=float(request.args.get('humi'))
	israin=int(request.args.get('israin'))
	cmd="insert into weather values ('%s', %.1f, %.1f, %d)"%(
	datetime.now(pytz.timezone('Asia/Bangkok')).isoformat(),
	temp,humi,israin)
	try:
		db = connectSQL()
		cursor=db.cursor()
		cursor.execute(cmd)
		db.commit()
		db.close()
	finally:
		pass
	return "OK"

@app.route('/read/',methods=['GET'])
def read():
	global c,tz
	html="""
	<style>
	table tr:nth-child(even) {
	    background-color: #eee;
	}
	table tr:nth-child(odd) {
	   background-color:#fff;
	}
	table th	{
	    background-color: grey;
	    color: white;
	}
	</style>
	<html><body><table>
	<tr><th>Time</th><th>Temperature</th><th>Humidity</th><th>IsRain</th></tr>"""
	try:
		db = connectSQL()
		cursor=db.cursor()
		cursor.execute ("""select * from weather ORDER BY time DESC""")
		for row in cursor.fetchall ():
			html+="<tr><td>%s</td><td>%.1f</td><td>%.1f</td><td>%d</tr>"%(row)
		html+="""</table></body></html>"""
		db.close()
	finally:
		pass
	return (html,
		200, {'Refresh': '5;'})


def createTable():
	c.execute("""create table if not exists weather (
        	time DATETIME NOT NULL PRIMARY KEY, 
			temp real NOT NULL, 
			humi real NOT NULL, 
			israin BOOLEAN NOT NULL)""")

#conn = MySQLdb.connect(host= "146.148.37.209",user="root",passwd="",db="weather")
#c = conn.cursor()
#tz=pytz.timezone('Asia/Bangkok')
if __name__ == '__main__':
#	app.run(debug=True,host='0.0.0.0')
	app.run(host='0.0.0.0')
#	app.run()