from typing import Any
from django.forms.models import BaseModelForm
from django.http import HttpResponse, HttpResponseNotFound, Http404
from django.shortcuts import render, redirect, get_object_or_404
from django.urls import reverse_lazy
from django.views.generic import ListView, DetailView, CreateView, FormView
from django.contrib.auth.mixins import LoginRequiredMixin
#from django.contrib.auth.decorators import login_required
from django.core.paginator import Paginator
#from django.contrib.auth.forms import UserCreationForm
from django.contrib.auth.views import LoginView
#from django.contrib.auth.forms import AuthenticationForm
from django.contrib.auth import logout, login
from .forms import *
from .models import *
from .utils import *
from rest_framework import generics
from . import serializers
from django.contrib.auth.models import User
# Create your views here.
#def index(request): #HttpRequest
#	return HttpResponse("Страница приложения Women")
#menu=["О сайте", "Добавить статью", "Обратная связь", "Войти"]
#menu=[{'title':"О сайте", 'url_name':'about'}, 
	#{'title':"Добавить статью", 'url_name':'add_page'},
	#{'title':"Обратная связь", 'url_name':'contact'},
	#{'title':"Войти", 'url_name':'login'}]
#def index(request):
	#return render(request, 'women/index.html', {'title':'Главная страница'})
	#posts=Women.objects.all()
	#cats=Category.objects.all()
	#context={'posts':posts, 
		#'cats':cats,
		#'menu':menu, 
		#'title':'Главная страница',
		#'cat_selected':0}
	#return render(request, 'women/index.html', context=context)
#class WomenHome(ListView):
class WomenHome(DataMixin, ListView):
	#paginate_by = 2
	model=Women
	template_name='women/index.html'
	context_object_name='posts'
	#extra_context={'title':'Главная страница'}
	def get_context_data(self, *, object_list=None, **kwargs):
		context=super().get_context_data(**kwargs)
		#context['menu']=menu
		#context['title']='Главная страница'
		#context['cat_selected']=0
		c_def = self.get_user_context(title="Главная страница")
		return dict(list(context.items())+list(c_def.items()))
	def get_queryset(self):
		return Women.objects.filter(is_published=True).select_related('cat')
#@login_required
def about(request):
	#return render(request, 'women/about.html', {'menu':menu, 'title':'О сайте'})
	contact_list=Women.objects.all()
	paginator=Paginator(contact_list,2)
	page_number=request.GET.get('page')
	page_obj=paginator.get_page(page_number)
	return render(request, 'women/about.html', {'page_obj':page_obj, 'menu':menu, 'title':'О сайте'})
#def categories(request):
	#return HttpResponse("<h1>Статьи по категориям</h1>")
#def categories(request, catid):
	#print(request.GET) #http://127.0.0.1:8000/cats/1/?name=Gagarina&type=pop
	#if(request.GET):
		#print(request.GET) #http://127.0.0.1:8000/cats/1
	#if(request.POST):
		#print(request.POST) 
	#return HttpResponse(f"<h1>Статьи по категориям</h1><p>{catid}</p>")
#def archive(request, year):
	#if int(year)>2020:
		#raise Http404() #http://127.0.0.1:8000/archive/2022/
		#return redirect('/', )
		#return redirect('home', permanent=True)
	#return HttpResponse(f"<h1>Архив по годам</h1><p>{year}</p>") #http://127.0.0.1:8000/archive/2020/
def pageNotFound(request, exception):
	return HttpResponseNotFound("<h1>Страница не найдена</h1>")
#def addpage(request):
	#return HttpResponse("Добавление статьи")
	#return render(request, 'women/addpage.html', {'menu':menu, 'title':'Добавление статьи'})
	#form=AddPostForm()
	#if request.method=='POST':
		#form=AddPostForm(request.POST)
		#form=AddPostForm(request.POST, request.FILES)
		#if form.is_valid():
			#print(form.cleaned_data)
			#try:
				#Women.objects.create(**form.cleaned_data)
			#form.save()
			#return redirect('home')
			#except:
			#	form.add_error(None,'Ошибка добавления поста')
	#else:
		#form=AddPostForm()
	#return render(request, 'women/addpage.html', {'form':form,'menu':menu, 'title':'Добавление статьи'})
