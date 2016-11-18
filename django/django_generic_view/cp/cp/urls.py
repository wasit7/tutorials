"""cp URL Configuration

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
from myapp.views import TableDetail, TableList, TableCreate, TableUpdate
urlpatterns = [
    url(r'^admin/', admin.site.urls),
    url(r'^table_detail/(?P<pk>\d+)/', TableDetail.as_view(), name='table_detail'),
    url(r'^table_list/', TableList.as_view(), name='table_list'),
    url(r'^table_update/(?P<pk>\d+)/', TableUpdate.as_view(), name='table_update'),
    url(r'^table_create/', TableCreate.as_view(), name='table_create'),
]
