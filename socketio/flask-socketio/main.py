from flask import Flask, render_template, request
from flask_socketio import SocketIO, send, emit

app = Flask(__name__)
#app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)

@app.route("/")
def hello():
	return render_template('index.html')


@socketio.on('c2s')
def handle_message(message):
	emit('s2c',message, broadcast=True)
	print(message)

if __name__ == "__main__":
    #app.run(host='0.0.0.0', debug=False)
    socketio.run(app)