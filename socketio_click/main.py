from flask import Flask, render_template, request
from flask_socketio import SocketIO, send, emit
from datetime import datetime

app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)

@socketio.on('secret_room')
def handle_s2c(json):
    print 'received message: %s'%json
    socketio.emit('secret_room', json)

@app.route("/click")
def sliderbar():
	return render_template('click.html')

@app.route("/show")
def display():
	return render_template('show.html')

if __name__ == "__main__":
    #app.run(host='0.0.0.0',port=4999,debug=True)
    socketio.run(app)