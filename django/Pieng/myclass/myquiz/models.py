from __future__ import unicode_literals

from django.db import models

# Create your models here.
class Questions(models.Model):
	# Fields
	CHOICES = (
		('a', 'a.'),('b', 'b.'),('c', 'c.'),('d', 'd.'),
	)
	created = models.DateTimeField(auto_now_add=True, editable=False)
	last_updated = models.DateTimeField(auto_now=True, editable=False)
	question = models.TextField(max_length=100)
	a = models.CharField(max_length=30)
	b = models.CharField(max_length=30)
	c = models.CharField(max_length=30)
	d = models.CharField(max_length=30)
	anwser = models.CharField(max_length=1,choices=CHOICES)
	
	def __unicode__(self):
		return u'%s' % self.question