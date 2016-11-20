from rest_framework import serializers
from myapp.models import Table, Chair

class TableSerializer(serializers.ModelSerializer):
	url = serializers.CharField(source='get_absolute_url', read_only=True)

	class Meta:
		model =Table
		#fields=('name','chair','weight',)
		fields = '__all__'
		#depth = 2
    	# = serializers.PrimaryKeyRelatedField(many=True)

class ChairSerializer(serializers.ModelSerializer):
	class Meta:
		model =Chair
		fields=('name',)