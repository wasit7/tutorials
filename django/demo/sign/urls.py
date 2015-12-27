from django.conf.urls import url, patterns
from . import views

urlpatterns = patterns(
    url(r'^signin/$', views.signin,'signin'),
    url(r'^register-by-token/(?P<backend>[^/]+)/$',views.register_by_access_token),
)

