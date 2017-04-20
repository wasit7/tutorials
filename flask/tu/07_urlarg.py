from flask import Flask
from flask import render_template
from flask import request

app = Flask(__name__)

@app.route('/path/<uname>')
def pass_by_url_path(uname):
    return render_template('home_bootstrap.html', name=uname)

"""
http://localhost:5000/arg/?firstname=Albert&lastname=Einstein
"""
@app.route('/arg/')
def pass_by_url_arg():
	firstname = request.args.get('firstname', '')
	lastname = request.args.get('lastname', '')
	uname = firstname+ " " + lastname
	return render_template('home_bootstrap.html', name=uname)

# 'ipconfig' to check your pubic ip
# you have to disable firewall or allow incomming connection to the server
if __name__ == '__main__':
    app.run(debug=True)

