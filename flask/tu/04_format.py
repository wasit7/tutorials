from flask import Flask
app = Flask(__name__)

myhtml = '''
	<!DOCTYPE html>
	<html>
	<head>
		<title>{name}'s Page Title</title>
	</head>
	<body>
		<h1>Hello {name}</h1>
		<p>This is a paragraph.</p>
	</body>
	</html>
'''

@app.route('/')
def hello_world():
    return myhtml.format( name='Wasit' )


# 'ipconfig' to check your pubic ip
# you have to disable firewall or allow incomming connection to the server
if __name__ == '__main__':
    app.run(debug=True)

