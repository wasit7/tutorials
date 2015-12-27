from django.shortcuts import get_object_or_404, render

from django.contrib.auth import authenticate, login, logout
from django.contrib.auth.decorators import login_required
from django.shortcuts import redirect

def _login(request):
    #if request.method == 'GET':
    if request.method == 'POST':
        trigger=request.POST['trigger']
        if trigger=='signin':
            username = request.POST['username']
            password = request.POST['password']
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
        elif trigger=='signout':
            print "signout"
            if 'user_username' in request.session:
                del request.session['user_username']
                print "del uname"
            logout(request)
            
    return render(request,'login.html',{'msg': "Please sign-in"})

@login_required(login_url='url_login')
def _index(request):
    if 'user_username' in request.session:
        uname=request.session['user_username']
    else:
        uname="Anonymous"
    return render(request,'index.html',{'msg': "Hello %s"%uname})
