from flask import Flask, render_template, request
from flask_socketio import SocketIO, send, emit
from datetime import datetime

app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)

@socketio.on('c2s')
def handle_s2c(json):
    print 'received message: %s'%json
    socketio.emit('s2c', json)

@app.route("/sliderbar")
def sliderbar():
	return render_template('sliderbar.html')

@app.route("/display")
def display():
	return render_template('index.html')

@app.route("/graph")
def graph():
	return render_template('d3_graph.html')

@app.route("/drag")
def drag():
	return render_template('d3_drag.html')

@app.route("/alarm")
def alarm():
	log= str(datetime.now()) + ": Alarm!!!"
	socketio.emit('s2c', log)
	return "Recieved"

if __name__ == "__main__":
    #app.run(host='0.0.0.0',port=4999,debug=True)
    socketio.run(app)