from flask import Flask
from datetime import datetime
app = Flask(__name__)
ti=datetime.now()
i=0
@app.route("/")
def hello():
	global ti,i
	tf=datetime.now()
	dt=tf-ti
	i+=1
	return "%06d_%s"%(i,dt)

if __name__ == "__main__":
    app.run(debug=True, host='0.0.0.0')