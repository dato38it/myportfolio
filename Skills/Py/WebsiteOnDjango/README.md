# Website on Django
<p>
    <strong>Decision:</strong><br>
    $ mkdir djsite<br>
    $ cd djsite/<br>
    $ python3 -m venv venv<br>
    $ source venv/bin/activate<br>
    $ pip install django<br>
    $ django-admin startproject coolsite<br>
    $ cd coolsite/<br>
    $ python manage.py runserver<br>
    $ python manage.py runserver 4000<br>
    $ python manage.py startapp women<br>
    $ vim coolsite/settings.py<br>
    $ cat coolsite/settings.py<br>
    ...<br>
    INSTALLED_APPS = [<br>
    &nbsp;&nbsp;'django.contrib.admin',<br>
    &nbsp;&nbsp;'django.contrib.auth',<br>
    &nbsp;&nbsp;'django.contrib.contenttypes',<br>
    &nbsp;&nbsp;'django.contrib.sessions',<br>
    &nbsp;&nbsp;'django.contrib.messages',<br>
    &nbsp;&nbsp;'django.contrib.staticfiles',<br>
    &nbsp;&nbsp;'women.apps.WomenConfig'<br>
    ]<br>
    ...<br>
    $ vim women/views.py<br>
    $ cat women/views.py<br>
    from django.http import HttpResponse<br>
    from django.shortcuts import render<br>
    # Create your views here.<br>
    def index(request): #HttpRequest<br>
    return HttpResponse("Страница приложения Women")<br>
    def categories(request): #HttpRequest<br>
    return HttpResponse("&lt;h1&gt;Статьи по категориям&lt;/h1&gt;")<br>
    $ vim coolsite/urls.py<br>
    $ cat coolsite/urls.py<br>
    ...<br>
    from django.contrib import admin<br>
    from django.urls import path, include<br>
    #from women.views import index<br>
    from women.views import *<br>
    urlpatterns = [<br>
    &nbsp;&nbsp;path('admin/', admin.site.urls),<br>
    &nbsp;&nbsp;#path('women/', index), #http://127.0.0.1:8000/women/<br>
    &nbsp;&nbsp;#path('', index), #http://127.0.0.1:8000/<br>
    &nbsp;&nbsp;#path('cats/', categories), #http://127.0.0.1:8000/cats/<br>
    &nbsp;&nbsp;path('women/', include('women.urls')), #http://127.0.0.1:8000/women/<br>
    ]<br>
    $ touch women/urls.py<br>
    $ vim women/urls.py<br>
    $ cat women/urls.py<br>
    from django.urls import path<br>
    from .views import *<br>
    urlpatterns = [<br>
    path('', index), #http://127.0.0.1:8000/women/<br>
    path('cats/', categories), #http://127.0.0.1:8000/women/cats/<br>
    ]<br>
    $ python manage.py runserver<br>
    $ vim coolsite/urls.py<br>
    $ cat coolsite/urls.py<br>
    ...<br>
    urlpatterns = [<br>
    &nbsp;&nbsp;path('admin/', admin.site.urls),<br>
    &nbsp;&nbsp;#path('women/', index), #http://127.0.0.1:8000/women/<br>
    &nbsp;&nbsp;#path('', index), #http://127.0.0.1:8000/<br>
    &nbsp;&nbsp;#path('cats/', categories), #http://127.0.0.1:8000/cats/<br>
    &nbsp;&nbsp;#path('women/', include('women.urls')), #http://127.0.0.1:8000/women/<br>
    &nbsp;&nbsp;path('', include('women.urls')), #http://127.0.0.1:8000/women/<br>
    ]<br>
    handler404 = pageNotFound<br>
    $ vim women/urls.py<br>
    $ cat women/urls.py<br>
    from django.urls import path, re_path<br>
    from .views import *<br>
    urlpatterns = [<br>
    #path('', index), #http://127.0.0.1:8000/women/<br>
    #path('home/', index, name='home'), #http://127.0.0.1:8000/<br>
    path('', index, name='home'), #http://127.0.0.1:8000/<br>
    #path('cats/', categories), #http://127.0.0.1:8000/women/cats/<br>
    #path('cats/', categories), #http://127.0.0.1:8000/cats/<br>
    path('cats/&lt;int:catid&gt;/', categories), #http://127.0.0.1:8000/cats/1/<br>
    re_path(r'^archive/(?P&lt;year&gt;[0-9]{4})/', archive), #http://127.0.0.1:8000/archive/2020/<br>
    ]<br>
    $ vim women/views.py<br>
    $ cat women/views.py<br>
    from django.http import HttpResponse, HttpResponseNotFound, Http404<br>
    from django.shortcuts import render, redirect<br>
    # Create your views here.<br>
    def index(request): #HttpRequest<br>
    return HttpResponse("Страница приложения Women")<br>
    #def categories(request):<br>
    #return HttpResponse("&lt;h1&gt;Статьи по категориям&lt;/h1&gt;")<br>
    def categories(request, catid):<br>
    #print(request.GET) #http://127.0.0.1:8000/cats/1/?name=Gagarina&amp;type=pop<br>
    #if(request.GET):<br>
    #print(request.GET) #http://127.0.0.1:8000/cats/1<br>
    if(request.POST):<br>
    print(request.POST)&nbsp;<br>
    return HttpResponse(f"&lt;h1&gt;Статьи по категориям&lt;/h1&gt;&lt;p&gt;{catid}&lt;/p&gt;")<br>
    def archive(request, year):<br>
    if int(year)&gt;2020:<br>
    #raise Http404() #http://127.0.0.1:8000/archive/2022/<br>
    #return redirect('/', )<br>
    return redirect('home', permanent=True)<br>
    return HttpResponse(f"&lt;h1&gt;Архив по годам&lt;/h1&gt;&lt;p&gt;{year}&lt;/p&gt;") #http://127.0.0.1:8000/archive/2020/<br>
    def pageNotFound(request, exception):<br>
    return HttpResponseNotFound("&lt;h1&gt;Страница не найдена&lt;/h1&gt;")<br>
    $ vim coolsite/settings.py<br>
    $ cat coolsite/settings.py<br>
    ...<br>
    #DEBUG = True<br>
    DEBUG = False<br>
    #ALLOWED_HOSTS = []<br>
    ALLOWED_HOSTS = ['127.0.0.1']<br>
    ...<br>
    $ python manage.py runserver<br>
    $ vim women/models.py<br>
    $ cat women/models.py<br>
    from django.db import models<br>
    # Create your models here.<br>
    class Women(models.Model):<br>
    """docstring for Women"""<br>
    title=models.CharField(max_length=255)<br>
    content=models.TextField(blank=True)<br>
    photo=models.ImageField(upload_to="photos/%Y/%m/%d/")<br>
    time_create=models.DateTimeField(auto_now_add=True)<br>
    time_update=models.DateTimeField(auto_now=True)<br>
    is_published=models.BooleanField(default=True)<br>
    $ vim coolsite/settings.py<br>
    $ cat coolsite/settings.py<br>
    import os<br>
    from pathlib import Path<br>
    ...<br>
    DEBUG = True<br>
    #DEBUG = False<br>
    #ALLOWED_HOSTS = []<br>
    ...<br>
    DEFAULT_AUTO_FIELD = 'django.db.models.BigAutoField'<br>
    MEDIA_ROOT = os.path.join(BASE_DIR, 'media')<br>
    MEDIA_URL = '/media/'<br>
    $ vim coolsite/urls.py<br>
    $ cat coolsite/urls.py<br>
    from django.conf.urls.static import static<br>
    from django.contrib import admin<br>
    from coolsite import settings<br>
    from django.urls import path, include<br>
    #from women.views import index<br>
    from women.views import *<br>
    ...<br>
    if settings.DEBUG:<br>
    &nbsp;&nbsp;urlpatterns += static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)<br>
    handler404 = pageNotFound<br>
    $ python manage.py makemigrations<br>
    $ python manage.py sqlmigrate women 0001<br>
    $ python manage.py migrate<br>
    $ sqlite3 db.sqlite3<br>
    sqlite&gt; SELECT * FROM sqlite_master where type='table';<br>
    $ python manage.py shell<br>
    &gt;&gt;&gt; from women.models import Women<br>
    &gt;&gt;&gt; Women(title='Anjeline Joli', content='Биография Anjeline Joli')<br>
    &gt;&gt;&gt; w1=_<br>
    &gt;&gt;&gt; w1<br>
    &gt;&gt;&gt; w1.save()<br>
    &gt;&gt;&gt; w1<br>
    &gt;&gt;&gt; w1.id<br>
    &gt;&gt;&gt; w1.title<br>
    &gt;&gt;&gt; w1.time_create<br>
    &gt;&gt;&gt; w1.pk<br>
    &gt;&gt;&gt; from django.db import connection<br>
    &gt;&gt;&gt; connection.queries<br>
    &gt;&gt;&gt; w2.save()<br>
    &gt;&gt;&gt; connection.queries<br>
    &gt;&gt;&gt; w3=Women()<br>
    &gt;&gt;&gt; w3.title='Juli Roberts'<br>
    &gt;&gt;&gt; w3.content='Биография Juli Roberts'<br>
    &gt;&gt;&gt; w3.save()<br>
    &gt;&gt;&gt; connection.queries<br>
    &gt;&gt;&gt; # objects<br>
    &gt;&gt;&gt; Women.objects<br>
    &gt;&gt;&gt; w4=Women.objects.create(title='Uma Turman', content='Биография Uma Turman')<br>
    &gt;&gt;&gt; w4<br>
    &gt;&gt;&gt; Women.objects.create(title='Kira Nightly', content='Биография Kira Nightly')<br>
    &gt;&gt;&gt; Women.objects.all()<br>
    &gt;&gt;&gt; exit()<br>
    $ vim women/models.py<br>
    $ cat women/models.py<br>
    ...<br>
    def __str__(self):<br>
    return self.title<br>
    $ python manage.py shell<br>
    &gt;&gt;&gt; from women.models import Women<br>
    &gt;&gt;&gt; Women.objects.all()<br>
    &gt;&gt;&gt; w=_<br>
    &gt;&gt;&gt; w[0]<br>
    &gt;&gt;&gt; w[1]<br>
    &gt;&gt;&gt; w[0].title<br>
    &gt;&gt;&gt; len(w)<br>
    &gt;&gt;&gt; for wi in w:<br>
    ...&nbsp;&nbsp; print(wi.title)<br>
    &gt;&gt;&gt; Women.objects.filter(title='Enn Hatay')<br>
    &gt;&gt;&gt; from django.db import connection<br>
    &gt;&gt;&gt; connection.queries<br>
    &gt;&gt;&gt; Women.objects.filter(pk=2)<br>
    &gt;&gt;&gt; Women.objects.filter(pk__gte=2)<br>
    &gt;&gt;&gt; Women.objects.exclude(pk=2)<br>
    &gt;&gt;&gt; Women.objects.get(pk=2)<br>
    &gt;&gt;&gt; Women.objects.filter(pk__lte=4).order_by('title')<br>
    &gt;&gt;&gt; Women.objects.order_by('title')<br>
    &gt;&gt;&gt; Women.objects.order_by('time_update')<br>
    &gt;&gt;&gt; Women.objects.order_by('-time_update')<br>
    &gt;&gt;&gt; wu=Women.objects.get(pk=2)<br>
    &gt;&gt;&gt; wu.title='Margo Robbi'<br>
    &gt;&gt;&gt; wu.content='Биография Margo Robbi'<br>
    &gt;&gt;&gt; wu.save()<br>
    &gt;&gt;&gt; connection.queries<br>
    &gt;&gt;&gt; wd=Women.objects.filter(pk__gte=4)<br>
    &gt;&gt;&gt; wd<br>
    &gt;&gt;&gt; wd.delete()<br>
    &gt;&gt;&gt; exit()<br>
    $ mkdir women/templates<br>
    $ mkdir women/templates/women<br>
    $ touch women/templates/women/index.html<br>
    $ vim women/templates/women/index.html<br>
    $ cat women/templates/women/index.html<br>
    {% extends 'women/base.html' %}<br>
    {% block content %}<br>
    &lt;h1&gt;{{title}}&lt;/h1&gt;<br>
    &lt;!--&lt;p&gt;Содержимое главной страницы&lt;/p&gt;--&gt;<br>
    &lt;ul&gt;<br>
    {% for p in posts %}<br>
    &lt;li&gt;<br>
    &lt;h2&gt;{{p.title}}&lt;/h2&gt;<br>
    &lt;p&gt;{{p.content}}&lt;/p&gt;<br>
    &lt;hr&gt;<br>
    &lt;/li&gt;<br>
    {% endfor %}<br>
    &lt;/ul&gt;<br>
    {% endblock %}<br>
    $ touch women/templates/women/about.html<br>
    $ vim women/templates/women/about.html<br>
    $ cat women/templates/women/about.html<br>
    {% extends 'women/base.html' %}<br>
    {% block content %}<br>
    &lt;h1&gt;{{title}}&lt;/h1&gt;<br>
    &lt;p&gt;Содержимое главной страницы&lt;/p&gt;<br>
    {% endblock %}<br>
    $ touch women/templates/women/base.html<br>
    $ vim women/templates/women/base.html<br>
    $ cat women/templates/women/base.html<br>
    &lt;!DOCTYPE html&gt;<br>
    &lt;html lang="en"&gt;&lt;head&gt;&lt;meta charset="utf-8"&gt;<br>
    &lt;title&gt;{{ title }}&lt;/title&gt;<br>
    &lt;/head&gt;&lt;body&gt;<br>
    {% block mainmenu %}<br>
    &lt;ul&gt;<br>
    {% for m in menu %}<br>
    &lt;li&gt;{{m}}&lt;/li&gt;<br>
    {% endfor %}<br>
    &lt;/ul&gt;<br>
    {% endblock mainmenu %}<br>
    {% block content %}<br>
    {% endblock %}<br>
    &lt;/ul&gt;<br>
    &lt;/body&gt;&lt;/html&gt;<br>
    $ vim women/views.py<br>
    $ cat women/views.py<br>
    from django.http import HttpResponse, HttpResponseNotFound, Http404<br>
    from django.shortcuts import render, redirect<br>
    from .models import *<br>
    # Create your views here.<br>
    #def index(request): #HttpRequest<br>
    #return HttpResponse("Страница приложения Women")<br>
    menu=["О сайте", "Добавить статью", "Обратная связь", "Войти"]<br>
    def index(request):<br>
    #return render(request, 'women/index.html', {'title':'Главная страница'})<br>
    posts=Women.objects.all()<br>
    return render(request, 'women/index.html', {'posts':posts, 'menu':menu, 'title':'Главная страница'})<br>
    def about(request):<br>
    return render(request, 'women/about.html', {'menu':menu, 'title':'О сайте'})<br>
    ...<br>
    $ vim women/urls.py<br>
    $ cat women/urls.py<br>
    ...<br>
    urlpatterns = [<br>
    #path('', index), #http://127.0.0.1:8000/women/<br>
    #path('home/', index, name='home'), #http://127.0.0.1:8000/<br>
    path('', index, name='home'), #http://127.0.0.1:8000/<br>
    #path('cats/', categories), #http://127.0.0.1:8000/women/cats/<br>
    #path('cats/', categories), #http://127.0.0.1:8000/cats/<br>
    #path('cats/&lt;int:catid&gt;/', categories), #http://127.0.0.1:8000/cats/1/<br>
    #re_path(r'^archive/(?P&lt;year&gt;[0-9]{4})/', archive), #http://127.0.0.1:8000/archive/2020/<br>
    path('about/', about, name='about'), #http://127.0.0.1:8000/<br>
    ]<br>
    $ python manage.py runserver<br>
    $ mkdir women/static<br>
    $ mkdir women/static/women<br>
    $ mkdir women/static/women/css<br>
    $ touch women/static/women/css/style.css<br>
    html, body {<br>
    font-family: 'Arial';<br>
    margin: 0;<br>
    padding: 0;<br>
    height: 100%;<br>
    width: 100%;<br>
    color: #444;<br>
    }<br>
    a {<br>
    color: #0059b2;<br>
    text-decoration: none;<br>
    }<br>
    a:hover {<br>
    color: #CC0000;<br>
    text-decoration: underline;<br>
    }<br>
    img {max-width: 600px; height: auto;}<br>
    img.img-article-left {<br>
    max-width: 300px;<br>
    height: auto;<br>
    float: left;<br>
    padding: 0 10px 10px 0;<br>
    }<br>
    img.img-article-left.thumb {<br>
    max-width: 150px;<br>
    height: auto;<br>
    }<br>
    p.link-read-post {<br>
    text-align: right;<br>
    }<br>
    p.link-read-post a {<br>
    padding: 10px;<br>
    min-width: 100px;<br>
    background: #333671;<br>
    color: #fff;<br>
    text-decoration: none;<br>
    }<br>
    div.article-panel {<br>
    &nbsp;&nbsp;background: #eee;<br>
    &nbsp;&nbsp;padding: 5px 10px 5px 10px;<br>
    &nbsp;&nbsp;box-sizing: border-box;<br>
    &nbsp;&nbsp;overflow: hidden;<br>
    &nbsp;&nbsp;color: #555;<br>
    }<br>
    div.article-panel p.first {<br>
    &nbsp;&nbsp;margin: 0;<br>
    &nbsp;&nbsp;float: left;<br>
    }<br>
    div.article-panel p.last {<br>
    &nbsp;&nbsp;margin: 0;<br>
    &nbsp;&nbsp;float: right;<br>
    }<br>
    ul.list-articles {<br>
    list-style: none;<br>
    margin: 0;<br>
    padding: 0;<br>
    }<br>
    ul.list-articles li {<br>
    border-bottom: 1px solid #ccc;<br>
    }<br>
    .table-page {<br>
    width: 100%;<br>
    height: 100%;<br>
    vertical-align: top;<br>
    }<br>
    .table-page tr {height: 100%;}<br>
    .clear {clear: both;}<br>
    .header {<br>
    background: #3F4137;<br>
    height: 60px;<br>
    }<br>
    .logo {<br>
    background: url('../images/logo.png') no-repeat 10px 5px;<br>
    width: 70px;<br>
    height: 60px;<br>
    }<br>
    ul.mainmenu {<br>
    list-style: none;<br>
    margin: 0;<br>
    padding: 0;<br>
    height: 60px;<br>
    color: #fdc073;<br>
    font-size: 20px;<br>
    overflow: hidden;<br>
    }<br>
    ul.mainmenu li {<br>
    float: left;<br>
    margin: 18px 40px 0 30px;<br>
    }<br>
    ul.mainmenu li.logo {margin: 0;}<br>
    ul.mainmenu li.last {float: right;}<br>
    ul.mainmenu li a {<br>
    color: #fdc073;<br>
    text-decoration: none;<br>
    }<br>
    ul.mainmenu li a:hover {<br>
    color: #FDA83D;<br>
    }<br>
    .panelitems {<br>
    text-align: center;<br>
    }<br>
    ul.langitem {<br>
    list-style: none;<br>
    display: inline-block;<br>
    margin: 30px;<br>
    padding: 0;<br>
    max-width: 300px<br>
    }<br>
    ul.langitem li {<br>
    margin: 10px 0 0 0;<br>
    width: 100%;<br>
    }<br>
    ul.langitem li.image {<br>
    margin: 0;<br>
    text-align: center;<br>
    width: 100%;<br>
    height: 250px;<br>
    overflow: hidden;<br>
    }<br>
    ul.langitem li.descr {<br>
    color: #777;<br>
    height: 170px;<br>
    overflow: hidden;<br>
    }<br>
    ul.langitem li a {<br>
    color: #fdc073;<br>
    text-decoration: none;<br>
    font-size: 20px;<br>
    }<br>
    ul.langitem li a:hover {<br>
    color: #FDA83D;<br>
    }<br>
    div.button {<br>
    background: #3F4137;<br>
    max-width: 200px;<br>
    margin: 0 auto;<br>
    padding: 5px 20px 5px 20px;<br>
    border-radius: 10px;<br>
    font-size: 20px;<br>
    }<br>
    .table-content {<br>
    width: 100%;<br>
    min-height: 100%;<br>
    height: 100%;<br>
    }<br>
    .left-chapters {<br>
    margin: 0;<br>
    background: #eee;<br>
    border-right: 1px solid #ccc;<br>
    min-height: 100%;<br>
    }<br>
    .left-chapters ul {<br>
    width: 230px;<br>
    min-height: 100%;<br>
    margin: 0;<br>
    padding: 20px 10px 10px 20px;<br>
    list-style: none;<br>
    font-size: 20px;<br>
    }<br>
    .left-chapters ul li {<br>
    margin: 30px 0 0 0;<br>
    color: #999;<br>
    }<br>
    .left-chapters ul li.selected {color: #0059b2; }<br>
    .left-chapters ul li a {<br>
    color: #444;<br>
    text-decoration: none;<br>
    }<br>
    .left-chapters ul li a:hover { color: #CC0000; }<br>
    .left-chapters ul li.share {margin: 60px 0 0 0;}<br>
    .left-chapters ul li.share p {margin: 30px 0 30px 0;}<br>
    .left-chapters ul li.share a {<br>
    display: inline-block;<br>
    width: 40px;<br>
    height: 40px;<br>
    margin: 0 20px 0 0;<br>
    }<br>
    .left-chapters ul li.share a.share-yt {<br>
    width: 100%;<br>
    height: 30px;<br>
    background: url('../images/share_yt.png') no-repeat 0 0<br>
    }<br>
    .left-chapters ul li.share a.share-yt:hover {<br>
    width: 100%;<br>
    height: 30px;<br>
    background: url('../images/share_yt.png') no-repeat 0 -30px<br>
    }<br>
    .content {<br>
    padding: 40px 20px 20px 40px;<br>
    width: 100%;<br>
    box-sizing: border-box;<br>
    }<br>
    ul.breadcrumbs {<br>
    margin: 0;<br>
    padding: 0;<br>
    list-style: none;<br>
    font-size: 20px;<br>
    font-family: Sans-serif, Arial, Tahoma;<br>
    }<br>
    ul.breadcrumbs li {<br>
    display: inline-block;<br>
    }<br>
    ul.breadcrumbs li a {<br>
    color: #0059b2;<br>
    text-decoration: none;<br>
    }<br>
    ul.breadcrumbs li a:hover { color: #CC0000; }<br>
    ul.breadcrumbs li:after{<br>
    padding: 0 10px 0 10px;<br>
    content: "\2192";<br>
    }<br>
    ul.breadcrumbs li.last:after {content: "";}<br>
    ul.control {<br>
    margin: 0;<br>
    padding: 60px 0 0 0;<br>
    list-style: none;<br>
    font-family: Sans-serif, Arial, Tahoma;<br>
    font-size: 18px;<br>
    width: 100%;<br>
    }<br>
    ul.control li {float: left; padding: 0 0 0 10px;}<br>
    ul.control li.first:before {content: "\2190"; padding: 0 10px 0 0;}<br>
    ul.control li.last {float: right; padding: 0 40px 0 0;}<br>
    ul.control li.last:after {content: "\2192"; padding: 0 0 0 10px;}<br>
    ul.control li a { color: #0059b2; text-decoration: none; }<br>
    ul.control li a:hover { color: #CC0000; }<br>
    ul.content-table {<br>
    margin: 0;<br>
    padding: 60px 0 0 30px;<br>
    list-style: none;<br>
    font-family: Sans-serif, Arial, Tahoma;<br>
    font-size: 28px;<br>
    }<br>
    ul.content-table li {<br>
    margin: 0 0 40px 0;<br>
    }<br>
    ul.content-table li a {<br>
    color: #BB5715;<br>
    text-decoration: none;<br>
    }<br>
    ul.content-table li a:hover {color: #F0711C;}<br>
    .content-text {<br>
    margin: 60px 0 0 30px;<br>
    color: #000;<br>
    font-size: 20px;<br>
    font-family: Yandex Sans Display Light;<br>
    }<br>
    .content-text h1 {font-size: 32px;}<br>
    ul.lang-list {<br>
    list-style: none;<br>
    margin: 0;<br>
    padding: 14px 0 0 0;<br>
    background: #3F4137;<br>
    width: 100%;<br>
    height: 50px;<br>
    border-top: 1px solid #959A82;<br>
    box-sizing: border-box;<br>
    font-size: 18px;<br>
    font-family: Sans-serif, Arial, Tahoma;<br>
    }<br>
    ul.lang-list li {<br>
    display: inline-block;<br>
    margin-left: 40px;<br>
    }<br>
    ul.lang-list li.selected {color: #fdc073; border-bottom: 1px solid #fdc073;}<br>
    ul.lang-list li a {<br>
    color: #eee;<br>
    text-decoration: none;<br>
    }<br>
    ul.lang-list li a:hover {color: #fdc073;}<br>
    .topic-subject .topic-line {<br>
    border-bottom: 1px solid #CC0000;<br>
    margin-top: -16px;<br>
    }<br>
    .topic-subject .topic-text {<br>
    display: inline-block;<br>
    font-size: 28px;<br>
    color: #777;<br>
    padding: 0 10px 0 10px;<br>
    margin-left: 30px;<br>
    background: #fff;<br>
    font-family: Sans-serif, Arial, Tahoma;<br>
    }<br>
    .list-topic {<br>
    margin: 40px 0 60px 0;<br>
    font-family: Sans-serif, Arial, Tahoma;<br>
    }<br>
    .list-topic p {<br>
    margin: 0;<br>
    font-size: 28px;<br>
    }<br>
    .list-topic ol {<br>
    columns: 2;<br>
    -webkit-columns: 2;<br>
    column-gap: 40px;<br>
    }<br>
    .list-topic ol li {<br>
    display: list-item;<br>
    margin: 10px 10px 0 0px;<br>
    padding: 0 0 0 10px;<br>
    }<br>
    .list-topic ol li a {<br>
    color: #0059b2;<br>
    text-decoration: none;<br>
    }<br>
    .list-topic ol li a:hover {color: #CC0000;}<br>
    .highlight {<br>
    max-width: 350px;<br>
    padding: 0 10px 0 10px;<br>
    margin: 0;<br>
    overflow: auto;<br>
    overflow-y: hidden;<br>
    background: #f0f0f0;<br>
    }<br>
    .highlight p { margin: 0; }<br>
    .highlight .block {<br>
    width: 100%;<br>
    margin: 0;<br>
    }<br>
    .highlight .block p { margin: 0; }<br>
    .quote {<br>
    background: url('../images/blockquote.png') no-repeat 0 10px;<br>
    padding: 5px 5px 5px 70px;<br>
    font-family: Sans-serif, Arial, Tahoma;<br>
    font-style: italic;<br>
    }<br>
    #footer {<br>
    box-sizing: border-box;<br>
    background: #3F4137;<br>
    padding: 5px;<br>
    color: #aaa;<br>
    font-size: 14px;<br>
    font-family: Verdana, Geneva, Arial, Helvetica;<br>
    text-align: left;<br>
    overflow: hidden;<br>
    }<br>
    #footer a {<br>
    text-decoration: underline;<br>
    color: #aaa;<br>
    }<br>
    .form-input {<br>
    &nbsp;&nbsp;width: 300px;<br>
    &nbsp;&nbsp;font-size: 16px;<br>
    }<br>
    .form-label {<br>
    &nbsp;&nbsp;display: inline-block;<br>
    &nbsp;&nbsp;min-width: 150px;<br>
    &nbsp;&nbsp;vertical-align: top;<br>
    }<br>
    .form-error ul {<br>
    &nbsp;&nbsp;list-style: none;<br>
    &nbsp;&nbsp;padding: 0;<br>
    &nbsp;&nbsp;color: #CC0000;<br>
    }<br>
    .form-button {<br>
    &nbsp;&nbsp;min-width: 200px;<br>
    &nbsp;&nbsp;font-size: 16px;<br>
    }<br>
    $ mkdir women/static/women/js<br>
    $ mkdir women/static/women/images<br>
    $ ls women/static/women/images<br>
    blockquote.png btn_yt.png logo.png main.ico share_yt.png smallmenu.png<br>
    $ vim coolsite/settings.py<br>
    $ cat coolsite/settings.py<br>
    ...<br>
    # Static files (CSS, JavaScript, Images)<br>
    # https://docs.djangoproject.com/en/4.2/howto/static-files/<br>
    STATIC_URL = '/static/'<br>
    STATIC_ROOT = os.path.join(BASE_DIR, 'static')<br>
    STATICFILES_DIRS=[]<br>
    # Default primary key field type<br>
    ...<br>
    $ vim women/templates/women/base.html<br>
    $ cat women/templates/women/base.html<br>
    {% load static %}<br>
    &lt;!DOCTYPE html&gt;<br>
    &lt;html&gt;<br>
    &lt;head&gt;<br>
    &lt;title&gt;{{title}}&lt;/title&gt;<br>
    &lt;link type="text/css" href="{% static 'women/css/style.css' %}" rel="stylesheet" /&gt;<br>
    &lt;meta http-equiv="Content-Type" content="text/html; charset=utf-8"&gt;<br>
    &lt;link rel="shortcut icon" href="{% static 'women/images/main.ico' %}" type="image/x-icon"/&gt;<br>
    &lt;meta name="viewport" content="width=device-width, initial-scale=1.0"&gt;<br>
    &lt;/head&gt;<br>
    &lt;body&gt;<br>
    &lt;table class="table-page" border=0 cellpadding="0" cellspacing="0"&gt;<br>
    &lt;tr&gt;&lt;td valign=top&gt;<br>
    {% block mainmenu %}<br>
    &lt;div class="header"&gt;<br>
    &lt;ul id="mainmenu" class="mainmenu"&gt;<br>
    &lt;li class="logo"&gt;&lt;a href="#"&gt;&lt;div class="logo"&gt;&lt;/div&gt;&lt;/a&gt;&lt;/li&gt;<br>
    {% for m in menu %}<br>
    {% if not forloop.last %}<br>
    &lt;li&gt;&lt;a href="#"&gt;{{m.title}}&lt;/a&gt;&lt;/li&gt;<br>
    {% else %}<br>
    &lt;li class="last"&gt;&lt;a href="#"&gt;{{m.title}}&lt;/a&gt;&lt;/li&gt;<br>
    {% endif %}<br>
    {% endfor %}<br>
    &lt;/ul&gt;<br>
    &lt;div class="clear"&gt;&lt;/div&gt;<br>
    &lt;/div&gt;<br>
    {% endblock mainmenu %}<br>
    &lt;table class="table-content" border=0 cellpadding="0" cellspacing="0"&gt;<br>
    &lt;tr&gt;<br>
    &lt;!-- Sidebar слева --&gt;<br>
    &lt;td valign="top" class="left-chapters"&gt;<br>
    &lt;ul id="leftchapters"&gt;<br>
    &lt;li class="selected"&gt;Все категории&lt;/li&gt;<br>
    &lt;li&gt;&lt;a href="#"&gt;Актрисы&lt;/a&gt;&lt;/li&gt;<br>
    &lt;li&gt;&lt;a href="#"&gt;Певицы&lt;/a&gt;&lt;/li&gt;<br>
    &lt;li&gt;&lt;a href="#"&gt;Спортсменки&lt;/a&gt;&lt;/li&gt;<br>
    &lt;li class="share"&gt;<br>
    &lt;p&gt;Наш канал&lt;/p&gt;<br>
    &lt;a class="share-yt" href="https://www.youtube.com/channel/UClJzWfGWuGJL2t-3dYKcHTA/playlists" target="_blank" rel="nofollow"&gt;&lt;/a&gt;<br>
    &lt;/li&gt;<br>
    &lt;/ul&gt;<br>
    &lt;/td&gt;<br>
    &lt;!-- Конец Sidebar'а --&gt;<br>
    &lt;td valign="top" class="content"&gt;<br>
    &lt;!-- Хлебные крошки --&gt;<br>
    {% block breadcrumbs %}<br>
    {% endblock %}<br>
    &lt;!-- Блок контента --&gt;<br>
    &lt;div class="content-text"&gt;<br>
    {% block content %}<br>
    {% endblock %}<br>
    &lt;/div&gt;<br>
    &lt;!-- Конец блока контента --&gt;<br>
    &lt;/td&gt;&lt;/tr&gt;&lt;/table&gt;<br>
    &lt;/td&gt;&lt;/tr&gt;<br>
    &lt;!-- Footer --&gt;<br>
    &lt;tr&gt;&lt;td valign=top&gt;<br>
    &lt;div id="footer"&gt;<br>
    &lt;p&gt;© 2021 Частичное или полное копирование информации с данного сайта для распространения на других ресурсах, в том числе и бумажных, строго запрещено.&lt;/p&gt;<br>
    &lt;/div&gt;<br>
    &lt;/td&gt;&lt;/tr&gt;&lt;/table&gt;<br>
    &lt;!-- Конец footer'а и страницы --&gt;<br>
    &lt;/body&gt;<br>
    &lt;/html&gt;<br>
    $ vim women/templates/women/index.html<br>
    $ cat women/templates/women/index.html<br>
    {% extends 'women/base.html' %}<br>
    {% block content %}<br>
    &lt;ul class="list-articles"&gt;<br>
    {% for p in posts %}<br>
    &lt;li&gt;&lt;h2&gt;{{p.title}}&lt;/h2&gt;<br>
    {% autoescape on %}<br>
    {{p.content|linebreaks|truncatewords:50}}<br>
    {% endautoescape %}<br>
    &lt;div class="clear"&gt;&lt;/div&gt;<br>
    &lt;p class="link-read-post"&gt;&lt;a href="#"&gt;Читать пост&lt;/a&gt;&lt;/p&gt;<br>
    &lt;/li&gt;<br>
    {% endfor %}<br>
    &lt;/ul&gt;<br>
    {% endblock %}<br>
    $ python manage.py runserver<br>
    $ vim women/templates/women/index.html<br>
    $ cat women/templates/women/index.html<br>
    ...<br>
    {% for p in posts %}<br>
    &lt;li&gt;&lt;h2&gt;{{p.title}}&lt;/h2&gt;<br>
    {% autoescape on %}<br>
    {{p.content|linebreaks|truncatewords:50}}<br>
    {% endautoescape %}<br>
    &lt;div class="clear"&gt;&lt;/div&gt;<br>
    &lt;p class="link-read-post"&gt;<br>
    &lt;!--&lt;a href="#"&gt;--&gt;<br>
    &lt;!--&lt;a href="{% url 'post' p.pk %}"&gt;--&gt;<br>
    &lt;a href="{{ p.get_absolute_url }}"&gt;<br>
    Читать пост<br>
    &lt;/a&gt;<br>
    &lt;/p&gt;<br>
    &lt;/li&gt;<br>
    {% endfor %}<br>
    ...<br>
    $ vim women/templates/women/base.html<br>
    $ cat women/templates/women/base.html<br>
    ...<br>
    {% block mainmenu %}<br>
    &lt;div class="header"&gt;<br>
    &lt;ul id="mainmenu" class="mainmenu"&gt;<br>
    &lt;li class="logo"&gt;<br>
    &lt;!--&lt;a href="#"&gt;--&gt;<br>
    &lt;a href="{% url 'home' %}"&gt;<br>
    &lt;div class="logo"&gt;&lt;/div&gt;<br>
    &lt;/a&gt;<br>
    &lt;/li&gt;<br>
    {% for m in menu %}<br>
    {% if not forloop.last %}<br>
    &lt;li&gt;&lt;a href="{% url m.url_name %}"&gt;{{m.title}}&lt;/a&gt;&lt;/li&gt;<br>
    {% else %}<br>
    &lt;li class="last"&gt;&lt;a href="{% url m.url_name %}"&gt;{{m.title}}&lt;/a&gt;&lt;/li&gt;<br>
    {% endif %}<br>
    {% endfor %}<br>
    &lt;/ul&gt;<br>
    &lt;div class="clear"&gt;&lt;/div&gt;<br>
    &lt;/div&gt;<br>
    {% endblock mainmenu %}<br>
    ...<br>
    $ vim women/views.py<br>
    $ cat women/views.py<br>
    from django.http import HttpResponse, HttpResponseNotFound, Http404<br>
    from django.shortcuts import render, redirect<br>
    from .models import *<br>
    # Create your views here.<br>
    #def index(request): #HttpRequest<br>
    #return HttpResponse("Страница приложения Women")<br>
    #menu=["О сайте", "Добавить статью", "Обратная связь", "Войти"]<br>
    menu=[{'title':"О сайте", 'url_name':'about'},&nbsp;<br>
    {'title':"Добавить статью", 'url_name':'add_page'},<br>
    {'title':"Обратная связь", 'url_name':'contact'},<br>
    {'title':"Войти", 'url_name':'login'}]<br>
    def index(request):<br>
    #return render(request, 'women/index.html', {'title':'Главная страница'})<br>
    posts=Women.objects.all()<br>
    context={'posts':posts,&nbsp;<br>
    'menu':menu,&nbsp;<br>
    'title':'Главная страница'}<br>
    return render(request, 'women/index.html', context=context)<br>
    def about(request):<br>
    return render(request, 'women/about.html', {'menu':menu, 'title':'О сайте'})<br>
    #def categories(request):<br>
    #return HttpResponse("&lt;h1&gt;Статьи по категориям&lt;/h1&gt;")<br>
    #def categories(request, catid):<br>
    #print(request.GET) #http://127.0.0.1:8000/cats/1/?name=Gagarina&amp;type=pop<br>
    #if(request.GET):<br>
    #print(request.GET) #http://127.0.0.1:8000/cats/1<br>
    #if(request.POST):<br>
    #print(request.POST)&nbsp;<br>
    #return HttpResponse(f"&lt;h1&gt;Статьи по категориям&lt;/h1&gt;&lt;p&gt;{catid}&lt;/p&gt;")<br>
    #def archive(request, year):<br>
    #if int(year)&gt;2020:<br>
    #raise Http404() #http://127.0.0.1:8000/archive/2022/<br>
    #return redirect('/', )<br>
    #return redirect('home', permanent=True)<br>
    #return HttpResponse(f"&lt;h1&gt;Архив по годам&lt;/h1&gt;&lt;p&gt;{year}&lt;/p&gt;") #http://127.0.0.1:8000/archive/2020/<br>
    def pageNotFound(request, exception):<br>
    return HttpResponseNotFound("&lt;h1&gt;Страница не найдена&lt;/h1&gt;")<br>
    def addpage(request):<br>
    return HttpResponse("Добавление статьи")<br>
    def contact(request):<br>
    return HttpResponse("Обратная связь")<br>
    def login(request):<br>
    return HttpResponse("Авторизация")<br>
    def show_post(request, post_id):<br>
    return HttpResponse(f"Отображение статьи с id = {post_id}")<br>
    $ vim women/urls.py<br>
    $ cat women/urls.py<br>
    ...<br>
    urlpatterns = [<br>
    #path('', index), #http://127.0.0.1:8000/women/<br>
    #path('home/', index, name='home'), #http://127.0.0.1:8000/<br>
    path('', index, name='home'), #http://127.0.0.1:8000/<br>
    #path('cats/', categories), #http://127.0.0.1:8000/women/cats/<br>
    #path('cats/', categories), #http://127.0.0.1:8000/cats/<br>
    #path('cats/&lt;int:catid&gt;/', categories), #http://127.0.0.1:8000/cats/1/<br>
    #re_path(r'^archive/(?P&lt;year&gt;[0-9]{4})/', archive), #http://127.0.0.1:8000/archive/2020/<br>
    path('about/', about, name='about'), #http://127.0.0.1:8000/<br>
    path('addpage/', addpage, name='add_page'),<br>
    path('contact/', contact, name='contact'),<br>
    path('login/', login, name='login'),<br>
    path('post/&lt;int:post_id&gt;/', show_post, name='post'),<br>
    ]<br>
    $ vim women/models.py<br>
    $ cat women/models.py<br>
    from django.db import models<br>
    from django.urls import reverse<br>
    ...<br>
    def get_absolute_url(self):<br>
    return reverse('post', kwargs={'post_id':self.pk})<br>
    $ python manage.py runserver<br>
    $ vim women/models.py<br>
    $ cat women/models.py<br>
    ...<br>
    class Women(models.Model):<br>
    """docstring for Women"""<br>
    title=models.CharField(max_length=255)<br>
    content=models.TextField(blank=True)<br>
    photo=models.ImageField(upload_to="photos/%Y/%m/%d/")<br>
    time_create=models.DateTimeField(auto_now_add=True)<br>
    time_update=models.DateTimeField(auto_now=True)<br>
    is_published=models.BooleanField(default=True)<br>
    cat=models.ForeignKey('Category', on_delete=models.PROTECT, null=True)<br>
    def __str__(self):<br>
    return self.title<br>
    def get_absolute_url(self):<br>
    return reverse('post', kwargs={'post_id':self.pk})<br>
    class Category(models.Model):<br>
    name=models.CharField(max_length=100, db_index=True)<br>
    def __str__(self):<br>
    return self.name<br>
    $ python manage.py makemigrations<br>
    $ python manage.py migrate<br>
    $ sqlite3 db.sqlite3<br>
    sqlite&gt; SELECT * FROM sqlite_master where type='table';<br>
    $ python manage.py shell<br>
    &gt;&gt;&gt; from women.models import *<br>
    &gt;&gt;&gt; Category.objects.create(name='Актрисы')<br>
    &gt;&gt;&gt; Category.objects.create(name='Певицы')<br>
    &gt;&gt;&gt; w_list=Women.objects.all()<br>
    &gt;&gt;&gt; w_list.update(cat_id=1)<br>
    &gt;&gt;&gt; exit()<br>
    $ sqlite3 db.sqlite3<br>
    sqlite&gt; select * from women_women;<br>
    sqlite&gt; select * from women_category;<br>
    $ python manage.py shell<br>
    &gt;&gt;&gt; from women.models import *<br>
    &gt;&gt;&gt; Women.title<br>
    &gt;&gt;&gt; w1=Women(title='t1',content='c1',cat_id=1)<br>
    &gt;&gt;&gt; type(w1.title)<br>
    &gt;&gt;&gt; type(Women.title)<br>
    &gt;&gt;&gt; type(w1.cat)<br>
    &gt;&gt;&gt; w1.pk<br>
    &gt;&gt;&gt; print(w1.id,w1.time_create,w1.time_update)<br>
    &gt;&gt;&gt; from django.db import connection<br>
    &gt;&gt;&gt; connection.queries<br>
    &gt;&gt;&gt; exit()<br>
    $ python manage.py shell<br>
    &gt;&gt;&gt; from women.models import *<br>
    &gt;&gt;&gt; w1=Women(title='t1',content='c1',cat_id=1)<br>
    &gt;&gt;&gt; from django.db import connection<br>
    &gt;&gt;&gt; connection.queries<br>
    &gt;&gt;&gt; w1.cat<br>
    &gt;&gt;&gt; connection.queries<br>
    &gt;&gt;&gt; w2=Women.objects.get(pk=2)<br>
    &gt;&gt;&gt; connection.queries<br>
    &gt;&gt;&gt; w2.title<br>
    &gt;&gt;&gt; w2.cat<br>
    &gt;&gt;&gt; connection.queries<br>
    &gt;&gt;&gt; w2.cat.name<br>
    &gt;&gt;&gt; exit()<br>
    $ vim women/models.py<br>
    $ cat women/models.py<br>
    from django.db import models<br>
    from django.urls import reverse<br>
    # Create your models here.<br>
    class Women(models.Model):<br>
    """docstring for Women"""<br>
    title=models.CharField(max_length=255)<br>
    content=models.TextField(blank=True)<br>
    photo=models.ImageField(upload_to="photos/%Y/%m/%d/")<br>
    time_create=models.DateTimeField(auto_now_add=True)<br>
    time_update=models.DateTimeField(auto_now=True)<br>
    is_published=models.BooleanField(default=True)<br>
    cat=models.ForeignKey('Category', on_delete=models.PROTECT, null=True)<br>
    def __str__(self):<br>
    return self.title<br>
    def get_absolute_url(self):<br>
    return reverse('post', kwargs={'post_id':self.pk})<br>
    class Category(models.Model):<br>
    name=models.CharField(max_length=100, db_index=True)<br>
    def __str__(self):<br>
    return self.name<br>
    def get_absolute_url(self):<br>
    return reverse('category', kwargs={'cat_id':self.pk})<br>
    $ vim women/urls.py<br>
    $ cat women/urls.py<br>
    from django.urls import path, re_path<br>
    from .views import *<br>
    urlpatterns = [<br>
    #path('', index), #http://127.0.0.1:8000/women/<br>
    #path('home/', index, name='home'), #http://127.0.0.1:8000/<br>
    path('', index, name='home'), #http://127.0.0.1:8000/<br>
    #path('cats/', categories), #http://127.0.0.1:8000/women/cats/<br>
    #path('cats/', categories), #http://127.0.0.1:8000/cats/<br>
    #path('cats/&lt;int:catid&gt;/', categories), #http://127.0.0.1:8000/cats/1/<br>
    #re_path(r'^archive/(?P&lt;year&gt;[0-9]{4})/', archive), #http://127.0.0.1:8000/archive/2020/<br>
    path('about/', about, name='about'), #http://127.0.0.1:8000/<br>
    path('addpage/', addpage, name='add_page'),<br>
    path('contact/', contact, name='contact'),<br>
    path('login/', login, name='login'),<br>
    path('post/&lt;int:post_id&gt;/', show_post, name='post'),<br>
    path('category/&lt;int:cat_id&gt;/', show_category, name='category'),<br>
    ]<br>
    $ vim women/views.py<br>
    $ cat women/views.py<br>
    from django.http import HttpResponse, HttpResponseNotFound, Http404<br>
    from django.shortcuts import render, redirect<br>
    from .models import *<br>
    # Create your views here.<br>
    #def index(request): #HttpRequest<br>
    #return HttpResponse("Страница приложения Women")<br>
    #menu=["О сайте", "Добавить статью", "Обратная связь", "Войти"]<br>
    menu=[{'title':"О сайте", 'url_name':'about'},&nbsp;<br>
    {'title':"Добавить статью", 'url_name':'add_page'},<br>
    {'title':"Обратная связь", 'url_name':'contact'},<br>
    {'title':"Войти", 'url_name':'login'}]<br>
    def index(request):<br>
    #return render(request, 'women/index.html', {'title':'Главная страница'})<br>
    posts=Women.objects.all()<br>
    cats=Category.objects.all()<br>
    context={'posts':posts,&nbsp;<br>
    'cats':cats,<br>
    'menu':menu,&nbsp;<br>
    'title':'Главная страница',<br>
    'cat_selected':0}<br>
    return render(request, 'women/index.html', context=context)<br>
    def about(request):<br>
    return render(request, 'women/about.html', {'menu':menu, 'title':'О сайте'})<br>
    #def categories(request):<br>
    #return HttpResponse("&lt;h1&gt;Статьи по категориям&lt;/h1&gt;")<br>
    #def categories(request, catid):<br>
    #print(request.GET) #http://127.0.0.1:8000/cats/1/?name=Gagarina&amp;type=pop<br>
    #if(request.GET):<br>
    #print(request.GET) #http://127.0.0.1:8000/cats/1<br>
    #if(request.POST):<br>
    #print(request.POST)&nbsp;<br>
    #return HttpResponse(f"&lt;h1&gt;Статьи по категориям&lt;/h1&gt;&lt;p&gt;{catid}&lt;/p&gt;")<br>
    #def archive(request, year):<br>
    #if int(year)&gt;2020:<br>
    #raise Http404() #http://127.0.0.1:8000/archive/2022/<br>
    #return redirect('/', )<br>
    #return redirect('home', permanent=True)<br>
    #return HttpResponse(f"&lt;h1&gt;Архив по годам&lt;/h1&gt;&lt;p&gt;{year}&lt;/p&gt;") #http://127.0.0.1:8000/archive/2020/<br>
    def pageNotFound(request, exception):<br>
    return HttpResponseNotFound("&lt;h1&gt;Страница не найдена&lt;/h1&gt;")<br>
    def addpage(request):<br>
    return HttpResponse("Добавление статьи")<br>
    def contact(request):<br>
    return HttpResponse("Обратная связь")<br>
    def login(request):<br>
    return HttpResponse("Авторизация")<br>
    def show_post(request, post_id):<br>
    return HttpResponse(f"Отображение статьи с id = {post_id}")<br>
    #def show_category(request, cat_id):<br>
    #return HttpResponse(f"Отображение категории с id = {cat_id}")<br>
    def show_category(request, cat_id):<br>
    posts=Women.objects.filter(cat_id=cat_id)<br>
    cats=Category.objects.all()<br>
    if len(posts)==0:<br>
    raise Http404()<br>
    context={'posts':posts,<br>
    'cats':cats,<br>
    'menu':menu,<br>
    'title':'Главная страница',<br>
    'cat_selected':cat_id,}<br>
    return render(request, 'women/index.html', context=context)<br>
    $ vim women/templates/women/base.html<br>
    $ cat women/templates/women/base.html<br>
    {% load static %}<br>
    &lt;!DOCTYPE html&gt;<br>
    &lt;html&gt;<br>
    &lt;head&gt;<br>
    &lt;title&gt;{{title}}&lt;/title&gt;<br>
    &lt;link type="text/css" href="{% static 'women/css/style.css' %}" rel="stylesheet" /&gt;<br>
    &lt;meta http-equiv="Content-Type" content="text/html; charset=utf-8"&gt;<br>
    &lt;link rel="shortcut icon" href="{% static 'women/images/main.ico' %}" type="image/x-icon"/&gt;<br>
    &lt;meta name="viewport" content="width=device-width, initial-scale=1.0"&gt;<br>
    &lt;/head&gt;<br>
    &lt;body&gt;<br>
    &lt;table class="table-page" border=0 cellpadding="0" cellspacing="0"&gt;<br>
    &lt;tr&gt;&lt;td valign=top&gt;<br>
    {% block mainmenu %}<br>
    &lt;div class="header"&gt;<br>
    &lt;ul id="mainmenu" class="mainmenu"&gt;<br>
    &lt;li class="logo"&gt;<br>
    &lt;!--&lt;a href="#"&gt;--&gt;<br>
    &lt;a href="{% url 'home' %}"&gt;<br>
    &lt;div class="logo"&gt;&lt;/div&gt;<br>
    &lt;/a&gt;<br>
    &lt;/li&gt;<br>
    {% for m in menu %}<br>
    {% if not forloop.last %}<br>
    &lt;li&gt;&lt;a href="{% url m.url_name %}"&gt;{{m.title}}&lt;/a&gt;&lt;/li&gt;<br>
    {% else %}<br>
    &lt;li class="last"&gt;&lt;a href="{% url m.url_name %}"&gt;{{m.title}}&lt;/a&gt;&lt;/li&gt;<br>
    {% endif %}<br>
    {% endfor %}<br>
    &lt;/ul&gt;<br>
    &lt;div class="clear"&gt;&lt;/div&gt;<br>
    &lt;/div&gt;<br>
    {% endblock mainmenu %}<br>
    &lt;table class="table-content" border=0 cellpadding="0" cellspacing="0"&gt;<br>
    &lt;tr&gt;<br>
    &lt;!-- Sidebar слева --&gt;<br>
    &lt;td valign="top" class="left-chapters"&gt;<br>
    &lt;ul id="leftchapters"&gt;<br>
    {% if cat_selected == 0 %}<br>
    &lt;li class="selected"&gt;Все категории&lt;/li&gt;<br>
    {% else %}<br>
    &lt;li&gt;&lt;a href="{% url 'home' %}"&gt;Все категории&lt;/a&gt;&lt;/li&gt;<br>
    {% endif %}<br>
    {% for c in cats %}<br>
    {% if c.pk == cat_selected %}<br>
    &lt;li class="selected"&gt;{{c.name}}&lt;/li&gt;<br>
    {% else %}<br>
    &lt;li&gt;&lt;a href="{{ c.get_absolute_url }}"&gt;{{c.name}}&lt;/a&gt;&lt;/li&gt;<br>
    {% endif %}<br>
    {% endfor %}<br>
    &lt;li class="share"&gt;<br>
    &lt;p&gt;Наш канал&lt;/p&gt;<br>
    &lt;a class="share-yt" href="https://www.youtube.com/channel/UClJzWfGWuGJL2t-3dYKcHTA/playlists" target="_blank" rel="nofollow"&gt;&lt;/a&gt;<br>
    &lt;/li&gt;<br>
    &lt;/ul&gt;<br>
    &lt;/td&gt;<br>
    &lt;!-- Конец Sidebar'а --&gt;<br>
    &lt;td valign="top" class="content"&gt;<br>
    &lt;!-- Хлебные крошки --&gt;<br>
    {% block breadcrumbs %}<br>
    {% endblock %}<br>
    &lt;!-- Блок контента --&gt;<br>
    &lt;div class="content-text"&gt;<br>
    {% block content %}<br>
    {% endblock %}<br>
    &lt;/div&gt;<br>
    &lt;!-- Конец блока контента --&gt;<br>
    &lt;/td&gt;&lt;/tr&gt;&lt;/table&gt;<br>
    &lt;/td&gt;&lt;/tr&gt;<br>
    &lt;!-- Footer --&gt;<br>
    &lt;tr&gt;&lt;td valign=top&gt;<br>
    &lt;div id="footer"&gt;<br>
    &lt;p&gt;© 2021 Частичное или полное копирование информации с данного сайта для распространения на других ресурсах, в том числе и бумажных, строго запрещено.&lt;/p&gt;<br>
    &lt;/div&gt;<br>
    &lt;/td&gt;&lt;/tr&gt;&lt;/table&gt;<br>
    &lt;!-- Конец footer'а и страницы --&gt;<br>
    &lt;/body&gt;<br>
    &lt;/html&gt;<br>
    $ vim women/templates/women/index.html<br>
    $ cat women/templates/women/index.html<br>
    {% extends 'women/base.html' %}<br>
    {% block content %}<br>
    &lt;ul class="list-articles"&gt;<br>
    {% for p in posts %}<br>
    &lt;li&gt;<br>
    &lt;div class="article_panel"&gt;<br>
    &lt;p class="first"&gt;Категория: {{p.cat}}&lt;/p&gt;<br>
    &lt;p class="last"&gt;Дата: {{p.time_update|date:"d-m-Y H:i:s"}}&lt;/p&gt;<br>
    &lt;/div&gt;<br>
    &lt;h2&gt;{{p.title}}&lt;/h2&gt;<br>
    {% autoescape on %}<br>
    {{p.content|linebreaks|truncatewords:50}}<br>
    {% endautoescape %}<br>
    &lt;div class="clear"&gt;&lt;/div&gt;<br>
    &lt;p class="link-read-post"&gt;<br>
    &lt;!--&lt;a href="#"&gt;--&gt;<br>
    &lt;!--&lt;a href="{% url 'post' p.pk %}"&gt;--&gt;<br>
    &lt;a href="{{ p.get_absolute_url }}"&gt;<br>
    Читать пост<br>
    &lt;/a&gt;<br>
    &lt;/p&gt;<br>
    &lt;/li&gt;<br>
    {% endfor %}<br>
    &lt;/ul&gt;<br>
    {% endblock %}<br>
    $ python manage.py runserver<br>
    $ vim coolsite/settings.py<br>
    $ cat coolsite/settings.py<br>
    ...<br>
    # Internationalization<br>
    # https://docs.djangoproject.com/en/4.2/topics/i18n/<br>
    #LANGUAGE_CODE = 'en-us'<br>
    LANGUAGE_CODE = 'ru'<br>
    TIME_ZONE = 'UTC'<br>
    USE_I18N = True<br>
    USE_TZ = True<br>
    ...<br>
    $ python manage.py createsuperuser<br>
    $ vim women/admin.py<br>
    $ cat women/admin.py<br>
    from django.contrib import admin<br>
    from .models import *<br>
    # Register your models here.<br>
    class WomenAdmin(admin.ModelAdmin):<br>
    &nbsp;&nbsp;list_display = ('id', 'title', 'time_create', 'photo', 'is_published')<br>
    &nbsp;&nbsp;list_display_links = ('id', 'title')<br>
    &nbsp;&nbsp;search_fields = ('title', 'content')<br>
    class CategoryAdmin(admin.ModelAdmin):<br>
    &nbsp;&nbsp;list_display = ('id', 'name')<br>
    &nbsp;&nbsp;list_display_links = ('id', 'name')<br>
    &nbsp;&nbsp;search_fields = ('name',)<br>
    admin.site.register(Women, WomenAdmin)<br>
    admin.site.register(Category, CategoryAdmin)<br>
    $ vim women/models.py<br>
    $ cat women/models.py<br>
    from django.db import models<br>
    from django.urls import reverse<br>
    # Create your models here.<br>
    class Women(models.Model):<br>
    """docstring for Women"""<br>
    title=models.CharField(max_length=255, verbose_name="Заголовок")<br>
    content=models.TextField(blank=True, verbose_name="Текст статьи")<br>
    photo=models.ImageField(upload_to="photos/%Y/%m/%d/", verbose_name="Фото")<br>
    time_create=models.DateTimeField(auto_now_add=True, verbose_name="Время создания")<br>
    time_update=models.DateTimeField(auto_now=True, verbose_name="Время изменения")<br>
    is_published=models.BooleanField(default=True, verbose_name="Публикация")<br>
    cat=models.ForeignKey('Category', on_delete=models.PROTECT, null=True, verbose_name="Категории")<br>
    def __str__(self):<br>
    return self.title<br>
    def get_absolute_url(self):<br>
    return reverse('post', kwargs={'post_id':self.pk})<br>
    class Meta:<br>
    verbose_name='Известные женщины'<br>
    verbose_name_plural='Известные женщины'<br>
    #ordering=['time_create','title']<br>
    ordering=['-time_create','title']<br>
    class Category(models.Model):<br>
    name=models.CharField(max_length=100, db_index=True, verbose_name="Категория")<br>
    def __str__(self):<br>
    return self.name<br>
    def get_absolute_url(self):<br>
    return reverse('category', kwargs={'cat_id':self.pk})<br>
    class Meta:<br>
    verbose_name='Категория'<br>
    verbose_name_plural='Категории'<br>
    ordering=['id']<br>
    $ vim women/apps.py<br>
    $ cat women/apps.py<br>
    from django.apps import AppConfig<br>
    class WomenConfig(AppConfig):<br>
    &nbsp;&nbsp;default_auto_field = 'django.db.models.BigAutoField'<br>
    &nbsp;&nbsp;name = 'women'<br>
    &nbsp;&nbsp;verbose_name='Женщины мира'<br>
    $ python manage.py makemigrations<br>
    $ python manage.py migrate<br>
    $ vim women/templates/women/index.html<br>
    $ cat women/templates/women/index.html<br>
    {% extends 'women/base.html' %}<br>
    {% block content %}<br>
    &lt;ul class="list-articles"&gt;<br>
    {% for p in posts %}<br>
    &lt;li&gt;<br>
    &lt;div class="article_panel"&gt;<br>
    &lt;p class="first"&gt;Категория: {{p.cat}}&lt;/p&gt;<br>
    &lt;p class="last"&gt;Дата: {{p.time_update|date:"d-m-Y H:i:s"}}&lt;/p&gt;<br>
    &lt;/div&gt;<br>
    {% if p.photo %}<br>
    &lt;p&gt;&lt;img class="img-article-left thumb" src="{{p.photo.url}}"&gt;&lt;/p&gt;<br>
    {% endif %}<br>
    &lt;h2&gt;{{p.title}}&lt;/h2&gt;<br>
    {% autoescape on %}<br>
    {{p.content|linebreaks|truncatewords:50}}<br>
    {% endautoescape %}<br>
    &lt;div class="clear"&gt;&lt;/div&gt;<br>
    &lt;p class="link-read-post"&gt;<br>
    &lt;!--&lt;a href="#"&gt;--&gt;<br>
    &lt;!--&lt;a href="{% url 'post' p.pk %}"&gt;--&gt;<br>
    &lt;a href="{{ p.get_absolute_url }}"&gt;<br>
    Читать пост<br>
    &lt;/a&gt;<br>
    &lt;/p&gt;<br>
    &lt;/li&gt;<br>
    {% endfor %}<br>
    &lt;/ul&gt;<br>
    {% endblock %}<br>
    $ vim women/admin.py<br>
    $ cat women/admin.py<br>
    from django.contrib import admin<br>
    from .models import *<br>
    # Register your models here.<br>
    class WomenAdmin(admin.ModelAdmin):<br>
    &nbsp;&nbsp;list_display = ('id', 'title', 'time_create', 'photo', 'is_published')<br>
    &nbsp;&nbsp;list_display_links = ('id', 'title')<br>
    &nbsp;&nbsp;search_fields = ('title', 'content')<br>
    &nbsp;&nbsp;list_editable = ('is_published',)<br>
    &nbsp;&nbsp;list_filter = ('is_published', 'time_create')<br>
    class CategoryAdmin(admin.ModelAdmin):<br>
    &nbsp;&nbsp;list_display = ('id', 'name')<br>
    &nbsp;&nbsp;list_display_links = ('id', 'name')<br>
    &nbsp;&nbsp;search_fields = ('name',)<br>
    admin.site.register(Women, WomenAdmin)<br>
    admin.site.register(Category, CategoryAdmin)<br>
    $ python manage.py runserver<br>
    $ vim women/views.py<br>
    $ cat women/views.py<br>
    ...<br>
    def index(request):<br>
    #return render(request, 'women/index.html', {'title':'Главная страница'})<br>
    posts=Women.objects.all()<br>
    #cats=Category.objects.all()<br>
    context={'posts':posts,&nbsp;<br>
    #'cats':cats,<br>
    'menu':menu,&nbsp;<br>
    'title':'Главная страница',<br>
    'cat_selected':0}<br>
    return render(request, 'women/index.html', context=context)<br>
    ...<br>
    def show_category(request, cat_id):<br>
    posts=Women.objects.filter(cat_id=cat_id)<br>
    #cats=Category.objects.all()<br>
    if len(posts)==0:<br>
    raise Http404()<br>
    context={'posts':posts,<br>
    #'cats':cats,<br>
    'menu':menu,<br>
    'title':'Главная страница',<br>
    'cat_selected':cat_id,}<br>
    return render(request, 'women/index.html', context=context)<br>
    $ mkdir women/templatetags<br>
    $ touch women/templatetags/__init__.py<br>
    $ touch women/templatetags/women_tags.py<br>
    $ vim women/templatetags/women_tags.py<br>
    $ cat women/templatetags/women_tags.py<br>
    from django import template<br>
    from women.models import *<br>
    register=template.Library()<br>
    @register.simple_tag(name='getcats')<br>
    def get_categories(filter=None):<br>
    #return Category.objects.all()<br>
    if not filter:<br>
    return Category.objects.all()<br>
    else:<br>
    return Category.objects.filter(pk=filter)<br>
    @register.inclusion_tag('women/list_categories.html')<br>
    #def show_categories():<br>
    def show_categories(sort=None, cat_selected=0):<br>
    #cats=Category.objects.all()<br>
    #return {"cats": cats}<br>
    if not sort:<br>
    cats = Category.objects.all()<br>
    else:<br>
    cats = Category.objects.order_by(sort)<br>
    return {"cats":cats, "cat_selected":cat_selected}<br>
    $ vim women/templates/women/base.html<br>
    $ cat women/templates/women/base.html<br>
    ...<br>
    &lt;!-- Sidebar слева --&gt;<br>
    &lt;td valign="top" class="left-chapters"&gt;<br>
    &lt;ul id="leftchapters"&gt;<br>
    {% if cat_selected == 0 %}<br>
    &lt;li class="selected"&gt;Все категории&lt;/li&gt;<br>
    {% else %}<br>
    &lt;li&gt;&lt;a href="{% url 'home' %}"&gt;Все категории&lt;/a&gt;&lt;/li&gt;<br>
    {% endif %}<br>
    {% show_categories cat_selected=cat_selected %}<br>
    &lt;li class="share"&gt;&lt;p&gt;Наш канал&lt;/p&gt;&lt;a class="share-yt" href="https://www.youtube.com/channel/UClJzWfGWuGJL2t-3dYKcHTA/playlists" target="_blank" rel="nofollow"&gt;&lt;/a&gt;&lt;/li&gt;<br>
    &lt;/ul&gt;<br>
    &lt;/td&gt;<br>
    ...<br>
    $ touch women/templates/women/list_categories.html<br>
    $ vim women/templates/women/list_categories.html<br>
    $ cat women/templates/women/list_categories.html<br>
    {% for c in cats %}<br>
    {% if c.pk == cat_selected %}<br>
    &lt;li class="selected"&gt;{{c.name}}&lt;/li&gt;<br>
    {% else %}<br>
    &lt;li&gt;&lt;a href="{{ c.get_absolute_url }}"&gt;{{c.name}}&lt;/a&gt;&lt;/li&gt;<br>
    {% endif %}<br>
    {% endfor %}<br>
    $ python manage.py runserver<br>
    $ vim women/views.py<br>
    $ cat women/views.py<br>
    from django.http import HttpResponse, HttpResponseNotFound, Http404<br>
    from django.shortcuts import render, redirect, get_object_or_404<br>
    from .models import *<br>
    ...<br>
    #def show_post(request, post_id):<br>
    def show_post(request, post_slug):<br>
    #return HttpResponse(f"Отображение статьи с id = {post_id}")<br>
    #post=get_object_or_404(Women, pk=post_id)<br>
    post=get_object_or_404(Women, slug=post_slug)<br>
    context={'post':post,<br>
    'menu':menu,<br>
    'title':post.title,<br>
    'cat_selected':post.cat_id,}<br>
    return render(request, 'women/post.html', context=context)<br>
    ...<br>
    $ touch women/templates/women/post.html<br>
    $ vim women/templates/women/post.html<br>
    $ cat women/templates/women/post.html<br>
    {% extends 'women/base.html' %}<br>
    {% block content %}<br>
    &lt;h1&gt;{{post.title}}&lt;/h1&gt;<br>
    {% if post.photo %}<br>
    &lt;p&gt;&lt;img class="img-article-left thumb" src="{{post.photo.url}}"&gt;&lt;/p&gt;<br>
    {% endif %}<br>
    {{post.content|linebreaks}}<br>
    {% endblock %}<br>
    $ vim women/models.py<br>
    $ cat women/models.py<br>
    ...<br>
    class Women(models.Model):<br>
    """docstring for Women"""<br>
    title=models.CharField(max_length=255, verbose_name="Заголовок")<br>
    slug=models.SlugField(max_length=255, unique=True, db_index=True, verbose_name="URL")<br>
    content=models.TextField(blank=True, verbose_name="Текст статьи")<br>
    photo=models.ImageField(upload_to="photos/%Y/%m/%d/", verbose_name="Фото")<br>
    time_create=models.DateTimeField(auto_now_add=True, verbose_name="Время создания")<br>
    time_update=models.DateTimeField(auto_now=True, verbose_name="Время изменения")<br>
    is_published=models.BooleanField(default=True, verbose_name="Публикация")<br>
    #cat=models.ForeignKey('Category', on_delete=models.PROTECT, null=True, verbose_name="Категории")<br>
    cat=models.ForeignKey('Category', on_delete=models.PROTECT, verbose_name="Категории")<br>
    def __str__(self):<br>
    return self.title<br>
    def get_absolute_url(self):<br>
    return reverse('post', kwargs={'post_slug':self.slug})<br>
    ...<br>
    class Category(models.Model):<br>
    name=models.CharField(max_length=100, db_index=True, verbose_name="Категория")<br>
    slug=models.SlugField(max_length=255, unique=True, db_index=True, verbose_name="URL")<br>
    ...<br>
    $ vim women/admin.py<br>
    $ cat women/admin.py<br>
    ...<br>
    class WomenAdmin(admin.ModelAdmin):<br>
    &nbsp;&nbsp;list_display = ('id', 'title', 'time_create', 'photo', 'is_published')<br>
    &nbsp;&nbsp;list_display_links = ('id', 'title')<br>
    &nbsp;&nbsp;search_fields = ('title', 'content')<br>
    &nbsp;&nbsp;list_editable = ('is_published',)<br>
    &nbsp;&nbsp;list_filter = ('is_published', 'time_create')<br>
    &nbsp;&nbsp;prepopulated_fields = {"slug": ("title",)}<br>
    class CategoryAdmin(admin.ModelAdmin):<br>
    &nbsp;&nbsp;list_display = ('id', 'name')<br>
    &nbsp;&nbsp;list_display_links = ('id', 'name')<br>
    &nbsp;&nbsp;search_fields = ('name',)<br>
    &nbsp;&nbsp;prepopulated_fields = {"slug": ("name",)}<br>
    ...<br>
    $ vim women/urls.py<br>
    $ cat women/urls.py<br>
    ...<br>
    urlpatterns = [<br>
    #path('', index), #http://127.0.0.1:8000/women/<br>
    #path('home/', index, name='home'), #http://127.0.0.1:8000/<br>
    path('', index, name='home'), #http://127.0.0.1:8000/<br>
    #path('cats/', categories), #http://127.0.0.1:8000/women/cats/<br>
    #path('cats/', categories), #http://127.0.0.1:8000/cats/<br>
    #path('cats/&lt;int:catid&gt;/', categories), #http://127.0.0.1:8000/cats/1/<br>
    #re_path(r'^archive/(?P&lt;year&gt;[0-9]{4})/', archive), #http://127.0.0.1:8000/archive/2020/<br>
    path('about/', about, name='about'), #http://127.0.0.1:8000/<br>
    path('addpage/', addpage, name='add_page'),<br>
    path('contact/', contact, name='contact'),<br>
    path('login/', login, name='login'),<br>
    #path('post/&lt;int:post_id&gt;/', show_post, name='post'),<br>
    path('post/&lt;slug:post_slug&gt;/', show_post, name='post'),<br>
    path('category/&lt;int:cat_id&gt;/', show_category, name='category'),<br>
    ]<br>
    $ rm -rf women/migrations/000*.py<br>
    $ rm -rf db.sqlite3<br>
    $ python manage.py makemigrations<br>
    $ python manage.py migrate<br>
    $ python manage.py createsuperuser<br>
    $ python manage.py runserver<br>
    <strong>Decision:</strong><br>
    $ vim women/views.py<br>
    $ cat women/views.py<br>
    from django.http import HttpResponse, HttpResponseNotFound, Http404<br>
    from django.shortcuts import render, redirect, get_object_or_404<br>
    from .forms import *<br>
    from .models import *<br>
    ...<br>
    return HttpResponseNotFound("&lt;h1&gt;Страница не найдена&lt;/h1&gt;")<br>
    def addpage(request):<br>
    #return HttpResponse("Добавление статьи")<br>
    #return render(request, 'women/addpage.html', {'menu':menu, 'title':'Добавление статьи'})<br>
    #form=AddPostForm()<br>
    if request.method=='POST':<br>
    form=AddPostForm(request.POST)<br>
    if form.is_valid():<br>
    #print(form.cleaned_data)<br>
    try:<br>
    Women.objects.create(**form.cleaned_data)<br>
    return redirect('home')<br>
    except:<br>
    form.add_error(None,'Ошибка добавления поста')<br>
    else:<br>
    form=AddPostForm()<br>
    return render(request, 'women/addpage.html', {'form':form,'menu':menu, 'title':'Добавление статьи'})<br>
    def contact(request):<br>
    ...<br>
    $ touch women/templates/women/addpage.html<br>
    $ vim women/templates/women/addpage.html<br>
    $ cat women/templates/women/addpage.html<br>
    {% extends 'women/base.html' %}<br>
    {% block content %}<br>
    &lt;h1&gt;{{title}}&lt;/h1&gt;<br>
    &lt;form action="{% url 'add_page' %}" method="post"&gt;<br>
    {% csrf_token %}<br>
    &lt;div class="form-error"&gt;{{ form.non_field_errors }}&lt;/div&gt;<br>
    {% for f in form %}<br>
    &lt;p&gt;&lt;label class="form-label" for="{{ f.id_for_label }}"&gt;{{f.label}}:&lt;/label&gt;{{ f }}&lt;/p&gt;<br>
    &lt;div class="form-error"&gt;{{ f.errors }}&lt;/div&gt;<br>
    {% endfor %}<br>
    &lt;button type="submit"&gt;Добавить&lt;/button&gt;<br>
    &lt;/form&gt;<br>
    {% endblock %}<br>
    $ touch women/forms.py<br>
    $ vim women/forms.py<br>
    $ cat women/forms.py<br>
    from django import forms<br>
    from .models import *<br>
    class AddPostForm(forms.Form):<br>
    &nbsp;&nbsp;title=forms.CharField(max_length=255, label="Заголовок", widget=forms.TextInput(attrs={'class':'form-input'}))<br>
    &nbsp;&nbsp;slug=forms.SlugField(max_length=255, label="URL")<br>
    &nbsp;&nbsp;content=forms.CharField(widget=forms.Textarea(attrs={'cols':60, 'rows':10}), label="Контент")<br>
    &nbsp;&nbsp;is_published=forms.BooleanField(label="Публикация", required=False, initial=True)<br>
    &nbsp;&nbsp;cat=forms.ModelChoiceField(queryset=Category.objects.all(), label="Категория", empty_label="Категория не выбрана")<br>
    $ python manage.py runserver<br>
    <strong>Decision:</strong><br>
    $ vim women/forms.py<br>
    $ cat women/forms.py<br>
    from django import forms<br>
    from django.core.exceptions import ValidationError<br>
    from .models import *<br>
    #class AddPostForm(forms.Form):<br>
    &nbsp;&nbsp;#title=forms.CharField(max_length=255, label="Заголовок", widget=forms.TextInput(attrs={'class':'form-input'}))<br>
    &nbsp;&nbsp;#slug=forms.SlugField(max_length=255, label="URL")<br>
    &nbsp;&nbsp;#content=forms.CharField(widget=forms.Textarea(attrs={'cols':60, 'rows':10}), label="Контент")<br>
    &nbsp;&nbsp;#is_published=forms.BooleanField(label="Публикация", required=False, initial=True)<br>
    &nbsp;&nbsp;#cat=forms.ModelChoiceField(queryset=Category.objects.all(), label="Категория", empty_label="Категория не выбрана")<br>
    class AddPostForm(forms.ModelForm):<br>
    &nbsp;&nbsp;def __init__(self, *args, **kwargs):<br>
    &nbsp;&nbsp;&nbsp;&nbsp;super().__init__(*args, **kwargs)<br>
    &nbsp;&nbsp;&nbsp;&nbsp;self.fields['cat'].empty_label="Категория не выбрана"<br>
    &nbsp;&nbsp;class Meta:<br>
    &nbsp;&nbsp;&nbsp;&nbsp;model=Women<br>
    &nbsp;&nbsp;&nbsp;&nbsp;#fields='__all__'<br>
    &nbsp;&nbsp;&nbsp;&nbsp;fields=['title', 'slug', 'content', 'photo', 'is_published', 'cat']<br>
    &nbsp;&nbsp;&nbsp;&nbsp;widgets={<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;'title':forms.TextInput(attrs={'class':'form-input'}),<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;'content':forms.Textarea(attrs={'cols':60,'rows':10}),<br>
    &nbsp;&nbsp;&nbsp;&nbsp;}<br>
    &nbsp;&nbsp;def clean_title(self):<br>
    &nbsp;&nbsp;&nbsp;&nbsp;title=self.cleaned_data['title']<br>
    &nbsp;&nbsp;&nbsp;&nbsp;if len(title)&gt;200:<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;raise ValidationError('Длина превышает 200 символов')<br>
    &nbsp;&nbsp;&nbsp;&nbsp;return title<br>
    $ vim women/views.py<br>
    $ cat women/views.py<br>
    ...<br>
    def addpage(request):<br>
    #return HttpResponse("Добавление статьи")<br>
    #return render(request, 'women/addpage.html', {'menu':menu, 'title':'Добавление статьи'})<br>
    #form=AddPostForm()<br>
    if request.method=='POST':<br>
    #form=AddPostForm(request.POST)<br>
    form=AddPostForm(request.POST, request.FILES)<br>
    if form.is_valid():<br>
    #print(form.cleaned_data)<br>
    #try:<br>
    #Women.objects.create(**form.cleaned_data)<br>
    form.save()<br>
    return redirect('home')<br>
    #except:<br>
    #form.add_error(None,'Ошибка добавления поста')<br>
    else:<br>
    form=AddPostForm()<br>
    return render(request, 'women/addpage.html', {'form':form,'menu':menu, 'title':'Добавление статьи'})<br>
    ...<br>
    $ vim women/templates/women/addpage.html<br>
    $ cat women/templates/women/addpage.html<br>
    ...<br>
    &lt;h1&gt;{{title}}&lt;/h1&gt;<br>
    &lt;form action="{% url 'add_page' %}" method="post" enctype="multipart/form-data"&gt;<br>
    {% csrf_token %}<br>
    ...<br>
    $ python manage.py runserver<br>
    <strong>Decision:</strong><br>
    $ vim women/views.py<br>
    $ cat women/views.py<br>
    from django.http import HttpResponse, HttpResponseNotFound, Http404<br>
    from django.shortcuts import render, redirect, get_object_or_404<br>
    from django.urls import reverse_lazy<br>
    from django.views.generic import ListView, DetailView, CreateView<br>
    from .forms import *<br>
    from .models import *<br>
    ...<br>
    #def index(request):<br>
    #return render(request, 'women/index.html', {'title':'Главная страница'})<br>
    #posts=Women.objects.all()<br>
    #cats=Category.objects.all()<br>
    #context={'posts':posts,&nbsp;<br>
    #'cats':cats,<br>
    #'menu':menu,&nbsp;<br>
    #'title':'Главная страница',<br>
    #'cat_selected':0}<br>
    #return render(request, 'women/index.html', context=context)<br>
    class WomenHome(ListView):<br>
    model=Women<br>
    template_name='women/index.html'<br>
    context_object_name='posts'<br>
    #extra_context={'title':'Главная страница'}<br>
    def get_context_data(self, *, object_list=None, **kwargs):<br>
    context=super().get_context_data(**kwargs)<br>
    context['menu']=menu<br>
    context['title']='Главная страница'<br>
    context['cat_selected']=0<br>
    return context<br>
    def get_queryset(self):<br>
    return Women.objects.filter(is_published=True)<br>
    ...<br>
    #def addpage(request):<br>
    #return HttpResponse("Добавление статьи")<br>
    #return render(request, 'women/addpage.html', {'menu':menu, 'title':'Добавление статьи'})<br>
    #form=AddPostForm()<br>
    #if request.method=='POST':<br>
    #form=AddPostForm(request.POST)<br>
    #form=AddPostForm(request.POST, request.FILES)<br>
    #if form.is_valid():<br>
    #print(form.cleaned_data)<br>
    #try:<br>
    #Women.objects.create(**form.cleaned_data)<br>
    #form.save()<br>
    #return redirect('home')<br>
    #except:<br>
    #form.add_error(None,'Ошибка добавления поста')<br>
    #else:<br>
    #form=AddPostForm()<br>
    #return render(request, 'women/addpage.html', {'form':form,'menu':menu, 'title':'Добавление статьи'})<br>
    class AddPage(CreateView):<br>
    form_class=AddPostForm<br>
    template_name='women/addpage.html'<br>
    success_url=reverse_lazy('home')<br>
    def get_context_data(self, *, object_list=None, **kwargs):<br>
    context=super().get_context_data(**kwargs)<br>
    context['title']='Добав статьи'<br>
    context['menu']=menu<br>
    return context<br>
    ...<br>
    #def show_post(request, post_slug):<br>
    #return HttpResponse(f"Отображение статьи с id = {post_id}")<br>
    #post=get_object_or_404(Women, pk=post_id)<br>
    #post=get_object_or_404(Women, slug=post_slug)<br>
    #context={'post':post,<br>
    #'menu':menu,<br>
    #'title':post.title,<br>
    #'cat_selected':post.cat_id,}<br>
    #return render(request, 'women/post.html', context=context)<br>
    class ShowPost(DetailView):<br>
    model=Women<br>
    template_name='women/post.html'<br>
    slug_url_kwarg='post_slug'<br>
    context_object_name='post'<br>
    def get_context_data(self, *, object_list=None, **kwargs):<br>
    context=super().get_context_data(**kwargs)<br>
    context['title']=context['post']<br>
    context['menu']=menu<br>
    return context<br>
    ...<br>
    #def show_category(request, cat_id):<br>
    #posts=Women.objects.filter(cat_id=cat_id)<br>
    #cats=Category.objects.all()<br>
    #if len(posts)==0:<br>
    #raise Http404()<br>
    #context={'posts':posts,<br>
    #'cats':cats,<br>
    #'menu':menu,<br>
    #'title':'Главная страница',<br>
    #'cat_selected':cat_id,}<br>
    #return render(request, 'women/index.html', context=context)<br>
    class WomenCategory(ListView):<br>
    model=Women<br>
    template_name='women/index.html'<br>
    context_object_name='posts'<br>
    allow_empty=False<br>
    def get_queryset(self):<br>
    return Women.objects.filter(cat__slug=self.kwargs['cat_slug'], is_published=True)<br>
    def get_context_data(self, *, object_list=None, **kwargs):<br>
    context=super().get_context_data(**kwargs)<br>
    context['title']='Категория - ' + str(context['posts'][0].cat)<br>
    context['menu']=menu<br>
    context['cat_selected']=context['posts'][0].cat_id<br>
    return context<br>
    $ vim women/urls.py<br>
    $ cat women/urls.py<br>
    ...<br>
    urlpatterns = [<br>
    #path('', index), #http://127.0.0.1:8000/women/<br>
    #path('home/', index, name='home'), #http://127.0.0.1:8000/<br>
    #path('', index, name='home'), #http://127.0.0.1:8000/<br>
    path('', WomenHome.as_view(), name='home'), #http://127.0.0.1:8000/<br>
    #path('cats/', categories), #http://127.0.0.1:8000/women/cats/<br>
    #path('cats/', categories), #http://127.0.0.1:8000/cats/<br>
    #path('cats/&lt;int:catid&gt;/', categories), #http://127.0.0.1:8000/cats/1/<br>
    #re_path(r'^archive/(?P&lt;year&gt;[0-9]{4})/', archive), #http://127.0.0.1:8000/archive/2020/<br>
    path('about/', about, name='about'), #http://127.0.0.1:8000/<br>
    #path('addpage/', addpage, name='add_page'),<br>
    path('addpage/', AddPage.as_view(), name='add_page'),<br>
    path('contact/', contact, name='contact'),<br>
    path('login/', login, name='login'),<br>
    #path('post/&lt;int:post_id&gt;/', show_post, name='post'),<br>
    #path('post/&lt;slug:post_slug&gt;/', show_post, name='post'),<br>
    path('post/&lt;slug:post_slug&gt;/', ShowPost.as_view(), name='post'),<br>
    #path('category/&lt;int:cat_id&gt;/', show_category, name='category'),<br>
    path('category/&lt;slug:cat_slug&gt;/', WomenCategory.as_view(), name='category'),<br>
    ]<br>
    $ vim women/models.py<br>
    $ cat women/models.py<br>
    ...<br>
    def get_absolute_url(self):<br>
    #return reverse('category', kwargs={'cat_id':self.pk})<br>
    return reverse('category', kwargs={'cat_slug':self.slug})<br>
    ...<br>
    $ python manage.py runserver<br>
    <strong>Decision:</strong><br>
    $ vim women/views.py<br>
    $ cat women/views.py<br>
    from django.http import HttpResponse, HttpResponseNotFound, Http404<br>
    from django.shortcuts import render, redirect, get_object_or_404<br>
    from django.urls import reverse_lazy<br>
    from django.views.generic import ListView, DetailView, CreateView<br>
    from django.contrib.auth.mixins import LoginRequiredMixin<br>
    #from django.contrib.auth.decorators import login_required<br>
    from .forms import *<br>
    from .models import *<br>
    from .utils import *<br>
    ...<br>
    #menu=[{'title':"О сайте", 'url_name':'about'},&nbsp;<br>
    #{'title':"Добавить статью", 'url_name':'add_page'},<br>
    #{'title':"Обратная связь", 'url_name':'contact'},<br>
    #{'title':"Войти", 'url_name':'login'}]<br>
    ...<br>
    #class WomenHome(ListView):<br>
    class WomenHome(DataMixin, ListView):<br>
    model=Women<br>
    template_name='women/index.html'<br>
    context_object_name='posts'<br>
    #extra_context={'title':'Главная страница'}<br>
    def get_context_data(self, *, object_list=None, **kwargs):<br>
    context=super().get_context_data(**kwargs)<br>
    #context['menu']=menu<br>
    #context['title']='Главная страница'<br>
    #context['cat_selected']=0<br>
    c_def = self.get_user_context(title="Главная страница")<br>
    return dict(list(context.items())+list(c_def.items()))<br>
    def get_queryset(self):<br>
    return Women.objects.filter(is_published=True)<br>
    ...<br>
    #@login_required<br>
    def about(request):<br>
    return render(request, 'women/about.html', {'menu':menu, 'title':'О сайте'})<br>
    ...<br>
    #class AddPage(CreateView):<br>
    class AddPage(LoginRequiredMixin, DataMixin, CreateView):<br>
    form_class=AddPostForm<br>
    template_name='women/addpage.html'<br>
    success_url=reverse_lazy('home')<br>
    login_url = reverse_lazy('home')<br>
    raise_exception = True<br>
    def get_context_data(self, *, object_list=None, **kwargs):<br>
    context=super().get_context_data(**kwargs)<br>
    c_def = self.get_user_context(title="Добавление статьи")<br>
    return dict(list(context.items())+list(c_def.items()))<br>
    ...<br>
    class ShowPost(DataMixin, DetailView):<br>
    model=Women<br>
    template_name='women/post.html'<br>
    slug_url_kwarg='post_slug'<br>
    context_object_name='post'<br>
    def get_context_data(self, *, object_list=None, **kwargs):<br>
    context=super().get_context_data(**kwargs)<br>
    c_def = self.get_user_context(title=context['post'])<br>
    return dict(list(context.items())+list(c_def.items()))<br>
    ...<br>
    class WomenCategory(DataMixin, ListView):<br>
    model=Women<br>
    template_name='women/index.html'<br>
    context_object_name='posts'<br>
    allow_empty=False<br>
    def get_queryset(self):<br>
    return Women.objects.filter(cat__slug=self.kwargs['cat_slug'], is_published=True)<br>
    def get_context_data(self, *, objecft_list=None, **kwargs):<br>
    context=super().get_context_data(**kwargs)<br>
    c_def = self.get_user_context(title='Категория - ' + str(context['posts'][0].cat), cat_selected=context['posts'][0].cat_id)<br>
    return dict(list(context.items())+list(c_def.items()))<br>
    $ touch women/utils.py<br>
    $ vim women/utils.py<br>
    $ cat women/utils.py<br>
    from .models import *<br>
    from django.db.models import Count<br>
    menu=[{'title':"О сайте", 'url_name':'about'},&nbsp;<br>
    {'title':"Добавить статью", 'url_name':'add_page'},<br>
    {'title':"Обратная связь", 'url_name':'contact'},<br>
    {'title':"Войти", 'url_name':'login'}]<br>
    class DataMixin:<br>
    def get_user_context(self, **kwargs):<br>
    context = kwargs<br>
    #cats = Category.objects.all()<br>
    cats = Category.objects.annotate(Count('women'))<br>
    #context['menu']=menu<br>
    user_menu = menu.copy()<br>
    if not self.request.user.is_authenticated:<br>
    user_menu.pop(1)<br>
    context['menu']=user_menu<br>
    context['cats']=cats<br>
    if 'cat_selected' not in context:<br>
    context['cat_selected'] = 0<br>
    return context<br>
    $ vim women/templates/women/base.html<br>
    $ cat women/templates/women/base.html<br>
    ...<br>
    {% if cat_selected == 0 %}<br>
    &lt;li class="selected"&gt;Все категории&lt;/li&gt;<br>
    {% else %}<br>
    &lt;li&gt;&lt;a href="{% url 'home' %}"&gt;Все категории&lt;/a&gt;&lt;/li&gt;<br>
    {% endif %}<br>
    {% for c in cats %}<br>
    {% if c.women__count &gt; 0 %}<br>
    {% if c.pk == cat_selected %}<br>
    &lt;li class="selected"&gt;{{c.name}}&lt;/li&gt;<br>
    {% else %}<br>
    &lt;li class=""&gt;&lt;a href="{{ c.get_absolute_url }}"&gt;{{c.name}}&lt;/a&gt;&lt;/li&gt;<br>
    {% endif %}<br>
    {% endif %}<br>
    {% endfor %}<br>
    &lt;li class="share"&gt;&lt;p&gt;Наш канал&lt;/p&gt;&lt;a class="share-yt" href="https://www.youtube.com/channel/UClJzWfGWuGJL2t-3dYKcHTA/playlists" target="_blank" rel="nofollow"&gt;&lt;/a&gt;&lt;/li&gt;<br>
    ...<br>
    $ python manage.py runserver<br>
    <strong>Decision:</strong><br>
    $ python manage.py shell<br>
    &gt;&gt;&gt; from django.core.paginator import Paginator<br>
    &gt;&gt;&gt; women=['Nicol Kidman', 'Марго Робби', '']<br>
    &gt;&gt;&gt; women=['Nicol Kidman', 'Марго Робби', 'Анжелика Джоли']<br>
    &gt;&gt;&gt; p= Paginator(women, 3)<br>
    &gt;&gt;&gt; p.count<br>
    3<br>
    &gt;&gt;&gt; p.num.pages<br>
    &gt;&gt;&gt; p.num_pages<br>
    1<br>
    &gt;&gt;&gt; p.page_range<br>
    range(1, 2)<br>
    &gt;&gt;&gt; p1=p.page(1)<br>
    &gt;&gt;&gt; p1.object_list<br>
    ['Nicol Kidman', 'Марго Робби', 'Анжелика Джоли']<br>
    &gt;&gt;&gt; p1.has_next()<br>
    &gt;&gt;&gt; p1.has_previous()<br>
    &gt;&gt;&gt; p1.has_other_pages()<br>
    &gt;&gt;&gt; p1.next_page_number()<br>
    &gt;&gt;&gt; p1.previous_page_number()<br>
    &gt;&gt;&gt; quit()<br>
    $ vim women/views.py<br>
    $ cat women/views.py<br>
    from django.http import HttpResponse, HttpResponseNotFound, Http404<br>
    from django.shortcuts import render, redirect, get_object_or_404<br>
    from django.urls import reverse_lazy<br>
    from django.views.generic import ListView, DetailView, CreateView<br>
    from django.contrib.auth.mixins import LoginRequiredMixin<br>
    #from django.contrib.auth.decorators import login_required<br>
    from django.core.paginator import Paginator<br>
    from .forms import *<br>
    from .models import *<br>
    from .utils import *<br>
    ...<br>
    class WomenHome(DataMixin, ListView):<br>
    #paginate_by = 2<br>
    model=Women<br>
    template_name='women/index.html'<br>
    context_object_name='posts'<br>
    #extra_context={'title':'Главная страница'}<br>
    def get_context_data(self, *, object_list=None, **kwargs):<br>
    context=super().get_context_data(**kwargs)<br>
    #context['menu']=menu<br>
    #context['title']='Главная страница'<br>
    #context['cat_selected']=0<br>
    c_def = self.get_user_context(title="Главная страница")<br>
    return dict(list(context.items())+list(c_def.items()))<br>
    def get_queryset(self):<br>
    return Women.objects.filter(is_published=True)<br>
    #@login_required<br>
    def about(request):<br>
    #return render(request, 'women/about.html', {'menu':menu, 'title':'О сайте'})<br>
    contact_list=Women.objects.all()<br>
    paginator=Paginator(contact_list,2)<br>
    page_number=request.GET.get('page')<br>
    page_obj=paginator.get_page(page_number)<br>
    return render(request, 'women/about.html', {'page_obj':page_obj, 'menu':menu, 'title':'О сайте'})<br>
    ...<br>
    class WomenCategory(DataMixin, ListView):<br>
    #paginate_by=2<br>
    model=Women<br>
    ...<br>
    $ vim women/templates/women/about.html<br>
    $ cat women/templates/women/about.html<br>
    {% extends 'women/base.html' %}<br>
    {% block content %}<br>
    &lt;h1&gt;{{title}}&lt;/h1&gt;<br>
    {% endblock %}<br>
    $ vim women/static/women/css/style.css<br>
    $ cat women/static/women/css/style.css<br>
    ...<br>
    .form-button {<br>
    min-width: 200px;<br>
    font-size: 16px;<br>
    }<br>
    .list-pages {<br>
    text-align: center;<br>
    margin: 0 0 20px 0;<br>
    }<br>
    .list-pages ul {<br>
    margin: 20px 0 0 0;<br>
    padding: 0;<br>
    list-style: none;<br>
    }<br>
    .list-pages ul li {<br>
    display: inline-block;<br>
    margin: 0 20px 0 0;<br>
    }<br>
    .list-pages a {<br>
    color: #000;<br>
    font-size: 24px;<br>
    text-decoration: none;<br>
    }<br>
    .list-pages .page-num, .page-num-selected {<br>
    display: inline-block;<br>
    width: 60px;<br>
    height: 44px;<br>
    padding: 16px 0 0 0;<br>
    border: 1px solid #d0d0d0;<br>
    border-radius: 30px;<br>
    }<br>
    .list-pages .page-num:hover {<br>
    box-shadow: 3px 3px 1px #d0d0d0;&nbsp;<br>
    }<br>
    .list-pages .page-num-selected {<br>
    border: none;<br>
    color: #000;<br>
    font-size: 20px;<br>
    }<br>
    .list-pages .page-num-selected:hover {<br>
    box-shadow: none;&nbsp;<br>
    }<br>
    $ vim women/templates/women/base.html<br>
    $ cat women/templates/women/base.html<br>
    ...<br>
    {% endblock %}<br>
    {% if page_obj.has_other_pages %}<br>
    &lt;nav class="list-pages"&gt;<br>
    &lt;ul&gt;<br>
    {% if page_obj.has_previous %}<br>
    &lt;li class="page-num"&gt;&lt;a href="?page={{ page_obj.previous_page_number }}"&gt;&lt;&lt;/a&gt;&lt;/li&gt;<br>
    {% endif %}<br>
    {% for p in paginator.page_range %}<br>
    {% if page_obj.number == p %}<br>
    &lt;li class="page-num page-num-selected"&gt;{{ p }}&lt;/li&gt;<br>
    {% elif p &gt;= page_obj.number|add:-2 and p &lt;= page_obj.number|add:2 %}<br>
    &lt;li class="page-num"&gt;&lt;a href="?page={{ p }}"&gt;{{ p }}&lt;/a&gt;&lt;/li&gt;<br>
    {% endif %}<br>
    {% endfor %}<br>
    {% if page_obj.has_next %}<br>
    &lt;li class="page-num"&gt;&lt;a href="?page={{ page_obj.next_page_number }}"&gt;&gt;&lt;/a&gt;&lt;/li&gt;<br>
    {% endif %}<br>
    &lt;/ul&gt;<br>
    &lt;/nav&gt;<br>
    {% endif %}<br>
    &lt;/div&gt;<br>
    ...<br>
    $ vim women/utils.py<br>
    $ cat women/utils.py<br>
    ...<br>
    class DataMixin:<br>
    #paginate_by=30<br>
    paginate_by=2<br>
    def get_user_context(self, **kwargs):<br>
    ...<br>
    $ vim women/models.py<br>
    $ cat women/models.py<br>
    ...<br>
    class Meta:<br>
    verbose_name='Известные женщины'<br>
    verbose_name_plural='Известные женщины'<br>
    #ordering=['time_create','title']<br>
    #ordering=['-time_create','title']<br>
    ordering=['id']<br>
    class Category(models.Model):<br>
    ...<br>
    $ python manage.py runserver<br>
    <strong>Decision:</strong><br>
    $ vim women/templates/women/base.html<br>
    $ cat women/templates/women/base.html<br>
    ...<br>
    {% block mainmenu %}<br>
    &lt;div class="header"&gt;<br>
    &lt;ul id="mainmenu" class="mainmenu"&gt;<br>
    &lt;li class="logo"&gt;&lt;a href="{% url 'home' %}"&gt;&lt;div class="logo"&gt;&lt;/div&gt;&lt;/a&gt;&lt;/li&gt;<br>
    {% for m in menu %}<br>
    &lt;li&gt;&lt;a href="{% url m.url_name %}"&gt;{{m.title}}&lt;/a&gt;&lt;/li&gt;<br>
    {% endfor %}<br>
    &lt;li class="last"&gt;&lt;a href="{% url 'register' %}"&gt;Регистрация&lt;/a&gt;|&lt;a href="{% url 'login' %}"&gt;Войти&lt;/a&gt;&lt;/li&gt;<br>
    &lt;/ul&gt;<br>
    &lt;div class="clear"&gt;&lt;/div&gt;<br>
    &lt;/div&gt;<br>
    {% endblock mainmenu %}<br>
    ...<br>
    $ vim women/utils.py<br>
    $ cat women/utils.py<br>
    ...<br>
    menu=[{'title':"О сайте", 'url_name':'about'},&nbsp;<br>
    {'title':"Добавить статью", 'url_name':'add_page'},<br>
    {'title':"Обратная связь", 'url_name':'contact'}<br>
    #{'title':"Войти", 'url_name':'login'}<br>
    ]<br>
    ...<br>
    $ vim women/urls.py<br>
    $ cat women/urls.py<br>
    ...<br>
    [<br>
    path('category/&lt;slug:cat_slug&gt;/', WomenCategory.as_view(), name='category'),<br>
    #path('register/', login, name='register'),<br>
    path('register/', RegisterUser.as_view(), name='register'),<br>
    ]<br>
    $ vim women/views.py<br>
    $ cat women/views.py<br>
    ...<br>
    class RegisterUser(DataMixin, CreateView):<br>
    form_class=UserCreationForm<br>
    template_name='women/register.html'<br>
    success_url=reverse_lazy('login')<br>
    def get_context_data(self, *, object_list=None, **kwargs):<br>
    context=super().get_context_data(**kwargs)<br>
    c_def=self.get_user_context(title="Регистрация")<br>
    return dict(list(context.items())+list(c_def.items()))<br>
    $ touch women/templates/women/register.html<br>
    $ vim women/templates/women/register.html<br>
    $ cat women/templates/women/register.html<br>
    {% extends 'women/base.html' %}<br>
    {% block content %}<br>
    &lt;h1&gt;{{title}}&lt;/h1&gt;<br>
    &lt;form method="post"&gt;<br>
    {% csrf_token %}<br>
    {% for f in form %}<br>
    &lt;p&gt;&lt;label class="form-label" for="{{ f.id_for_label }}"&gt;{{f.label}}:&lt;/label&gt;{{ f }}&lt;/p&gt;<br>
    &lt;div class="form-error"&gt;{{ f.errors }}&lt;/div&gt;<br>
    {% endfor %}<br>
    &lt;button type="submit"&gt;Регистрация&lt;/button&gt;<br>
    &lt;/form&gt;<br>
    {% endblock %}<br>
    $ vim women/forms.py<br>
    $ cat women/forms.py<br>
    from django import forms<br>
    from django.core.exceptions import ValidationError<br>
    from django.contrib.auth.forms import UserCreationForm<br>
    from django.contrib.auth.models import User<br>
    from .models import *<br>
    ...<br>
    class RegisterUserForm(UserCreationForm):<br>
    username=forms.CharField(label='Логин', widget=forms.TextInput(attrs={'class':'form-input'}))<br>
    email=forms.EmailField(label='Email', widget=forms.EmailInput(attrs={'class':'form-input'}))<br>
    password1=forms.CharField(label='Пароль', widget=forms.PasswordInput(attrs={'class':'form-input'}))<br>
    password2=forms.CharField(label='Повтор пароля', widget=forms.PasswordInput(attrs={'class':'form-input'}))<br>
    class Meta:<br>
    model=User<br>
    fields=('username','email','password1','password2')<br>
    #widgets={<br>
    #&nbsp;&nbsp;'username':forms.TextInput(attrs={'class':'form-input'}),<br>
    #&nbsp;&nbsp;'password1':forms.PasswordInput(attrs={'class':'form-input'}),<br>
    #&nbsp;&nbsp;'password2':forms.PasswordInput(attrs={'class':'form-input'}),<br>
    #}<br>
    $ python manage.py runserver<br>
    <strong>Decision:</strong><br>
    $ vim women/views.py<br>
    $ cat women/views.py<br>
    from typing import Any<br>
    from django.forms.models import BaseModelForm<br>
    from django.http import HttpResponse, HttpResponseNotFound, Http404<br>
    from django.shortcuts import render, redirect, get_object_or_404<br>
    from django.urls import reverse_lazy<br>
    from django.views.generic import ListView, DetailView, CreateView<br>
    from django.contrib.auth.mixins import LoginRequiredMixin<br>
    #from django.contrib.auth.decorators import login_required<br>
    from django.core.paginator import Paginator<br>
    #from django.contrib.auth.forms import UserCreationForm<br>
    from django.contrib.auth.views import LoginView<br>
    #from django.contrib.auth.forms import AuthenticationForm<br>
    from django.contrib.auth import logout, login<br>
    ...<br>
    #def login(request):<br>
    #return HttpResponse("Авторизация")<br>
    ...<br>
    return dict(list(context.items())+list(c_def.items()))<br>
    def form_valid(self, form):<br>
    user=form.save()<br>
    login(self.request, user)<br>
    return redirect('home')<br>
    class LoginUser(DataMixin, LoginView):<br>
    form_class=AuthenticationForm<br>
    template_name='women/login.html'<br>
    def get_context_data(self, *, object_list=None, **kwargs):<br>
    context=super().get_context_data(**kwargs)<br>
    c_def=self.get_user_context(title="Авторизация")<br>
    return dict(list(context.items())+list(c_def.items()))<br>
    def get_success_url(self):<br>
    return reverse_lazy('home')<br>
    def logout_user(request):<br>
    logout(request)<br>
    return redirect('login')<br>
    $ vim women/forms.py<br>
    $ cat women/forms.py<br>
    from django import forms<br>
    from django.core.exceptions import ValidationError<br>
    from django.contrib.auth.forms import UserCreationForm<br>
    from django.contrib.auth.models import User<br>
    from django.contrib.auth.forms import AuthenticationForm<br>
    ...<br>
    class LoginUserForm(AuthenticationForm):<br>
    username=forms.CharField(label='Логин', widget=forms.TextInput(attrs={'class':'form-input'}))<br>
    password=forms.CharField(label='Пароль', widget=forms.PasswordInput(attrs={'class':'form-input'}))<br>
    $ touch women/templates/women/login.html<br>
    $ vim women/templates/women/login.html<br>
    $ cat women/templates/women/login.html<br>
    {% extends 'women/base.html' %}<br>
    {% block content %}<br>
    &lt;h1&gt;{{title}}&lt;/h1&gt;<br>
    &lt;form method="post"&gt;<br>
    {% csrf_token %}<br>
    &lt;div class="form-error"&gt;{{ form.non_field_errors }}&lt;/div&gt;<br>
    {% for f in form %}<br>
    &lt;p&gt;&lt;label class="form-label" for="{{ f.id_for_label }}"&gt;{{f.label}}:&lt;/label&gt;{{ f }}&lt;/p&gt;<br>
    &lt;div class="form-error"&gt;{{ f.errors }}&lt;/div&gt;<br>
    {% endfor %}<br>
    &lt;button type="submit"&gt;Войти&lt;/button&gt;<br>
    &lt;/form&gt;<br>
    {% endblock %}<br>
    $ vim women/urls.py<br>
    $ cat women/urls.py<br>
    ...<br>
    urlpatterns = [<br>
    #path('', index), #http://127.0.0.1:8000/women/<br>
    #path('home/', index, name='home'), #http://127.0.0.1:8000/<br>
    #path('', index, name='home'), #http://127.0.0.1:8000/<br>
    path('', WomenHome.as_view(), name='home'), #http://127.0.0.1:8000/<br>
    #path('cats/', categories), #http://127.0.0.1:8000/women/cats/<br>
    #path('cats/', categories), #http://127.0.0.1:8000/cats/<br>
    #path('cats/&lt;int:catid&gt;/', categories), #http://127.0.0.1:8000/cats/1/<br>
    #re_path(r'^archive/(?P&lt;year&gt;[0-9]{4})/', archive), #http://127.0.0.1:8000/archive/2020/<br>
    path('about/', about, name='about'), #http://127.0.0.1:8000/<br>
    #path('addpage/', addpage, name='add_page'),<br>
    path('addpage/', AddPage.as_view(), name='add_page'),<br>
    path('contact/', contact, name='contact'),<br>
    #path('login/', login, name='login'),<br>
    #path('post/&lt;int:post_id&gt;/', show_post, name='post'),<br>
    #path('post/&lt;slug:post_slug&gt;/', show_post, name='post'),<br>
    path('post/&lt;slug:post_slug&gt;/', ShowPost.as_view(), name='post'),<br>
    #path('category/&lt;int:cat_id&gt;/', show_category, name='category'),<br>
    path('category/&lt;slug:cat_slug&gt;/', WomenCategory.as_view(), name='category'),<br>
    #path('register/', login, name='register'),<br>
    path('register/', RegisterUser.as_view(), name='register'),<br>
    path('login/', LoginUser.as_view(), name='login'),<br>
    path('logout/', logout_user, name='logout'),<br>
    ]<br>
    $ vim coolsite/settings.py<br>
    $ cat coolsite/settings.py<br>
    ...<br>
    MEDIA_URL = '/media/'<br>
    #LOGIN_REDIRECT_URL = '/'<br>
    $ vim women/templates/women/base.html<br>
    $ cat women/templates/women/base.html<br>
    ...<br>
    &lt;ul id="mainmenu" class="mainmenu"&gt;<br>
    &lt;li class="logo"&gt;&lt;a href="{% url 'home' %}"&gt;&lt;div class="logo"&gt;&lt;/div&gt;&lt;/a&gt;&lt;/li&gt;<br>
    {% for m in menu %}<br>
    &lt;li&gt;&lt;a href="{% url m.url_name %}"&gt;{{m.title}}&lt;/a&gt;&lt;/li&gt;<br>
    {% endfor %}<br>
    {% if request.user.is_authenticated %}<br>
    &lt;li class="last"&gt;{{user.username}} | &lt;a href="{% url 'logout' %}"&gt;Выйти&lt;/a&gt;&lt;/li&gt;<br>
    {% else %}<br>
    &lt;li class="last"&gt;&lt;a href="{% url 'register' %}"&gt;Регистрация&lt;/a&gt;|&lt;a href="{% url 'login' %}"&gt;Войти&lt;/a&gt;&lt;/li&gt;<br>
    {% endif %}<br>
    &lt;/ul&gt;<br>
    ...<br>
    $ python manage.py runserver<br>
    <strong>Decision:</strong><br>
    $ pip install django-debug-toolbar<br>
    $ vim coolsite/settings.py<br>
    $ cat coolsite/settings.py<br>
    ...<br>
    INSTALLED_APPS = [<br>
    'django.contrib.admin',<br>
    'django.contrib.auth',<br>
    'django.contrib.contenttypes',<br>
    'django.contrib.sessions',<br>
    'django.contrib.messages',<br>
    'django.contrib.staticfiles',<br>
    'debug_toolbar',<br>
    'women.apps.WomenConfig'<br>
    ]<br>
    MIDDLEWARE = [<br>
    'django.middleware.security.SecurityMiddleware',<br>
    'django.contrib.sessions.middleware.SessionMiddleware',<br>
    'django.middleware.common.CommonMiddleware',<br>
    'django.middleware.csrf.CsrfViewMiddleware',<br>
    'django.contrib.auth.middleware.AuthenticationMiddleware',<br>
    'django.contrib.messages.middleware.MessageMiddleware',<br>
    'django.middleware.clickjacking.XFrameOptionsMiddleware',<br>
    'debug_toolbar.middleware.DebugToolbarMiddleware',<br>
    ]<br>
    ...<br>
    INTERNAL_IPS=[<br>
    '127.0.0.1',<br>
    ]<br>
    $ vim coolsite/urls.py<br>
    $ cat coolsite/urls.py<br>
    ...<br>
    if settings.DEBUG:<br>
    import debug_toolbar<br>
    urlpatterns = [<br>
    path('__debug__/', include(debug_toolbar.urls)),<br>
    ] + urlpatterns<br>
    urlpatterns += static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)<br>
    handler404 = pageNotFound<br>
    $ vim women/views.py<br>
    $ cat women/views.py<br>
    ...<br>
    def get_queryset(self):<br>
    return Women.objects.filter(is_published=True).select_related('cat')<br>
    #@login_required<br>
    ...<br>
    class WomenCategory(DataMixin, ListView):<br>
    #paginate_by=2<br>
    model=Women<br>
    template_name='women/index.html'<br>
    context_object_name='posts'<br>
    allow_empty=False<br>
    def get_queryset(self):<br>
    return Women.objects.filter(cat__slug=self.kwargs['cat_slug'], is_published=True).select_related('cat')<br>
    def get_context_data(self, *, object_list=None, **kwargs):<br>
    context=super().get_context_data(**kwargs)<br>
    c = Category.objects.get(slug=self.kwargs['cat_slug'])<br>
    #c_def = self.get_user_context(title='Категория - ' + str(context['posts'][0].cat), cat_selected=context['posts'][0].cat_id)<br>
    c_def = self.get_user_context(title='Категория - ' + str(c.name), cat_selected=c.pk)<br>
    return dict(list(context.items())+list(c_def.items()))<br>
    ...<br>
    $ python manage.py runserver<br>
    <strong>Decision:</strong><br>
    $ mkdir coolsite_cache<br>
    $ vim coolsite/settings.py<br>
    $ cat coolsite/settings.py<br>
    ...<br>
    CACHES = {<br>
    'default':{<br>
    'BACKEND':'django.core.cache.backends.filebased.FileBasedCache',<br>
    'LOCATION':os.path.join(BASE_DIR, 'coolsite_cache'),<br>
    }<br>
    }<br>
    $ vim women/urls.py<br>
    $ cat women/urls.py<br>
    from django.urls import path, re_path<br>
    from .views import *<br>
    from django.views.decorators.cache import cache_page<br>
    ...<br>
    path('', WomenHome.as_view(), name='home'), #http://127.0.0.1:8000/<br>
    #path('', cache_page(60)(WomenHome.as_view()), name='home'),<br>
    ...<br>
    $ vim women/utils.py<br>
    $ cat women/utils.py<br>
    from .models import *<br>
    from django.db.models import Count<br>
    from django.core.cache import cache<br>
    ...<br>
    context = kwargs<br>
    #cats = Category.objects.all()<br>
    #cats = Category.objects.annotate(Count('women'))<br>
    #context['menu']=menu<br>
    cats = cache.get('cats')<br>
    if not cats:<br>
    cats = Category.objects.annotate(Count('women'))<br>
    cache.set('cats', cats, 60)<br>
    user_menu = menu.copy()<br>
    ...<br>
    $ python manage.py runserver<br>
    <strong>Decision:</strong><br>
    $ pip install django-simple-captcha<br>
    $ vim women/views.py<br>
    $ cat women/views.py<br>
    ...<br>
    from django.views.generic import ListView, DetailView, CreateView, FormView<br>
    ...<br>
    class ContactFormView(DataMixin, FormView):<br>
    form_class = ContactForm<br>
    template_name = 'women/contact.html'<br>
    success_url = reverse_lazy('home')<br>
    def get_context_data(self, *, object_list=None, **kwargs):<br>
    context = super().get_context_data(**kwargs)<br>
    c_def = self.get_user_context(title="Обратная связь")<br>
    return dict(list(context.items()) + list(c_def.items()))<br>
    def form_valid(self, form):<br>
    print(form.cleaned_data)<br>
    return redirect('home')<br>
    $ vim women/forms.py<br>
    $ cat women/forms.py<br>
    ...<br>
    from django.contrib.auth.forms import AuthenticationForm<br>
    from captcha.fields import CaptchaField<br>
    ...<br>
    class ContactForm(forms.Form):<br>
    name = forms.CharField(label='Имя', max_length=255)<br>
    email = forms.EmailField(label='Email')<br>
    content = forms.CharField(widget=forms.Textarea(attrs={'cols': 60, 'rows': 10}))<br>
    capatcha = CaptchaField()<br>
    $ vim women/urls.py<br>
    $ cat women/urls.py<br>
    from django.urls import path, re_path<br>
    from .views import *<br>
    from django.views.decorators.cache import cache_page<br>
    ...<br>
    #path('contact/', contact, name='contact'),<br>
    path('contact/', ContactFormView.as_view(), name='contact'),<br>
    ...<br>
    $ touch women/templates/women/contact.html<br>
    $ vim women/templates/women/contact.html<br>
    $ cat women/templates/women/contact.html<br>
    {% extends 'women/base.html' %}<br>
    {% block content %}<br>
    &lt;h1&gt;{{title}}&lt;/h1&gt;<br>
    &lt;form method="post"&gt;<br>
    {% csrf_token %}<br>
    &lt;div class="form-error"&gt;{{ form.non_field_errors }}&lt;/div&gt;<br>
    {% for f in form %}<br>
    &lt;p&gt;&lt;label class="form-label" for="{{ f.id_for_label }}"&gt;{{f.label}}:&lt;/label&gt;{{ f }}&lt;/p&gt;<br>
    &lt;div class="form-error"&gt;{{ f.errors }}&lt;/div&gt;<br>
    {% endfor %}<br>
    &lt;button type="submit"&gt;Отправить&lt;/button&gt;<br>
    &lt;/form&gt;<br>
    {% endblock %}<br>
    $ vim coolsite/settings.py<br>
    $ cat coolsite/settings.py<br>
    ...<br>
    INSTALLED_APPS = [<br>
    'django.contrib.admin',<br>
    'django.contrib.auth',<br>
    'django.contrib.contenttypes',<br>
    'django.contrib.sessions',<br>
    'django.contrib.messages',<br>
    'django.contrib.staticfiles',<br>
    'debug_toolbar',<br>
    'captcha',<br>
    'women.apps.WomenConfig'<br>
    ]<br>
    ...<br>
    $ vim coolsite/urls.py<br>
    $ cat coolsite/urls.py<br>
    ...<br>
    path('captcha/', include('captcha.urls')),<br>
    ]<br>
    ...<br>
    $ python manage.py migrate<br>
    $ python manage.py runserver<br>
    <strong>Decision:</strong><br>
    $ mkdir templates<br>
    $ mkdir templates/admin<br>
    $ touch templates/admin/base_site.html<br>
    $ vim templates/admin/base_site.html<br>
    $ cat templates/admin/base_site.html<br>
    {% extends "admin/base.html" %}<br>
    {% load static %}<br>
    {% block extrastyle %}<br>
    &lt;link rel="stylesheet" href="{% static 'css/admin.css' %}"&gt;<br>
    {% endblock %}<br>
    {% block title %}{% if subtitle %}{{ subtitle }} | {% endif %}{{ title }} | {{ site_title|default:_('Django site admin') }}{% endblock %}<br>
    {% block branding %}<br>
    &lt;h1 id="site-name"&gt;&lt;a href="{% url 'admin:index' %}"&gt;{{ site_header|default:_('Django administration') }}&lt;/a&gt;&lt;/h1&gt;<br>
    {% if user.is_anonymous %}<br>
    {% include "admin/color_theme_toggle.html" %}<br>
    {% endif %}<br>
    {% endblock %}<br>
    {% block nav-global %}{% endblock %}<br>
    $ mkdir women/static/css<br>
    $ touch women/static/css/admin.css<br>
    $ vim women/static/css/admin.css<br>
    $ cat women/static/css/admin.css<br>
    #header, .module caption {<br>
    background: #5e3a00;<br>
    }<br>
    $ vim women/admin.py<br>
    $ cat women/admin.py<br>
    from django.contrib import admin<br>
    from .models import *<br>
    from django.utils.safestring import mark_safe<br>
    ...<br>
    class WomenAdmin(admin.ModelAdmin):<br>
    #list_display = ('id', 'title', 'time_create', 'photo', 'is_published')<br>
    list_display = ('id', 'title', 'time_create', 'get_html_photo', 'is_published')<br>
    list_display_links = ('id', 'title')<br>
    search_fields = ('title', 'content')<br>
    list_editable = ('is_published',)<br>
    list_filter = ('is_published', 'time_create')<br>
    prepopulated_fields = {"slug": ("title",)}<br>
    fields = ('title', 'slug', 'cat', 'content', 'photo', 'get_html_photo', 'is_published', 'time_create', 'time_update')<br>
    readonly_fields = ('time_create', 'time_update', 'get_html_photo')<br>
    save_on_top = True<br>
    def get_html_photo(self, object):<br>
    if object.photo:<br>
    return mark_safe(f"&lt;img src='{object.photo.url}' width=50&gt;")<br>
    get_html_photo.short_description="Миниатюра"<br>
    ...<br>
    admin.site.site_title='Админ-панель сайта о женщинах'<br>
    admin.site.site_header='Админ-панель сайта о женщинах 2'<br>
    $ vim coolsite/settings.py<br>
    $ cat coolsite/settings.py<br>
    ...<br>
    TEMPLATES = [<br>
    {<br>
    'BACKEND': 'django.template.backends.django.DjangoTemplates',<br>
    'DIRS': [os.path.join(BASE_DIR, 'templates')],<br>
    'APP_DIRS': True,<br>
    'OPTIONS': {<br>
    'context_processors': [<br>
    'django.template.context_processors.debug',<br>
    'django.template.context_processors.request',<br>
    'django.contrib.auth.context_processors.auth',<br>
    'django.contrib.messages.context_processors.messages',<br>
    ],<br>
    },<br>
    },<br>
    ]<br>
    ...<br>
    $ python manage.py runserver<br>
    <strong>Decision:</strong><br>
    $ deactivate<br>
    <strong>Task:</strong><br>
    Создаем API блога на Django REST Framefork<br>
    <strong>Decision:</strong><br>
    $ vim coolsite/settings<br>
    $ cat coolsite/settings<br>
    ...<br>
    INSTALLED_APPS = [<br>
    'django.contrib.admin',<br>
    'django.contrib.auth',<br>
    'django.contrib.contenttypes',<br>
    'django.contrib.sessions',<br>
    'django.contrib.messages',<br>
    'django.contrib.staticfiles',<br>
    'debug_toolbar',<br>
    'captcha',<br>
    'women.apps.WomenConfig',<br>
    'rest_framework',<br>
    ]<br>
    ...<br>
    $ vim women/serializers.py<br>
    $ cat women/serializers.py<br>
    from rest_framework import serializers<br>
    from django.contrib.auth.models import User<br>
    class UserSerializer(serializers.ModelSerializer):<br>
    class Meta:<br>
    model = User<br>
    fields = ['id', 'username']<br>
    $ vim women/views.py<br>
    $ cat women/views.py<br>
    ...<br>
    from rest_framework import generics<br>
    from . import serializers<br>
    from django.contrib.auth.models import User<br>
    ...<br>
    class UserList(generics.ListAPIView):<br>
    queryset = User.objects.all()<br>
    serializer_class = serializers.UserSerializer<br>
    class UserDetail(generics.RetrieveAPIView):<br>
    queryset = User.objects.all()<br>
    serializer_class = serializers.UserSerializer<br>
    $ vim women/urls.py<br>
    $ cat women/urls.py<br>
    ...<br>
    from rest_framework.urlpatterns import format_suffix_patterns<br>
    from . import views<br>
    urlpatterns = [<br>
    ...<br>
    path('users/', views.UserList.as_view()),<br>
    path('users/&lt;int:pk&gt;/', views.UserDetail.as_view()),<br>
    ]<br>
    urlpatterns = format_suffix_patterns(urlpatterns)<br>
    $ curl http://127.0.0.1:8000/users<br>
    $ vim women/models.py<br>
    $ cat women/models.py<br>
    class Women(models.Model):<br>
    ...<br>
    cat=models.ForeignKey('Category', on_delete=models.PROTECT, verbose_name="Категории")<br>
    owner = models.ForeignKey('auth.User', related_name='womens', on_delete=models.CASCADE)<br>
    ...<br>
    $ python3 manage.py makemigrations women<br>
    It is impossible to add a non-nullable field 'owner' to women without specifying a default. This is because the database needs something to populate existing rows.<br>
    Please select a fix:<br>
    1) Provide a one-off default now (will be set on all existing rows with a null value for this column)<br>
    2) Quit and manually define a default value in models.py.<br>
    Select an option: 2<br>
    $ rm -rf women/migrations/000*.py<br>
    $ rm -rf db.sqlite3<br>
    $ python3 manage.py makemigrations women<br>
    $ python3 manage.py migrate<br>
    $ python3 manage.py createsuperuser<br>
    <strong>Source:</strong><br>
    https://docs.python.org/3/tutorial/venv.html<br>
    https://translated.turbopages.org/proxy_u/en-ru.ru.6b298518-64cb356b-c3e4f7d2-74722d776562/https/stackoverflow.com/questions/5334882/how-to-get-list-of-all-the-tables-in-sqlite-programmatically<br>
    https://django-debug-toolbar.readthedocs.io/en/latest/<br>
    https://pypi.org/project/django-recaptcha/#installation<br>
    https://pythonru.com/uroki/django-rest-api<br>
</p>