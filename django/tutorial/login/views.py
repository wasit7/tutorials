from django.shortcuts import get_object_or_404, render

from django.contrib.auth import authenticate, login, logout
from django.contrib.auth.decorators import login_required
from django.shortcuts import redirect

def _login(request):
    #if request.method == 'GET':
    if request.method == 'POST':
        state=request.POST['state']
        if state=='signin':
            username = request.POST['username']
            password = request.POST['password']
            user = authenticate(username=username, password=password)
            if user is not None:
                if user.is_active:
                    login(request, user)
                    request.session['user_username'] = user.username
                    request.session['user_email'] = user.email
                    print "username:%s"%user.username
                    #return render(request,'index.html',{'msg': "Do something"})
                    return redirect('url_index')
                else:
                    msg="Disabled account"
            else:
                msg="Invalid login"
            return render(request,'login.html',{'msg': msg})
        else:
            logout(request)
    return render(request,'login.html',{'msg': "Please sign-in"})

@login_required(login_url='url_login')
def _index(request):
    return render(request,'index.html',{'msg': "Do something"})
