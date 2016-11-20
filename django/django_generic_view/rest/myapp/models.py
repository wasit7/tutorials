from __future__ import unicode_literals
from django.db import models
from rest_framework import serializers
from simple_history.models import HistoricalRecords

class Table(models.Model):
	name = models.CharField(max_length=10,blank=True, null=True)
	owner = models.ForeignKey('auth.User', related_name='tasks',null=True)
	weight=models.IntegerField(default=0)
	chair = models.ForeignKey('Chair',null=True)
	created = models.DateTimeField(auto_now_add=True)
	history = HistoricalRecords()
	def __unicode__(self):
		return "%s"%(self.name)
	class Meta:
		ordering = ('name',)

class Chair(models.Model):
	name=models.CharField(max_length=10,blank=True, null=True)

	def __unicode__(self):
		return "%s"%(self.name)