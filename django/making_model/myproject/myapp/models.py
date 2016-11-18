from __future__ import unicode_literals

from django.db import models

# Create your models here.
from django.contrib.auth.models import User

class Customer(User):
	name=models.CharField(max_length=10)

class Address(models.Model):
	customer=models.ForeignKey('Customer')
	first_line = models.CharField(max_length=10, blank=True, null=True, default='default text')