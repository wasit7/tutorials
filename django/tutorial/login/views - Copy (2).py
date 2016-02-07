from django.shortcuts import get_object_or_404, render

from django.contrib.auth import authenticate, login, logout
from django.contrib.auth.decorators import login_required
from django.shortcuts import redirect
from social.apps.django_app.utils import psa
from .models import OauthProvider

def _login(request):
    #if request.method == 'GET':
    if request.method == 'POST' and 'username' in request.POST:
        username = request.POST['username']
        password = request.POST['password']
        print "password: %s"%password
        user = authenticate(username=username, password=password)
        if user is not None:
            if user.is_active:
                login(request, user)
                request.session['user_username'] = user.username
                print "username:%s"%user.username
                #return render(request,'index.html',{'msg': "Do something"})
                return redirect('url_index')
            else:
                msg="Disabled account"
        else:
            msg="Invalid login"
        return render(request,'login.html',{'msg': msg})   
    return render(request,'login.html',{'msg': "Please sign-in"})

@psa('social:complete')
def register_by_access_token(request, backend):
    # This view expects an access_token GET parameter, if it's needed,
    # request.backend and request.strategy will be loaded with the current
    # backend and strategy.
    token = request.GET.get('access_token')
    user = request.backend.do_auth(request.GET.get('access_token'))
    if user:
        login(request, user)
        return 'OK'
    else:
        return 'ERROR'

def _logout(request):
    if request.method == 'POST':
        print "signout"
        if 'user_username' in request.session:
            del request.session['user_username']
            print "del uname"
        logout(request)
    return render(request,'login.html',{'msg': "Please sign-in"})

@login_required(login_url='url_login')
def _index(request):
    print "_index user:%s"%request.user.username
    if 'user_username' in request.session:
        uname=request.session['user_username']
    else:
        uname="Anonymous"
    return render(request,'index.html',{'msg': "Hello %s"%uname})
