from flask import Flask, render_template, request
from flask_socketio import SocketIO, send, emit
from datetime import datetime

app = Flask(__name__)
socketio = SocketIO(app)

@app.route("/")
def hello():
	return render_template('index.html',name='Wasit',message='Welcome message')

@app.route("/alarm")
def alarm():
	log= str(datetime.now()) + ": Alarm!!!"
	socketio.emit('s2c', log)
	return "Recieved"

if __name__ == "__main__":
    #app.run(host='0.0.0.0',port=4999,debug=True)
    socketio.run(app)