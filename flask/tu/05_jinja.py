from flask import Flask
from flask import render_template
app = Flask(__name__)

@app.route('/')
def show_entries():
    return render_template('index.html', name='Wasit')

# 'ipconfig' to check your pubic ip
# you have to disable firewall or allow incomming connection to the server
if __name__ == '__main__':
    app.run(debug=True)

