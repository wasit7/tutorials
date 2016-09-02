from django.shortcuts import render
from models import Questions
from django.shortcuts import render
from models import Questions
def question(request, num=1):
	#print "debug q: %s"%request.GET['q']

	#q=Questions.objects.get(pk=int(request.GET['q']))]
	print "debug num: %s"%num
	q=Questions.objects.get(pk=num)
	_Question=q.question
	_a=q.a
	_b=q.b
	_c=q.c
	_d=q.d

	return render(request, 'QuestionList.html', {
		'Question': _Question,
		'a':_a,
		'b':_b,
		'c':_c,
		'd':_d,
	})
