from flask import Flask,request
import winsound
def alarm():
	winsound.Beep(2300,500)
	winsound.Beep(2400,500)

def alarm2():
	winsound.Beep(1000,100)
	winsound.Beep(2000,100)
	winsound.Beep(1000,100)

app = Flask(__name__)
html="""
counter:%(counter)s ms:%(ms)s
"""
@app.route('/',methods=['GET'])
def index():
	global counter,ms
	counter=request.args.get('cnt')
	ms=request.args.get('ms')
	alarm2()
	return "OK"

@app.route('/read/',methods=['GET'])
def read():
	global counter,A
	return (html % {'counter': counter, 'ms':ms},
		200, {'Refresh': '2;'})

counter=''
ms=''
if __name__ == '__main__':
	app.run(debug=True,host='0.0.0.0')