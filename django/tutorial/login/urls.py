from django.conf.urls import url
from . import views

urlpatterns = [
    url(r'^login$', views._login,'_login'),
    #url(r'^glogin$', views._glogin,name="url_glogin"),
    url(r'^register-by-token/(?P<backend>[^/]+)/$',views.register_by_access_token,'register_by_access_token'),
    url(r'^logout$', views._logout,name="_logout"),
    #url(r'^logout$','django.contrib.auth.views.logout',{'next_page': '/successfully_logged_out/'})
	url(r'^$', views._index,name="_index"),
]