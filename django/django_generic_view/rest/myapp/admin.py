from django.contrib import admin
from .models import Table, Chair
from simple_history.admin import SimpleHistoryAdmin

class TableAdmin(admin.ModelAdmin):
	list_display=(
			"id",
			"created",
			"owner",
			"name",
			"weight"
		)
#admin.site.register(Table,TableAdmin)
admin.site.register(Table, SimpleHistoryAdmin)
class ChairAdmin(admin.ModelAdmin):
	list_display=(
			"name",
		)
admin.site.register(Chair,ChairAdmin)



