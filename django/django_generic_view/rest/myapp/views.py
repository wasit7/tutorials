from rest_framework import viewsets
from .models import Table, Chair
from .serializers import TableSerializer
from rest_framework.permissions import BasePermission, SAFE_METHODS

class IsOwnerOrReadOnly(BasePermission):
	def has_object_permission(self, request, view, obj):
		if request.method in SAFE_METHODS:
			return True
		return obj.owner == request.user

class TableViewSet(viewsets.ModelViewSet):
	queryset = Table.objects.all()
	serializer_class = TableSerializer
	permission_classes=(IsOwnerOrReadOnly,)
	def perform_create(self, serializer):
		serializer.save(owner=self.request.user)