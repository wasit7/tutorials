from django.shortcuts import render
from django.views.generic.detail import DetailView
from django.views.generic.list import ListView
from django.views.generic.edit import CreateView
from django.views.generic.edit import UpdateView
from .models import Table,Chair
from django import forms
from crispy_forms.helper import FormHelper
from crispy_forms.layout import Submit, Layout, Field, Fieldset, Button, HTML, ButtonHolder,Div
from crispy_forms.bootstrap import FormActions, TabHolder, Tab
#from django.urls import reverse
from django.core.urlresolvers import reverse
class TableDetail(DetailView):
	model = Table
class TableList(ListView):
	model = Table

class TableCreate(CreateView):
	model = Table	
	def get_success_url(self):
		return reverse('table_list')
	def get_form_class(self):
		return TableForm

class TableUpdate(UpdateView):
	model = Table
	def get_success_url(self):
		return reverse('table_list')
	def get_form_class(self):
		return TableForm
	def get_context_data(self, **kwargs):
		context = super(TableUpdate, self).get_context_data(**kwargs)
		context['repr'] = Table.objects.get(id=self.kwargs['pk'])
		print context['repr']
		return context

class TableForm(forms.ModelForm):
	def __init__(self, *args, **kwargs):
		super(TableForm, self).__init__(*args, **kwargs)
		self.helper = FormHelper(self)
		self.helper.form_method = 'post'
		self.helper.form_action = ''
		
		self.helper.layout = Layout(
			HTML("{{repr}}"),
			
			TabHolder(
				Tab("First Tab",
					Field("BigIntegerField", css_class='hello'),
					Field("BooleanField", css_class='hello'),
					Field("CharField", css_class='hello'),
					Field("DateField", css_class='hello'),
					Field("DateTimeField", css_class='hello'),
					Field("DecimalField", css_class='hello'),
					
					
				),
				Tab("Second Tab",
					Div( 
						Div(
							Field("EmailField", css_class='hello'),
							Div( Field("FileField", css_class='hello'), css_class='row col-xs-5'),
							Div(css_class='row col-xs-1'),
							Div( Field("FilePathField", css_class='hello'), css_class='row col-xs-5'),
							Div(css_class='row col-xs-1'),
							Div( Field("FloatField", css_class='hello'), css_class='row col-xs-5'),
							Div(css_class='row col-xs-1'),
							Div( Field("ForeignKey", css_class='hello'), css_class='row col-xs-5'),

							
							css_class='col-xs-12'
						), 
						css_class='row'
					),

					
				),
				Tab("Third Tab",
					"ImageField",
					"IntegerField",
					"GenericIPAddressField",
					"NullBooleanField",
					"PositiveIntegerField",
					
				),
				Tab("Final Tab",
					
					"PositiveSmallIntegerField",
					"SlugField",
					"SmallIntegerField",
					"TextField",
					"TimeField",
					"URLField",
				)
			)
		)
#		self.helper.layout.append( Submit('save', 'save') ) 
#		self.helper.layout.append( Field('x', css_class="black-fields") )

	class Meta:
		model = Table
		exclude=[]
