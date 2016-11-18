from django.shortcuts import render
from django.urls import reverse
from django.http import HttpResponseRedirect

from .forms import CarForm,RentForm, CarFormFactory
from .models import Car, Rent, CarModelForm, RentModelForm
from django.forms import modelformset_factory
from django.forms import modelform_factory
from django.views.generic.detail import DetailView
from django.views.generic.list import ListView
from django.views.generic.edit import CreateView
from django.views.generic.edit import UpdateView
from django import forms


def mycar(request):
	if request.method == 'POST':
		form = CarForm(request.POST)
		if form.is_valid():
			#form.save() cannot save
			return HttpResponseRedirect('mycar')
	else:
		form = CarForm()

	return render(request, 'home.html', {'form': form, 'action':''})

class CarDetailView(DetailView):
	model = Car
class CarListView(ListView):
	model = Car
class CarUpdateView(UpdateView):
	model = Car
#	fields = [
#		"BigIntegerField",
#		"BooleanField",
#		"CharField",
#		"DateField",
#		"DateTimeField",
#		"DecimalField",
#		"EmailField",
#		"FileField",
#		"FilePathField",
#		"FloatField",
#		"ForeignKey",
#		"ImageField",
#		"IntegerField",
#		"GenericIPAddressField",
#		"NullBooleanField",
#		"PositiveIntegerField",
#		"PositiveSmallIntegerField",
#		"SlugField",
#		"SmallIntegerField",
#		"TextField",
#		"TimeField",
#		"URLField",
#		"x",
#		"y",
#	]
	def get_success_url(self):
		return reverse('mycar_list')



def mycar_formfactory(request):
	myformfactory=modelform_factory(Car,exclude=([]))
	for i in myformfactory.base_fields:
		myformfactory.base_fields[i].widget.attrs['class']="form-group"
	if request.method == 'POST':
		form = myformfactory(request.POST)
		if form.is_valid():
			form.save()
			return HttpResponseRedirect(reverse('mycar_list'))
	else:
		form = myformfactory()
	return render(request, 'home.html', {'form': form, 'action':''})

def myrent(request):
	if request.method == 'POST':
		form = RentForm(request.POST)
		if form.is_valid():
			print form
			return HttpResponseRedirect('myrent')
	else:
		form = RentForm()

	return render(request, 'home.html', {'form': form, 'action':''})

def mycar_modelform(request):
	if request.method == 'POST':
		form = CarModelForm(request.POST)
		if form.is_valid():
			form.save()
			return HttpResponseRedirect('mycar_modelform')
	else:
		form = CarModelForm()

	return render(request, 'home.html', {'form': form})

def mycar_modelformset(request):
	CarModelFormSet = modelformset_factory(Car, fields=('name',) )
	if request.method == 'POST':
		formset = CarModelFormSet(request.POST)
		if formset.is_valid():
			formset.save()
			return HttpResponseRedirect('mycar_modelformset')
	else:
		formset = CarModelFormSet()
	#reverse('mycar_modelformset')
	return render(request, 'home.html', {'form': formset, 'action':''})
def myrent_modelformset(request):
	RentModelFormSet = modelformset_factory(Rent, fields=('car','customer',) )
	if request.method == 'POST':
		formset = RentModelFormSet(request.POST)
		if formset.is_valid():
			formset.save()
			return HttpResponseRedirect('myrent_modelformset')
	else:
		formset = RentModelFormSet()

	return render(request, 'home.html', {'form': formset, 'action':''})


#######################################crispy

class CarModelFormCreate(CreateView):
	model=Car
	form_class = CarModelForm
	def get_success_url(self):
		return reverse('mycar_list')
	def get_context_data(self, **kwargs):
		context = super(CarModelFormCreate, self).get_context_data(**kwargs)
		context['title'] = 'add a car'
		return context

class CarModelFormEdit(UpdateView):
	model=Car
	form_class = CarModelForm
	def get_success_url(self):
		return reverse('mycar_list')
	def get_context_data(self, **kwargs):
		context = super(CarModelFormEdit, self).get_context_data(**kwargs)
		context['title'] = 'edit a car'
		return context

class CarModelForm(forms.ModelForm):
	class Meta:
		model = Car
		exclude=[]
	def __init__(self, *args, **kwargs):

		print "__init__"
		super(CarModelForm, self).__init__(*args, **kwargs)
		self.helper = FormHelper(self)
		self.helper.layout.append(Submit('save', 'save')) 
		x = Layout(
			TabHolder(
				Tab(
					"BigIntegerField",
					"BooleanField",
					"CharField",
					"DateField",
					"DateTimeField",
					"DecimalField",
					"EmailField",
				),
				Tab(
					"FileField",
					"FilePathField",
					"FloatField",
					"ForeignKey",
					"ImageField",
					"IntegerField",
					"GenericIPAddressField",
				),
				Tab(
					"NullBooleanField",
					"PositiveIntegerField",
					"PositiveSmallIntegerField",
					"SlugField",
					"SmallIntegerField",
					"TextField",
					"TimeField",
					"URLField",
				),
				Tab(
					"x",
					"y",
				),
				Button(
					Submit('submit', 'Submit'),
					HTML(" {% if success %} <p> Successfully submitted </p> {% endif %}")
				)
			)
		)
