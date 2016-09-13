import os
'''
import sys
sys.path.insert(1,
	os.path.join(os.path.abspath('.'),'lib')
	)
'''

from flask import Flask,request,Response
from datetime import datetime
import pytz
import random
import MySQLdb
from flask import render_template
import json

app = Flask(__name__,static_url_path='/static')
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
	  # old db 173.194.246.163
	  db = MySQLdb.connect(
	    host='173.194.227.84',
	    port=3306,
	    db='weather',
	    user='root')
	return db

@app.route('/',methods=['GET'])
def index():
	global tz
	if 'israin' in request.args:
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
	else:
		try:
			db = connectSQL()
			cursor=db.cursor()
			cursor.execute ("""SELECT * FROM `weather` ORDER BY time DESC LIMIT 0 , 1 ;""")
			row_w =cursor.fetchall ()[0]
			cursor.execute ("""SELECT * FROM `forecast` ORDER BY time DESC LIMIT 0 , 1 ;""")
			row_f =cursor.fetchall ()[0]
			print ">>%s"%row_f[1]
			data=json.loads(row_f[1])
		finally:
			pass
		return render_template('forecast.html', 
				time=datetime.now(pytz.timezone('Asia/Bangkok')).isoformat(),
				temp=row_w[1],
				humi=row_w[2],
				israin=str(row_w[3]==1),
				forecast=data,
				debug=json.loads(row_f[1])
			)

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
		cursor.execute ("""SELECT * FROM `weather` ORDER BY time DESC LIMIT 0 , 100 ;""")
		for row in cursor.fetchall ():
			html+="<tr><td>%s</td><td>%.1f</td><td>%.1f</td><td>%d</tr>"%(row)
		html+="""</table></body></html>"""
		db.close()
	finally:
		pass
	return (html,
		200, {'Refresh': '5;'})

@app.route('/data.csv',methods=['GET'])
def data():
	global c,tz
	csv='''datetime,temperature,humidity,israin\n'''
	try:
		db = connectSQL()
		cursor=db.cursor()
		cursor.execute ("""SELECT * FROM `weather` ORDER BY time DESC LIMIT 0 , 6000 ;""")
		for row in cursor.fetchall ():
			csv+='''"%s","%.1f","%.1f","%d"\n'''%(
				"{:%y %m %d %H:%M:%S}".format(row[0]),
				row[1],row[2],row[3]
			)
		db.close()
	finally:
		pass
	return Response(csv,mimetype="text/csv")

@app.route('/graph')
def graph():
	return render_template('graph.html', name="Wasit")

@app.route('/forecast')
def forecast():
	try:
		db = connectSQL()
		cursor=db.cursor()
		cursor.execute ("""SELECT * FROM `weather` ORDER BY time DESC LIMIT 0 , 1 ;""")
		row =cursor.fetchall ()[0]
	finally:
		pass
	return render_template('forecast.html', 
		time=datetime.now(pytz.timezone('Asia/Bangkok')).isoformat(),
		temp=row[1],
		humi=row[2],
		israin=str(row[3]==1))

@app.route('/<x>')
def condition(x=1):
	html= x+'.html'
	return render_template(html)

@app.route('/contact')
def contact():
	return render_template('contact.html')
def createTable():
	c.execute("""create table if not exists weather (
        	time DATETIME NOT NULL PRIMARY KEY, 
			temp real NOT NULL, 
			humi real NOT NULL, 
			israin BOOLEAN NOT NULL)""")
	#create table if not exists forecast (time datetime not null primary key, forecast varchar(128) not null);
@app.route('/debug')
def debug():
	return ""+str(pd.__version__)
#conn = MySQLdb.connect(host= "146.148.37.209",user="root",passwd="",db="weather")
#c = conn.cursor()
#tz=pytz.timezone('Asia/Bangkok')
if __name__ == '__main__':
#	app.run(debug=True,host='0.0.0.0')
	app.run(host='0.0.0.0')
#	app.run()