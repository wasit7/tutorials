from flask import Flask, render_template, request, redirect
app = Flask(__name__)

@app.route('/home/<uname>')
def home(uname):
    return render_template('home_bootstrap.html', name=uname)

def valid_login(username, password):
	pwd={'admin':'45687952','wasit':'1234'}
	if pwd.get(username,'') !="":
		return pwd.get(username,'')== password

@app.route('/signin', methods=['GET', 'POST'])
def signin():
	if request.method == 'POST':
		username=request.form.get('username','')
		password=request.form.get('password','')
		print "< username: %s, password: %s >"%(username,password)
		if valid_login(username, password):
			return redirect("home/"+username, code=302)
		else:
			return render_template('form.html',error='Invalid username/password')
	else:
		return render_template('form.html', error='')

# 'ipconfig' to check your pubic ip
# you have to disable firewall or allow incomming connection to the server
if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')

## arguments passing summary
"""
## For URL Query parameter, use request.args
search = request.args.get("search")
page = request.args.get("page")

##For Form input, use request.form
email = request.form.get('email')
password = request.form.get('password')

##For data type application/json, use request.data
data = request.data
dataDict = json.loads(data)
"""