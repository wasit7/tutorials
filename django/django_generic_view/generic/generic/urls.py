"""generic URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/1.10/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  url(r'^$', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  url(r'^$', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.conf.urls import url, include
    2. Add a URL to urlpatterns:  url(r'^blog/', include('blog.urls'))
"""
from django.conf.urls import url
from django.contrib import admin
from myapp import views
from myapp.views import CarDetailView, CarListView, CarUpdateView, CarModelFormEdit,CarModelFormCreate

admin.site.site_header = 'My admin'

urlpatterns = [
    url(r'^admin/', admin.site.urls),
    url(r'^mycar/', views.mycar, name='mycar'),
    url(r'^myrent/', views.myrent, name='myrent'),
    url(r'^mycar_modelform/', views.mycar_modelform, name='mycar_modelform'),
    url(r'^mycar_formfactory/', views.mycar_formfactory, name='mycar_formfactory'),
    url(r'^mycar_modelformset/', views.mycar_modelformset, name='mycar_modelformset'),
    url(r'^myrent_modelformset/', views.myrent_modelformset, name='myrent_modelformset'),
    url(r'^mycar_detail/(?P<pk>\d+)/', CarDetailView.as_view(), name='mycar_detail'),
    url(r'^mycar_list/', CarListView.as_view(), name='mycar_list'),
    url(r'^mycar_update/(?P<pk>\d+)/', CarModelFormEdit.as_view(), name='mycar_update'),
    url(r'^mycar_create/', CarModelFormCreate.as_view(), name='mycar_create'),
    
]
