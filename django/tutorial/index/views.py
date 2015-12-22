#from django.shortcuts import render
from django.http import HttpResponse
#from django.contrib.auth.decorators import login_required

#@login_required(login_url='../login')
def index(request):
    count=request.session.get('count', 0)
    count= count+1
    request.session['count'] = count
    print request.session['username']
    return HttpResponse("count=%d"%count)