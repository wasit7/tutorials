from django.contrib import admin
from models import Questions
class QuestionsAdmin(admin.ModelAdmin):
    fields = ('question','a','b','c','d','anwser')
    list_filter=('question','a','b','c','d','anwser')
    list_display=('question','a','b','c','d','anwser')

admin.site.register(Questions, QuestionsAdmin)