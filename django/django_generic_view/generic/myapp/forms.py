from django import forms
from django.forms import Form
from .models import Car, Customer, Rent
from crispy_forms.helper import FormHelper
from crispy_forms.layout import Submit, Layout, Field, Fieldset, Button, HTML
from crispy_forms.bootstrap import FormActions, TabHolder, Tab
class CarForm(Form):
	name=forms.CharField(label='Car', max_length=10)


class CustomerForm(Form):
	name=forms.CharField(max_length=10)


class RentForm(Form):
	car=forms.ModelChoiceField(queryset=Car.objects.all())
	customer=forms.ModelChoiceField(queryset=Customer.objects.all())

class CarFormFactory(Form):
	BigIntegerField = forms.IntegerField()
	BooleanField = forms.BooleanField()
	CharField = forms.CharField(max_length=10,)
	DateField = forms.DateField()
	DateTimeField = forms.DateTimeField()
	DecimalField = forms.DecimalField(max_digits=3, decimal_places=2,)
	EmailField = forms.EmailField(help_text='A valid email address, please.')
	FileField = forms.FileField()
	FilePathField = forms.FilePathField(path='/path')
	FloatField = forms.FloatField()
	ForeignKey = forms.	ModelMultipleChoiceField(queryset=Customer.objects.all(), )
	ImageField = forms.ImageField()
	IntegerField = forms.IntegerField()
	GenericIPAddressField = forms.GenericIPAddressField()
	NullBooleanField = forms.NullBooleanField()
	PositiveIntegerField = forms.IntegerField()
	PositiveSmallIntegerField = forms.IntegerField()
	SlugField = forms.SlugField()
	SmallIntegerField = forms.IntegerField()
	TextField = forms.CharField()
	TimeField = forms.TimeField()
	URLField = forms.URLField()
	x = forms.DecimalField(max_digits=3, decimal_places=2)
	y = forms.DecimalField(max_digits=3, decimal_places=2)


