from django.conf.urls import url
from rest_framework import routers
from .views import TableViewSet

router = routers.DefaultRouter()
router.register(r'tables', TableViewSet)

urlpatterns = router.urls