from django.conf.urls import url
from . import views

urlpatterns = [
    url(r'^login$', views._login,name="url_login"),
	url(r'^$', views._index,name="url_index"),
]