from django.shortcuts import render
from django.http import HttpResponse
from .models import Weather
from django.shortcuts import render

def append_data(request):

	_nodeid=request.GET['nodeid']
	_temp=request.GET['temp']
	_humi=request.GET['humi']
	_israin=request.GET['israin']

	print "nodeid: %s" % request.GET['nodeid']
	print "temp: %s" % request.GET['temp']
	print "humi: %s" % request.GET['humi']

	w=Weather( 
			nodeid=_nodeid, 
			temp=float(_temp), 
			humi=float(_humi), 
			israin = (_israin =="True") 
		)
	w.temp = w.temp+273
	w.save()
	return HttpResponse("Recieved")

def show_table(request):
	q=Weather.objects.all()
	data=[]
	for r in q:
		data.append(
			{
				'time':r.time, 
				'nodeid':r.nodeid, 
				'temp':r.temp, 
				'humi':r.humi, 
				'israin':r.israin
			})
	return render(request,"show_table.html",{'username':'Einstein', 'data':data})
