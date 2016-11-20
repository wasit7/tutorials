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
from myapp.models import Table
from django.conf.urls import url, include
from rest_framework import routers, viewsets, serializers


class TableSerializer(serializers.ModelSerializer):
    class Meta:
        model = Table
        fields=('__all__')

class TableViewSet(viewsets.ModelViewSet):
    queryset = Table.objects.all()
    serializer_class = TableSerializer

router = routers.DefaultRouter()
router.register(r'tables', TableViewSet)

urlpatterns = [
    #url(r'^api/', include(router.urls)),
    #url(r'^admin/', admin.site.urls),
    #url(r'^web_table_detail/(?P<pk>\d+)/', TableDetail.as_view(), name='table_detail'),
    #url(r'^web_table_list/', TableList.as_view(), name='table_list'),
    #url(r'^web_table_update/(?P<pk>\d+)/', TableUpdate.as_view(), name='table_update'),
    #url(r'^web_table_create/', TableCreate.as_view(), name='table_create'),
    url(r'^', include(router.urls)),
    url(r'^api-auth/', include('rest_framework.urls', namespace='rest_framework'))
]
