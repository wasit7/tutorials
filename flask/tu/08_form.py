from flask import Flask
from flask import render_template
app = Flask(__name__)

@app.route('/home/<uname>')
def home(uname):
    return render_template('bootstrap.html', name=uname)

@app.route('/form')
def myform():
    return render_template('form.html')

# 'ipconfig' to check your pubic ip
# you have to disable firewall or allow incomming connection to the server
if __name__ == '__main__':
    app.run(debug=True)

