# Website on DRF
<p>
    <strong>Task:</strong><br>
    Установка Django Rest Framework<br>
    <strong>Decision:</strong><br>
    $ mkdir drf<br>
    $ cd drf/<br>
    $ vim requirements.txt<br>
    $ cat requirements.txt&nbsp;<br>
    django<br>
    djangorestframework<br>
    djoser<br>
    djangorestframework-simplejwt<br>
    $ pip install -r requirements.txt<br>
    $ django-admin startproject drfsite<br>
    $ cd drfsite/<br>
    $ google-chrome http://127.0.0.1:8000 &amp;<br>
    $ python3 manage.py runserver<br>
    $ python3 manage.py migrate<br>
    $ vim settings.py<br>
    $ cat settings.py<br>
    ...&nbsp;<br>
    #LANGUAGE_CODE = 'en-us'<br>
    LANGUAGE_CODE = 'ru'<br>
    #TIME_ZONE = 'UTC'<br>
    TIME_ZONE = 'Europe/Moscow'<br>
    ...<br>
    $ python3 manage.py startapp women<br>
    $ cat settings.txt<br>
    ...&nbsp;<br>
    INSTALLED_APPS = [<br>
    'django.contrib.admin',<br>
    'django.contrib.auth',<br>
    'django.contrib.contenttypes',<br>
    'django.contrib.sessions',<br>
    'django.contrib.messages',<br>
    'django.contrib.staticfiles',<br>
    'women.apps.WomenConfig',<br>
    ]<br>
    ...<br>
    $ vim women\models.py<br>
    $ cat women\models.py<br>
    from django.db import models<br>
    class Women(models.Model):<br>
    title=models.CharField(max_length=255, verbose_name="Заголовок")<br>
    content=models.TextField(blank=True, verbose_name="Текст статьи")<br>
    time_create=models.DateTimeField(auto_now_add=True, verbose_name="Время создания")<br>
    time_update=models.DateTimeField(auto_now=True, verbose_name="Время изменения")<br>
    is_published=models.BooleanField(default=True, verbose_name="Публикация")<br>
    cat=models.ForeignKey('Category', on_delete=models.PROTECT, null=True, verbose_name="Категории")<br>
    def __str__(self):<br>
    return self.title<br>
    class Category(models.Model):<br>
    name=models.CharField(max_length=100, db_index=True, verbose_name="Категория")<br>
    def __str__(self):<br>
    return self.name<br>
    $ python3 manage.py makemigrations<br>
    $ python3 manage.py migrate<br>
    $ python3 manage.py createsuperuser<br>
    Имя пользователя (leave blank to use 'tuser'): tuser<br>
    Адрес электронной почты: tmail138@yandex.ru<br>
    Password:&nbsp;<br>
    Password (again):&nbsp;<br>
    $ vim women\admin.py<br>
    $ cat women\admin.py<br>
    from django.contrib import admin<br>
    from .models import Women<br>
    admin.site.register(Women)<br>
    $ sudo apt install sqlite3<br>
    $ sqlite3 db.sqlite3<br>
    sqlite&gt; SELECT name from sqlite_master where type= "table";<br>
    django_migrations<br>
    sqlite_sequence<br>
    auth_group_permissions<br>
    auth_user_groups<br>
    auth_user_user_permissions<br>
    django_admin_log<br>
    django_content_type<br>
    auth_permission<br>
    auth_group<br>
    auth_user<br>
    django_session<br>
    women_category<br>
    women_women<br>
    sqlite&gt; INSERT INTO women_category (name)<br>
    VALUES ("Актрисы"), ("Певицы");<br>
    sqlite&gt; select * from women_category;<br>
    1|Актрисы<br>
    2|Певицы<br>
    $ python3 manage.py startapp women<br>
    $ cat settings.txt<br>
    ...&nbsp;<br>
    INSTALLED_APPS = [<br>
    'django.contrib.admin',<br>
    'django.contrib.auth',<br>
    'django.contrib.contenttypes',<br>
    'django.contrib.sessions',<br>
    'django.contrib.messages',<br>
    'django.contrib.staticfiles',<br>
    'women.apps.WomenConfig',<br>
    'rest_framework',&nbsp;&nbsp;<br>
    ]<br>
    ...<br>
    $ python3 manage.py runserver<br>
    $ vim women\views.py<br>
    $ cat women\views.py<br>
    from django.shortcuts import render<br>
    from rest_framework import generics<br>
    from .models import Women<br>
    from .serializers import WomenSerializer<br>
    class WomenAPIView(generics.ListAPIView):<br>
    queryset = Women.objects.all()<br>
    serializer_class = WomenSerializer<br>
    $ vim women\serializers.py<br>
    $ cat women\serializers.py<br>
    from rest_framework import serializers<br>
    from .models import Women<br>
    class WomenSerializer(serializers.ModelSerializer):<br>
    class Meta:<br>
    model = Women<br>
    fields = ('title', 'cat_id')<br>
    $ vim drfsite\urls.py<br>
    $ cat drfsite\urls.py<br>
    from django.contrib import admin<br>
    from django.urls import path<br>
    from women.views import WomenAPIView<br>
    urlpatterns = [<br>
    path('admin/', admin.site.urls),<br>
    path('api/v1/womenlist/', WomenAPIView.as_view()),<br>
    ]<br>
    $ google-chrome http://127.0.0.1:8000/api/v1/womenlist/ &amp;<br>
    <strong>Task:</strong><br>
    Базовый класс APIView для представлений<br>
    <strong>Decision:</strong><br>
    $ vim women\views.py<br>
    $ cat women\views.py<br>
    from django.shortcuts import render<br>
    from rest_framework import generics<br>
    from .models import Women<br>
    from .serializers import WomenSerializer<br>
    from rest_framework.views import APIView<br>
    from rest_framework.response import Response<br>
    from django.forms import model_to_dict<br>
    #class WomenAPIView(generics.ListAPIView):<br>
    # queryset = Women.objects.all()<br>
    # serializer_class = WomenSerializer<br>
    class WomenAPIView(APIView):<br>
    def get(self, request):<br>
    lst=Women.objects.all().values()<br>
    #return Response({'title':'Актриса1'})<br>
    return Response({'posts':list(lst)})<br>
    def post(self, request):<br>
    #return Response({'title':'Актриса2'})<br>
    post_new=Women.objects.create(<br>
    title=request.data['title'],<br>
    content=request.data['content'],<br>
    cat_id=request.data['cat_id']<br>
    )<br>
    return Response({'post':model_to_dict(post_new)})<br>
    $ google-chrome https://web.postman.co/workspace/ &amp;<br>
    <strong>Task:</strong><br>
    Класс Serializer<br>
    <strong>Decision:</strong><br>
    $ vim women\serializers.py<br>
    $ cat women\serializers.py<br>
    from rest_framework import serializers<br>
    from .models import Women<br>
    from rest_framework.renderers import JSONRenderer<br>
    class WomenModel:<br>
    def __init__(self, title, content):<br>
    self.title = title<br>
    self.content = content<br>
    #class WomenSerializer(serializers.ModelSerializer):<br>
    # class Meta:<br>
    #&nbsp;&nbsp; model = Women<br>
    #&nbsp;&nbsp; fields = ('title', 'cat_id')<br>
    class WomenSerializer(serializers.Serializer):<br>
    title = serializers.CharField(max_length=255)<br>
    content = serializers.CharField()<br>
    def encode():<br>
    model = WomenModel('Actrice1', 'Content: Actrice1')<br>
    model_sr = WomenSerializer(model)<br>
    print(model_sr.data, type(model_sr.data), sep='\n')<br>
    json = JSONRenderer().render(model_sr.data)<br>
    print(json)<br>
    $ python3 manage.py shell<br>
    &gt;&gt;&gt; from women.serializers import encode<br>
    &gt;&gt;&gt; encode()<br>
    {'title': 'Actrice1', 'content': 'Content: Actrice1'}<br>
    &lt;class 'rest_framework.utils.serializer_helpers.ReturnDict'&gt;<br>
    b'{"title":"Actrice1","content":"Content: Actrice1"}'<br>
    &gt;&gt;&gt; quit()<br>
    $ vim women\serializers.py<br>
    $ cat women\serializers.py<br>
    from rest_framework import serializers<br>
    from .models import Women<br>
    from rest_framework.renderers import JSONRenderer<br>
    from rest_framework.parsers import JSONParser<br>
    import io<br>
    ...<br>
    def decode():<br>
    stream = io.BytesIO(b'{"title":"Actrice1", "content":"Content: Actrice1"}')<br>
    data = JSONParser().parse(stream)<br>
    serializer = WomenSerializer(data=data)<br>
    serializer.is_valid()<br>
    print(serializer.validated_data)<br>
    $ python3 manage.py shell<br>
    &gt;&gt;&gt; from women.serializers import decode<br>
    &gt;&gt;&gt; decode()<br>
    OrderedDict([('title', 'Actrice1'), ('content', 'Content: Actrice1')])<br>
    &gt;&gt;&gt; quit()<br>
    $ vim women\serializers.py<br>
    $ cat women\serializers.py<br>
    from rest_framework import serializers<br>
    from .models import Women<br>
    from rest_framework.renderers import JSONRenderer<br>
    from rest_framework.parsers import JSONParser<br>
    import io<br>
    #class WomenModel:<br>
    # def __init__(self, title, content):<br>
    #&nbsp;&nbsp; self.title = title<br>
    #&nbsp;&nbsp; self.content = content<br>
    #class WomenSerializer(serializers.ModelSerializer):<br>
    # class Meta:<br>
    #&nbsp;&nbsp; model = Women<br>
    #&nbsp;&nbsp; fields = ('title', 'cat_id')<br>
    class WomenSerializer(serializers.Serializer):<br>
    title = serializers.CharField(max_length=255)<br>
    content = serializers.CharField()<br>
    time_create=serializers.DateTimeField(read_only=True)<br>
    time_update=serializers.DateTimeField(read_only=True)<br>
    is_published=serializers.BooleanField(default=True)<br>
    cat_id=serializers.IntegerField()&nbsp;<br>
    #def encode():<br>
    # model = WomenModel('Actrice1', 'Content: Actrice1')<br>
    # model_sr = WomenSerializer(model)<br>
    # print(model_sr.data, type(model_sr.data), sep='\n')<br>
    # json = JSONRenderer().render(model_sr.data)<br>
    # print(json)<br>
    #def decode():<br>
    # stream = io.BytesIO(b'{"title":"Actrice1", "content":"Content: Actrice1"}')<br>
    # data = JSONParser().parse(stream)<br>
    # serializer = WomenSerializer(data=data)<br>
    # serializer.is_valid()<br>
    # print(serializer.validated_data)<br>
    $ vim women\views.py<br>
    $ cat women\views.py<br>
    ...<br>
    class WomenAPIView(APIView):<br>
    def get(self, request):<br>
    #lst=Women.objects.all().values()<br>
    #return Response({'title':'Актриса1'})<br>
    #return Response({'posts':list(lst)})<br>
    w = Women.objects.all()<br>
    return Response({'posts':WomenSerializer(w, many=True).data})<br>
    def post(self, request):<br>
    #return Response({'title':'Актриса2'})<br>
    serializer=WomenSerializer(data=request.data)<br>
    serializer.is_valid(raise_exception=True)<br>
    post_new=Women.objects.create(<br>
    title=request.data['title'],<br>
    content=request.data['content'],<br>
    cat_id=request.data['cat_id']<br>
    )<br>
    #return Response({'post':model_to_dict(post_new)})<br>
    return Response({'post':WomenSerializer(post_new).data})<br>
    $ python3 manage.py runserver<br>
    <strong>Task:</strong><br>
    Методы save(), create() и update() класса Serializer<br>
    <strong>Decision:</strong><br>
    $ vim women\serializers.py<br>
    $ cat women\serializers.py<br>
    ...<br>
    class WomenSerializer(serializers.Serializer):<br>
    title = serializers.CharField(max_length=255)<br>
    content = serializers.CharField()<br>
    time_create=serializers.DateTimeField(read_only=True)<br>
    time_update=serializers.DateTimeField(read_only=True)<br>
    is_published=serializers.BooleanField(default=True)<br>
    cat_id=serializers.IntegerField()<br>
    def create(self, validated_data):<br>
    return Women.objects.create(**validated_data)<br>
    def update(self, instance, validated_data):<br>
    instance.title=validated_data.get("title", instance.title)<br>
    instance.content=validated_data.get("content", instance.content)<br>
    instance.time_update=validated_data.get("time_update", instance.time_update)<br>
    instance.is_published=validated_data.get("is_published", instance.is_published)<br>
    instance.cat_id=validated_data.get("cat_id", instance.cat_id)<br>
    instance.save()<br>
    return instance<br>
    ...<br>
    $ vim women\serializers.py<br>
    $ cat women\serializers.py<br>
    ...<br>
    def post(self, request):<br>
    #return Response({'title':'Актриса2'})<br>
    serializer=WomenSerializer(data=request.data)<br>
    serializer.is_valid(raise_exception=True)<br>
    #post_new=Women.objects.create(<br>
    # title=request.data['title'],<br>
    # content=request.data['content'],<br>
    # cat_id=request.data['cat_id']<br>
    #)<br>
    #return Response({'post':model_to_dict(post_new)})<br>
    #return Response({'post':WomenSerializer(post_new).data})<br>
    serializer.save()<br>
    return Response({'post':serializer.data})<br>
    def put(self, request, *args, **kwargs):<br>
    pk = kwargs.get("pk", None)<br>
    if not pk:<br>
    return Response({"error": "Method PUT not allowed"})<br>
    try:<br>
    instance = Women.objects.get(pk=pk)<br>
    except:<br>
    return Response({"error": "Object does not exists"})<br>
    serializer = WomenSerializer(data=request.data, instance=instance)<br>
    serializer.is_valid(raise_exception=True)<br>
    serializer.save()<br>
    return Response({"post": serializer.data})<br>
    def delete(self, request, *args, **kwargs):<br>
    pk = kwargs.get("pk", None)<br>
    if not pk:<br>
    return Response({"error": "Method DELETE not allowed"})<br>
    return Response({"post":"delete post "+str(pk)})<br>
    $ vim drfsite\urls.py<br>
    $ cat drfsite\urls.py<br>
    ...<br>
    urlpatterns = [<br>
    path('admin/', admin.site.urls),<br>
    path('api/v1/womenlist/', WomenAPIView.as_view()),<br>
    path('api/v1/womenlist/&lt;int:pk&gt;/', WomenAPIView.as_view()),<br>
    ]<br>
    $ python3 manage.py runserver<br>
    <strong>Task:</strong><br>
    Класс ModelSerializer и представление ListCreateAPIView&nbsp;<br>
    <strong>Decision:</strong><br>
    $ vim women\serializers.py<br>
    $ cat women\serializers.py<br>
    ...<br>
    #class WomenSerializer(serializers.Serializer):<br>
    #title = serializers.CharField(max_length=255)<br>
    #content = serializers.CharField()<br>
    #time_create=serializers.DateTimeField(read_only=True)<br>
    #time_update=serializers.DateTimeField(read_only=True)<br>
    #is_published=serializers.BooleanField(default=True)<br>
    #cat_id=serializers.IntegerField()<br>
    #def create(self, validated_data):<br>
    #return Women.objects.create(**validated_data)<br>
    #def update(self, instance, validated_data):<br>
    #instance.title=validated_data.get("title", instance.title)<br>
    #instance.content=validated_data.get("content", instance.content)<br>
    #instance.time_update=validated_data.get("time_update", instance.time_update)<br>
    #instance.is_published=validated_data.get("is_published", instance.is_published)<br>
    #instance.cat_id=validated_data.get("cat_id", instance.cat_id)<br>
    #instance.save()<br>
    #return instance<br>
    class WomenSerializer(serializers.ModelSerializer):<br>
    class Meta:<br>
    model=Women<br>
    #fields = ("title", "content", "cat")<br>
    fields="__all__"<br>
    ...<br>
    $ vim women\views.py<br>
    $ cat women\views.py<br>
    ...<br>
    #class WomenAPIView(generics.ListAPIView):<br>
    class WomenAPIList(generics.ListCreateAPIView):<br>
    queryset=Women.objects.all()<br>
    serializer_class=WomenSerializer<br>
    ...<br>
    $ vim drfsite\urls.py<br>
    $ cat drfsite\urls.py<br>
    ...<br>
    #from women.views import WomenAPIView<br>
    from women.views import *<br>
    urlpatterns = [<br>
    path('admin/', admin.site.urls),<br>
    #path('api/v1/womenlist/', WomenAPIView.as_view()),<br>
    path('api/v1/womenlist/', WomenAPIList.as_view()),<br>
    path('api/v1/womenlist/&lt;int:pk&gt;/', WomenAPIView.as_view()),<br>
    ]<br>
    $ python3 manage.py runserver<br>
    <strong>Task:</strong><br>
    Представления UpdateAPIView и RetrieveUpdateDestroyAPIView<br>
    <strong>Decision:</strong><br>
    $ vim women\views.py<br>
    $ cat women\views.py<br>
    ...<br>
    #class WomenAPIView(APIView):<br>
    #def get(self, request):<br>
    #lst=Women.objects.all().values()<br>
    #return Response({'title':'Актриса1'})<br>
    #return Response({'posts':list(lst)})<br>
    #w = Women.objects.all()<br>
    #return Response({'posts':WomenSerializer(w, many=True).data})<br>
    #def post(self, request):<br>
    #return Response({'title':'Актриса2'})<br>
    #serializer=WomenSerializer(data=request.data)<br>
    #serializer.is_valid(raise_exception=True)<br>
    #post_new=Women.objects.create(<br>
    #title=request.data['title'],<br>
    #content=request.data['content'],<br>
    #cat_id=request.data['cat_id']<br>
    #)<br>
    #return Response({'post':model_to_dict(post_new)})<br>
    #return Response({'post':WomenSerializer(post_new).data})<br>
    #serializer.save()<br>
    #return Response({'post':serializer.data})<br>
    #def put(self, request, *args, **kwargs):<br>
    #pk = kwargs.get("pk", None)<br>
    #if not pk:<br>
    #return Response({"error": "Method PUT not allowed"})<br>
    #try:<br>
    #instance = Women.objects.get(pk=pk)<br>
    #except:<br>
    #return Response({"error": "Object does not exists"})<br>
    #serializer = WomenSerializer(data=request.data, instance=instance)<br>
    #serializer.is_valid(raise_exception=True)<br>
    #serializer.save()<br>
    #return Response({"post": serializer.data})<br>
    #def delete(self, request, *args, **kwargs):<br>
    #pk = kwargs.get("pk", None)<br>
    #if not pk:<br>
    #return Response({"error": "Method DELETE not allowed"})<br>
    #return Response({"post":"delete post "+str(pk)})<br>
    class WomenAPIUpdate(generics.UpdateAPIView):<br>
    queryset = Women.objects.all()<br>
    serializer_class = WomenSerializer<br>
    class WomenAPIDetailView(generics.RetrieveUpdateDestroyAPIView):<br>
    queryset = Women.objects.all()<br>
    serializer_class = WomenSerializer<br>
    $ vim drfsite\urls.py<br>
    $ cat drfsite\urls.py<br>
    ...<br>
    urlpatterns = [<br>
    path('admin/', admin.site.urls),<br>
    #path('api/v1/womenlist/', WomenAPIView.as_view()),<br>
    path('api/v1/womenlist/', WomenAPIList.as_view()),<br>
    #path('api/v1/womenlist/&lt;int:pk&gt;/', WomenAPIView.as_view()),<br>
    path('api/v1/womenlist/&lt;int:pk&gt;/', WomenAPIUpdate.as_view()),<br>
    path('api/v1/womendetail/&lt;int:pk&gt;/', WomenAPIDetailView.as_view()),<br>
    ]<br>
    $ vim drfsite\settings.py<br>
    $ cat drfsite\settings.py<br>
    ...<br>
    REST_FRAMEWORK = {<br>
    'DEFAULT_RENDERER_CLASSES':[<br>
    'rest_framework.renderers.JSONRenderer',<br>
    #'rest_framework.renderers.BrowsableAPIRenderer',<br>
    ]<br>
    }<br>
    $ python3 manage.py runserver<br>
    <strong>Task:</strong><br>
    Viewsets и ModelViewSet<br>
    <strong>Decision:</strong><br>
    $ vim women\views.py<br>
    $ cat women\views.py<br>
    from django.shortcuts import render<br>
    from rest_framework import generics, viewsets, mixins<br>
    from .models import Women<br>
    from .serializers import WomenSerializer<br>
    from rest_framework.views import APIView<br>
    from rest_framework.response import Response<br>
    from django.forms import model_to_dict<br>
    from rest_framework.viewsets import GenericViewSet<br>
    ...<br>
    #class WomenAPIList(generics.ListCreateAPIView):<br>
    #queryset=Women.objects.all()<br>
    #serializer_class=WomenSerializer<br>
    ...<br>
    #class WomenAPIUpdate(generics.UpdateAPIView):<br>
    #queryset = Women.objects.all()<br>
    #serializer_class = WomenSerializer<br>
    #class WomenAPIDetailView(generics.RetrieveUpdateDestroyAPIView):<br>
    #queryset = Women.objects.all()<br>
    #serializer_class = WomenSerializer<br>
    #class WomenViewSet(viewsets.ModelViewSet):<br>
    #class WomenViewSet(viewsets.ReadOnlyModelViewSet):<br>
    class WomenViewSet(mixins.CreateModelMixin,<br>
    mixins.RetrieveModelMixin,<br>
    mixins.UpdateModelMixin,<br>
    mixins.ListModelMixin,<br>
    GenericViewSet):<br>
    queryset = Women.objects.all()<br>
    serializer_class = WomenSerializer<br>
    $ vim drfsite\urls.py<br>
    $ cat drfsite\urls.py<br>
    from django.contrib import admin<br>
    from django.urls import path, include<br>
    #from women.views import WomenAPIView<br>
    from women.views import *<br>
    from rest_framework import routers<br>
    router=routers.SimpleRouter()<br>
    router.register(r'women', WomenViewSet)<br>
    urlpatterns = [<br>
    &nbsp;&nbsp;path('admin/', admin.site.urls),<br>
    &nbsp;&nbsp;#path('api/v1/womenlist/', WomenAPIView.as_view()),<br>
    &nbsp;&nbsp;#path('api/v1/womenlist/', WomenAPIList.as_view()),<br>
    &nbsp;&nbsp;#path('api/v1/womenlist/&lt;int:pk&gt;/', WomenAPIView.as_view()),<br>
    &nbsp;&nbsp;#path('api/v1/womenlist/&lt;int:pk&gt;/', WomenAPIUpdate.as_view()),<br>
    &nbsp;&nbsp;#path('api/v1/womendetail/&lt;int:pk&gt;/', WomenAPIDetailView.as_view()),<br>
    &nbsp;&nbsp;#path('api/v1/womenlist/', WomenViewSet.as_view({'get':'list'})),<br>
    &nbsp;&nbsp;#path('api/v1/womendetail/&lt;int:pk&gt;/', WomenViewSet.as_view({'put':'update'})),<br>
    &nbsp;&nbsp;path('api/v1/', include(router.urls)),<br>
    ]<br>
    $ python3 manage.py runserver<br>
    <strong>Task:</strong><br>
    Роутеры: SimpleRouter и DefaultRouter&nbsp;<br>
    <strong>Decision:</strong><br>
    $ vim drfsite\urls.py<br>
    $ cat drfsite\urls.py<br>
    ...<br>
    class MyCustomRouter(routers.SimpleRouter):<br>
    routes = [<br>
    routers.Route(url=r'^{prefix}$',<br>
    mapping={'get': 'list'},<br>
    name='{basename}-list',<br>
    detail=False,<br>
    initkwargs={'suffix': 'List'}),<br>
    routers.Route(url=r'^{prefix}/{lookup}$',<br>
    mapping={'get': 'retrieve'},<br>
    name='{basename}-detail',<br>
    detail=True,<br>
    initkwargs={'suffix': 'Detail'})<br>
    ]<br>
    #router=routers.SimpleRouter()<br>
    #router=routers.DefaultRouter()<br>
    router=MyCustomRouter()<br>
    #router.register(r'women', WomenViewSet)<br>
    #router.register(r'women', WomenViewSet, basename='men')<br>
    router.register(r'women', WomenViewSet, basename='women')<br>
    print(router.urls)<br>
    ...<br>
    $ vim women\views.py<br>
    $ cat women\views.py<br>
    from django.shortcuts import render<br>
    from rest_framework import generics, viewsets, mixins<br>
    from .models import Women, Category<br>
    from .serializers import WomenSerializer<br>
    from rest_framework.views import APIView<br>
    from rest_framework.response import Response<br>
    from django.forms import model_to_dict<br>
    from rest_framework.viewsets import GenericViewSet<br>
    from rest_framework.decorators import action<br>
    ...<br>
    class WomenViewSet(mixins.CreateModelMixin,<br>
    mixins.RetrieveModelMixin,<br>
    mixins.UpdateModelMixin,<br>
    mixins.ListModelMixin,<br>
    GenericViewSet):<br>
    #queryset = Women.objects.all()<br>
    serializer_class = WomenSerializer<br>
    def get_queryset(self):<br>
    #return Women.objects.all()[:3]<br>
    pk=self.kwargs.get("pk")<br>
    if not pk:<br>
    return Women.objects.all()[:3]<br>
    return Women.objects.filter(pk=pk)<br>
    @action(methods=['get'], detail=True)<br>
    def category(self, request, pk=None):<br>
    #cats = Category.objects.all()<br>
    #return Response({'cats': [c.name for c in cats]})<br>
    cats = Category.objects.get(pk=pk)<br>
    return Response({'cats': cats.name})<br>
    $ python3 manage.py runserver<br>
    <strong>Task:</strong><br>
    Ограничения доступа (permissions)<br>
    <strong>Decision:</strong><br>
    $ vim women\models.py<br>
    $ cat women\models.py<br>
    from django.db import models<br>
    from django.contrib.auth.models import User<br>
    ...<br>
    cat=models.ForeignKey('Category', on_delete=models.PROTECT, null=True, verbose_name="Категории")<br>
    user=models.ForeignKey(User, on_delete=models.CASCADE, verbose_name="Пользователь")<br>
    def __str__(self):<br>
    ...<br>
    $ python3 manage.py makemigrations<br>
    Select an option: 1<br>
    &gt;&gt;&gt; 1<br>
    $ python3 manage.py migrate<br>
    $ vim women/views.py<br>
    $ cat women/views.py<br>
    from django.shortcuts import render<br>
    from rest_framework import generics, viewsets, mixins<br>
    from .models import Women, Category<br>
    from .serializers import WomenSerializer<br>
    from rest_framework.views import APIView<br>
    from rest_framework.response import Response<br>
    from django.forms import model_to_dict<br>
    from rest_framework.viewsets import GenericViewSet<br>
    from rest_framework.decorators import action<br>
    from rest_framework.permissions import IsAuthenticatedOrReadOnly, IsAdminUser<br>
    from .permissions import IsAdminOrReadOnly, IsOwnerOrReadOnly<br>
    class WomenAPIList(generics.ListCreateAPIView):<br>
    queryset=Women.objects.all()<br>
    serializer_class=WomenSerializer<br>
    #permissions_classes=(IsAuthenticatedOrReadOnly, )<br>
    class WomenAPIUpdate(generics.RetrieveUpdateAPIView):<br>
    queryset = Women.objects.all()<br>
    serializer_class = WomenSerializer<br>
    permissions_classes=(IsOwnerOrReadOnly, )<br>
    class WomenAPIDestroy(generics.RetrieveDestroyAPIView):<br>
    queryset = Women.objects.all()<br>
    serializer_class = WomenSerializer<br>
    permissions_classes=(IsAdminOrReadOnly, )<br>
    $ vim drfsite\urls.py<br>
    $ cat drfsite\urls.py<br>
    ...<br>
    #class MyCustomRouter(routers.SimpleRouter):<br>
    #&nbsp;&nbsp;routes = [<br>
    #&nbsp;&nbsp;&nbsp;&nbsp;routers.Route(url=r'^{prefix}$',<br>
    #&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; mapping={'get': 'list'},<br>
    #&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; name='{basename}-list',<br>
    #&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; detail=False,<br>
    #&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; initkwargs={'suffix': 'List'}),<br>
    #&nbsp;&nbsp;&nbsp;&nbsp;routers.Route(url=r'^{prefix}/{lookup}$',<br>
    #&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; mapping={'get': 'retrieve'},<br>
    #&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; name='{basename}-detail',<br>
    #&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; detail=True,<br>
    #&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; initkwargs={'suffix': 'Detail'})<br>
    #&nbsp;&nbsp;]<br>
    #router=routers.SimpleRouter()<br>
    #router=routers.DefaultRouter()<br>
    #router=MyCustomRouter()<br>
    #router.register(r'women', WomenViewSet)<br>
    #router.register(r'women', WomenViewSet, basename='men')<br>
    #router.register(r'women', WomenViewSet, basename='women')<br>
    #print(router.urls)<br>
    urlpatterns = [<br>
    path('admin/', admin.site.urls),<br>
    #path('api/v1/womenlist/', WomenAPIView.as_view()),<br>
    #path('api/v1/womenlist/', WomenAPIList.as_view()),<br>
    #path('api/v1/womenlist/&lt;int:pk&gt;/', WomenAPIView.as_view()),<br>
    #path('api/v1/womenlist/&lt;int:pk&gt;/', WomenAPIUpdate.as_view()),<br>
    #path('api/v1/womendetail/&lt;int:pk&gt;/', WomenAPIDetailView.as_view()),<br>
    #path('api/v1/womenlist/', WomenViewSet.as_view({'get':'list'})),<br>
    #path('api/v1/womendetail/&lt;int:pk&gt;/', WomenViewSet.as_view({'put':'update'})),<br>
    #path('api/v1/', include(router.urls)),<br>
    path('api/v1/women/', WomenAPIList.as_view()),<br>
    path('api/v1/women/&lt;int:pk&gt;/', WomenAPIUpdate.as_view()),<br>
    path('api/v1/womendelete/&lt;int:pk&gt;/', WomenAPIDestroy.as_view()),<br>
    ]<br>
    $ vim women/serializers.py<br>
    $ cat women/serializers.py<br>
    ...<br>
    class WomenSerializer(serializers.ModelSerializer):<br>
    user=serializers.HiddenField(default=serializers.CurrentUserDefault())<br>
    class Meta:<br>
    model=Women<br>
    #fields = ("title", "content", "cat")<br>
    fields="__all__"<br>
    ...<br>
    $ touch women/permissions.py<br>
    $ vim women/permissions.py<br>
    $ cat women/permissions.py<br>
    from rest_framework import permissions<br>
    class IsAdminOrReadOnly(permissions.BasePermission):<br>
    def has_permission(self, request, view):<br>
    if request.method in permissions.SAFE_METHODS:<br>
    return True<br>
    return bool(request.user and request.user.is_staff)<br>
    class IsOwnerOrReadOnly(permissions.BasePermission):<br>
    def has_object_permission(self, request, view, obj):<br>
    if request.method in permissions.SAFE_METHODS:<br>
    return True<br>
    return obj.user == request.user<br>
    $ vim drfsite\settings.py<br>
    $ cat drfsite\settings.py<br>
    ...<br>
    REST_FRAMEWORK = {<br>
    'DEFAULT_RENDERER_CLASSES':[<br>
    'rest_framework.renderers.JSONRenderer',<br>
    'rest_framework.renderers.BrowsableAPIRenderer',<br>
    ],<br>
    'DEFAULT_PERMISSION_CLASSES':[<br>
    #'rest_framework.permissions.IsAuthenticated',<br>
    'rest_framework.permissions.AllowAny',<br>
    ]<br>
    }<br>
    $ python3 manage.py runserver<br>
    <strong>Task:</strong><br>
    Авторизация и аутентификация. Session-based authentication.<br>
    <strong>Decision:</strong><br>
    $ vim drfsite\urls.py<br>
    $ cat drfsite\urls.py<br>
    ...<br>
    [<br>
    ...<br>
    path('api/v1/womendelete/&lt;int:pk&gt;/', WomenAPIDestroy.as_view()),<br>
    path('api/v1/drf-auth/', include('rest_framework.urls')),<br>
    ]<br>
    $ python3 manage.py runserver<br>
    $ google-chrome http://127.0.0.1:8000/api/v1/drf-auth/ &amp;&nbsp;<br>
    <strong>Task:</strong><br>
    Аутентификация по токенам. Пакет Djoser<br>
    <strong>Decision:</strong><br>
    $ vim drfsite\settings.py<br>
    $ cat drfsite\settings.py<br>
    ...<br>
    INSTALLED_APPS = [<br>
    'django.contrib.admin',<br>
    'django.contrib.auth',<br>
    'django.contrib.contenttypes',<br>
    'django.contrib.sessions',<br>
    'django.contrib.messages',<br>
    'django.contrib.staticfiles',<br>
    'women.apps.WomenConfig',<br>
    'rest_framework',<br>
    'rest_framework.authtoken',<br>
    'djoser',<br>
    ]<br>
    ...<br>
    $ python3 manage.py migrate<br>
    $ vim drfsite\urls.py<br>
    $ cat drfsite\urls.py<br>
    ...<br>
    from django.urls import path, include, re_path<br>
    [<br>
    ...<br>
    path('api/v1/drf-auth/', include('rest_framework.urls')),<br>
    path('api/v1/auth/', include('djoser.urls')),<br>
    re_path(r'^auth/', include('djoser.urls.authtoken')),<br>
    ]<br>
    $ vim drfsite\settings.py<br>
    $ cat drfsite\settings.py<br>
    ...<br>
    REST_FRAMEWORK = {<br>
    ...<br>
    'DEFAULT_AUTHENTICATION_CLASSES':[<br>
    'rest_framework.authentication.TokenAuthentication',<br>
    'rest_framework.authentication.BasicAuthentication',<br>
    'rest_framework.authentication.SessionAuthentication',<br>
    ],<br>
    }<br>
    $ vim women\views.py<br>
    $ cat women\views.py<br>
    ...<br>
    from rest_framework.permissions import IsAuthenticatedOrReadOnly, IsAdminUser, IsAuthenticated<br>
    from .permissions import IsAdminOrReadOnly, IsOwnerOrReadOnly<br>
    from rest_framework.authentication import TokenAuthentication<br>
    ...<br>
    class WomenAPIUpdate(generics.RetrieveUpdateAPIView):<br>
    queryset = Women.objects.all()<br>
    serializer_class = WomenSerializer<br>
    #permissions_classes=(IsOwnerOrReadOnly, )<br>
    permissions_classes=(IsAuthenticated, )<br>
    #authentication_classes = (TokenAuthentication, )<br>
    ...<br>
    $ python3 manage.py runserver<br>
    $ google-chrome http://127.0.0.1:8000/api/v1/auth/ &amp;&nbsp;<br>
    <strong>Task:</strong><br>
    Делаем авторизацию по JWT-токенам<br>
    <strong>Decision:</strong><br>
    $ vim drfsite\settings.py<br>
    $ cat drfsite\settings.py<br>
    from pathlib import Path<br>
    from datetime import timedelta<br>
    ...<br>
    REST_FRAMEWORK = {<br>
    ...<br>
    'DEFAULT_AUTHENTICATION_CLASSES':[<br>
    #'rest_framework.authentication.TokenAuthentication',<br>
    'rest_framework_simplejwt.authentication.JWTAuthentication',<br>
    'rest_framework.authentication.BasicAuthentication',<br>
    'rest_framework.authentication.SessionAuthentication',&nbsp;&nbsp;&nbsp;&nbsp;<br>
    ],<br>
    }<br>
    SIMPLE_JWT = {<br>
    "ACCESS_TOKEN_LIFETIME": timedelta(minutes=5),<br>
    "REFRESH_TOKEN_LIFETIME": timedelta(days=1),<br>
    "ROTATE_REFRESH_TOKENS": False,<br>
    "BLACKLIST_AFTER_ROTATION": False,<br>
    "UPDATE_LAST_LOGIN": False,<br>
    "ALGORITHM": "HS256",<br>
    "SIGNING_KEY": SECRET_KEY,<br>
    "VERIFYING_KEY": "",<br>
    "AUDIENCE": None,<br>
    "ISSUER": None,<br>
    "JSON_ENCODER": None,<br>
    "JWK_URL": None,<br>
    "LEEWAY": 0,<br>
    #"AUTH_HEADER_TYPES": ("Bearer",),<br>
    "AUTH_HEADER_TYPES": ("JWT",),<br>
    "AUTH_HEADER_NAME": "HTTP_AUTHORIZATION",<br>
    "USER_ID_FIELD": "id",<br>
    "USER_ID_CLAIM": "user_id",<br>
    "USER_AUTHENTICATION_RULE": "rest_framework_simplejwt.authentication.default_user_authentication_rule",<br>
    "AUTH_TOKEN_CLASSES": ("rest_framework_simplejwt.tokens.AccessToken",),<br>
    "TOKEN_TYPE_CLAIM": "token_type",<br>
    "TOKEN_USER_CLASS": "rest_framework_simplejwt.models.TokenUser",<br>
    "JTI_CLAIM": "jti",<br>
    "SLIDING_TOKEN_REFRESH_EXP_CLAIM": "refresh_exp",<br>
    "SLIDING_TOKEN_LIFETIME": timedelta(minutes=5),<br>
    "SLIDING_TOKEN_REFRESH_LIFETIME": timedelta(days=1),<br>
    "TOKEN_OBTAIN_SERIALIZER": "rest_framework_simplejwt.serializers.TokenObtainPairSerializer",<br>
    "TOKEN_REFRESH_SERIALIZER": "rest_framework_simplejwt.serializers.TokenRefreshSerializer",<br>
    "TOKEN_VERIFY_SERIALIZER": "rest_framework_simplejwt.serializers.TokenVerifySerializer",<br>
    "TOKEN_BLACKLIST_SERIALIZER": "rest_framework_simplejwt.serializers.TokenBlacklistSerializer",<br>
    "SLIDING_TOKEN_OBTAIN_SERIALIZER": "rest_framework_simplejwt.serializers.TokenObtainSlidingSerializer",<br>
    "SLIDING_TOKEN_REFRESH_SERIALIZER": "rest_framework_simplejwt.serializers.TokenRefreshSlidingSerializer",<br>
    }<br>
    $ vim drfsite\urls.py<br>
    $ cat drfsite\urls.py<br>
    from django.contrib import admin<br>
    from django.urls import path, include, re_path<br>
    #from women.views import WomenAPIView<br>
    from women.views import *<br>
    from rest_framework import routers<br>
    from rest_framework_simplejwt.views import TokenObtainPairView, TokenRefreshView, TokenVerifyView<br>
    ...<br>
    urlpatterns = [<br>
    ...<br>
    re_path(r'^auth/', include('djoser.urls.authtoken')),<br>
    path('api/v1/token/verify/', TokenVerifyView.as_view(), name='token_verify'),<br>
    path('api/v1/token/', TokenObtainPairView.as_view(), name='token_obtain_pair'),<br>
    path('api/v1/token/refresh/', TokenRefreshView.as_view(), name='token_refresh'),<br>
    ]<br>
    $ python3 manage.py runserver<br>
    $ google-chrome http://127.0.0.1:8000/api/v1/token/ &amp;&nbsp;<br>
    <strong>Task:</strong><br>
    Добавляем пагинацию (pagination)<br>
    <strong>Decision:</strong><br>
    $ vim drfsite\settings.py<br>
    $ cat drfsite\settings.py<br>
    ...<br>
    REST_FRAMEWORK = {<br>
    'DEFAULT_PAGINATION_CLASS': 'rest_framework.pagination.LimitOffsetPagination',<br>
    'PAGE_SIZE': 2,<br>
    ...<br>
    }<br>
    $ vim women\views.py<br>
    $ cat women\views.py<br>
    ...<br>
    from rest_framework.pagination import PageNumberPagination<br>
    #class WomenAPIView(generics.ListAPIView):<br>
    class WomenAPIListPagination(PageNumberPagination):<br>
    page_size=3<br>
    page_size_query_param='page_size'<br>
    max_page_size=10000<br>
    class WomenAPIList(generics.ListCreateAPIView):<br>
    queryset=Women.objects.all()<br>
    serializer_class=WomenSerializer<br>
    permissions_classes=(IsAuthenticatedOrReadOnly, )<br>
    pagination_class=WomenAPIListPagination<br>
    ...<br>
    $ python3 manage.py runserver<br>
    $ google-chrome http://127.0.0.1:8000/api/v1/women/ &amp;&nbsp;<br>
    <strong>Source:</strong><br>
    https://www.youtube.com/playlist?list=PLA0M1Bcd0w8xZA3Kl1fYmOH_MfLpiYMRs<br>
    https://www.freecodecamp.org/news/python-requirementstxt-explained/<br>
    https://timeweb.cloud/tutorials/sqlite/rukovodstvo-po-nastrojke-sqlite<br>
    https://itfy.org/threads/kak-poluchit-spisok-tablic-v-sqlite3.695/<br>
    https://linuxgenie.net/how-to-install-postman-on-ubuntu-22-04/<br>
    https://pyonlycode.com/post/how-to-solve-nameerror-name-io-is-not-defined/<br>
    https://django-rest-framework-simplejwt.readthedocs.io/en/latest/index.html<br>
    https://jwt.io/<br>
</p>