#class AddPage(CreateView):
class AddPage(LoginRequiredMixin, DataMixin, CreateView):
	form_class = AddPostForm
	template_name = 'women/addpage.html'
	success_url = reverse_lazy('home')
	login_url = reverse_lazy('home')
	raise_exception = True
	def get_context_data(self, *, object_list=None, **kwargs):
		context=super().get_context_data(**kwargs)
		c_def = self.get_user_context(title="Добавление статьи")
		return dict(list(context.items())+list(c_def.items()))
#def contact(request):
#	return HttpResponse("Обратная связь")
#def login(request):
#	return HttpResponse("Авторизация")
#def show_post(request, post_id):
#def show_post(request, post_slug):
	#return HttpResponse(f"Отображение статьи с id = {post_id}")
	#post=get_object_or_404(Women, pk=post_id)
	#post=get_object_or_404(Women, slug=post_slug)
	#context={'post':post,
		#'menu':menu,
		#'title':post.title,
		#'cat_selected':post.cat_id,}
	#return render(request, 'women/post.html', context=context)
class ShowPost(DataMixin, DetailView):
	model=Women
	template_name='women/post.html'
	slug_url_kwarg='post_slug'
	context_object_name='post'
	def get_context_data(self, *, object_list=None, **kwargs):
		context=super().get_context_data(**kwargs)
		c_def = self.get_user_context(title=context['post'])
		return dict(list(context.items())+list(c_def.items()))
#def show_category(request, cat_id):
	#return HttpResponse(f"Отображение категории с id = {cat_id}")
#def show_category(request, cat_id):
	#posts=Women.objects.filter(cat_id=cat_id)
	#cats=Category.objects.all()
	#if len(posts)==0:
		#raise Http404()
	#context={'posts':posts,
		#'cats':cats,
		#'menu':menu,
		#'title':'Главная страница',
		#'cat_selected':cat_id,}
	#return render(request, 'women/index.html', context=context)
class WomenCategory(DataMixin, ListView):
	#paginate_by=2
	model=Women
	template_name='women/index.html'
	context_object_name='posts'
	allow_empty=False
	def get_queryset(self):
		return Women.objects.filter(cat__slug=self.kwargs['cat_slug'], is_published=True).select_related('cat')
	def get_context_data(self, *, object_list=None, **kwargs):
		context=super().get_context_data(**kwargs)
		c = Category.objects.get(slug=self.kwargs['cat_slug'])
		#c_def = self.get_user_context(title='Категория - ' + str(context['posts'][0].cat), cat_selected=context['posts'][0].cat_id)
		c_def = self.get_user_context(title='Категория - ' + str(c.name), cat_selected=c.pk)
		return dict(list(context.items())+list(c_def.items()))
class RegisterUser(DataMixin, CreateView):
	form_class=UserCreationForm
	template_name='women/register.html'
	success_url=reverse_lazy('login')
	def get_context_data(self, *, object_list=None, **kwargs):
		context=super().get_context_data(**kwargs)
		c_def=self.get_user_context(title="Регистрация")
		return dict(list(context.items())+list(c_def.items()))
	def form_valid(self, form):
		user=form.save()
		login(self.request, user)
		return redirect('home')
class LoginUser(DataMixin, LoginView):
	form_class=AuthenticationForm
	template_name='women/login.html'
	def get_context_data(self, *, object_list=None, **kwargs):
		context=super().get_context_data(**kwargs)
		c_def=self.get_user_context(title="Авторизация")
		return dict(list(context.items())+list(c_def.items()))
	def get_success_url(self):
		return reverse_lazy('home')	
def logout_user(request):
	logout(request)
	return redirect('login')
class ContactFormView(DataMixin, FormView):
    form_class = ContactForm
    template_name = 'women/contact.html'
    success_url = reverse_lazy('home')
    def get_context_data(self, *, object_list=None, **kwargs):
        context = super().get_context_data(**kwargs)
        c_def = self.get_user_context(title="Обратная связь")
        return dict(list(context.items()) + list(c_def.items()))
    def form_valid(self, form):
        print(form.cleaned_data)
        return redirect('home')
class UserList(generics.ListAPIView):
    queryset = User.objects.all()
    serializer_class = serializers.UserSerializer
class UserDetail(generics.RetrieveAPIView):
    queryset = User.objects.all()
    serializer_class = serializers.UserSerializer