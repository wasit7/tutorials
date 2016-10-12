from flask import Flask
from flask import render_template
app = Flask(__name__)

@app.route('/<uname>')
def show_entries(uname):
    return render_template('bootstrap.html', name=uname)

# 'ipconfig' to check your pubic ip
# you have to disable firewall or allow incomming connection to the server
if __name__ == '__main__':
    app.run(debug=True)

