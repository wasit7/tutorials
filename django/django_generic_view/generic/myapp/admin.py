from django.contrib import admin
from .models import Car, Customer, Rent

class CarAdmin(admin.ModelAdmin):
	exclude=[]
admin.site.register(Car, CarAdmin)

class CustomerAdmin(admin.ModelAdmin):
	list_display=(
			"name",
		)
admin.site.register(Customer,CustomerAdmin)

class RentAdmin(admin.ModelAdmin):
	list_display=(
			"car","customer"
		)
admin.site.register(Rent,RentAdmin)