from __future__ import unicode_literals

from django.db import models

class Weather(models.Model):
	time=models.DateTimeField(auto_now_add=True)
	nodeid=models.CharField(max_length=3, blank=False)
	temp=models.FloatField(default=0.0)
	humi=models.FloatField(default=0.0)
	israin=models.BooleanField(default=False)

	def __repr__(self):
		return "<nodeid:%s, time:%s>"%(self.nodeid, self.time)