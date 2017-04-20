#to insert a record, 
#http://localhost:5000/?temp=30&humi=80&israin=1


from flask import Flask,request
import sqlite3
from datetime import datetime

app = Flask(__name__)
global c,conn

@app.route('/', methods=['GET'])
def index():
	timestr=unicode(datetime.now().replace(microsecond=0))
	temp=float(request.args.get('temp'))
	humi=float(request.args.get('humi'))
	israin=int(request.args.get('israin'))
	c.execute("INSERT INTO weather VALUES ('%s',%f,%f,%d)"%(timestr,temp,humi,israin))
	conn.commit()
	for row in c.execute('SELECT * FROM weather ORDER BY time'):
		print row
	return timestr

def createTable(dbfile):
	conn = sqlite3.connect(dbfile)
	c = conn.cursor()
	c.execute('''
		CREATE TABLE IF NOT EXISTS weather (
			time DATETIME, 
			temp real, 
			humi real, 
			israin BOOLEAN
			)
	''')
	conn.close()

def dropTable(dbfile):
	conn = sqlite3.connect(dbfile)
	c = conn.cursor()
	c.execute('''DROP TABLE IF EXISTS weather''')
	conn.close()

if __name__ == '__main__':
	dbfile='db.sqlite'
	#dropTable(dbfile)
	createTable(dbfile)
	conn = sqlite3.connect(dbfile,check_same_thread = False)
	c = conn.cursor()
	app.run(debug=True)