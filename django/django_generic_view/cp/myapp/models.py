from __future__ import unicode_literals
from django.db import models
from rest_framework import serializers

class Table(models.Model):
	BigIntegerField = models.BigIntegerField(blank=True, null=True)
	BooleanField = models.BooleanField(default=True)
	CharField = models.CharField(max_length=10,blank=True, null=True)
	DateField = models.DateField(blank=True, null=True)
	DateTimeField = models.DateTimeField(blank=True, null=True)
	DecimalField = models.DecimalField(max_digits=3, decimal_places=2,blank=True, null=True)
	EmailField = models.EmailField(blank=True, null=True)
	FileField = models.FileField(blank=True, null=True)
	FilePathField = models.FilePathField(blank=True, null=True)
	FloatField = models.FloatField(blank=True, null=True)
	ForeignKey = models.ForeignKey('Chair', on_delete=models.CASCADE, blank=True, null=True)
	ImageField = models.ImageField(blank=True, null=True)
	IntegerField = models.IntegerField(blank=True, null=True)
	GenericIPAddressField = models.GenericIPAddressField(blank=True, null=True)
	NullBooleanField = models.NullBooleanField(blank=True, null=True)
	PositiveIntegerField = models.PositiveIntegerField(blank=True, null=True)
	PositiveSmallIntegerField = models.PositiveSmallIntegerField(blank=True, null=True)
	SlugField = models.SlugField(blank=True, null=True)
	SmallIntegerField = models.SmallIntegerField(blank=True, null=True)
	TextField = models.TextField(blank=True, null=True)
	TimeField = models.TimeField(blank=True, null=True)
	URLField = models.URLField(blank=True, null=True)
	x = models.DecimalField(max_digits=3, decimal_places=2)
	y = models.DecimalField(max_digits=3, decimal_places=2)

	def __unicode__(self):
		return "%s %s %s"%(self.id, self.x, self.y)


class Chair(models.Model):
	name=models.CharField(max_length=10,blank=True, null=True)