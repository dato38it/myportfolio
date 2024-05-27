from django.shortcuts import render
from rest_framework import generics, viewsets, mixins
from .models import Women, Category
from .serializers import WomenSerializer
from rest_framework.views import APIView
from rest_framework.response import Response
from django.forms import model_to_dict
from rest_framework.viewsets import GenericViewSet
from rest_framework.decorators import action
from rest_framework.permissions import IsAuthenticatedOrReadOnly, IsAdminUser, IsAuthenticated
from .permissions import IsAdminOrReadOnly, IsOwnerOrReadOnly
from rest_framework.authentication import TokenAuthentication
from rest_framework.pagination import PageNumberPagination
#class WomenAPIView(generics.ListAPIView):
class WomenAPIListPagination(PageNumberPagination):
	page_size=3
	page_size_query_param='page_size'
	max_page_size=10000
class WomenAPIList(generics.ListCreateAPIView):
	queryset=Women.objects.all()
	serializer_class=WomenSerializer
	permissions_classes=(IsAuthenticatedOrReadOnly, )
	pagination_class=WomenAPIListPagination
#class WomenAPIView(APIView):
#	def get(self, request):
		#lst=Women.objects.all().values()
		#return Response({'title':'Актриса1'})
		#return Response({'posts':list(lst)})
#		w = Women.objects.all()
#		return Response({'posts':WomenSerializer(w, many=True).data})
#	def post(self, request):
		#return Response({'title':'Актриса2'})
#		serializer=WomenSerializer(data=request.data)
#		serializer.is_valid(raise_exception=True)
		#post_new=Women.objects.create(
		#	title=request.data['title'],
		#	content=request.data['content'],
		#	cat_id=request.data['cat_id']
		#)
		#return Response({'post':model_to_dict(post_new)})
		#return Response({'post':WomenSerializer(post_new).data})
#		serializer.save()
#		return Response({'post':serializer.data})
#	def put(self, request, *args, **kwargs):
#		pk = kwargs.get("pk", None)
#		if not pk:
#			return Response({"error": "Method PUT not allowed"})
#		try:
#			instance = Women.objects.get(pk=pk)
#		except:
#			return Response({"error": "Object does not exists"})
#		serializer = WomenSerializer(data=request.data, instance=instance)
#		serializer.is_valid(raise_exception=True)
#		serializer.save()
#		return Response({"post": serializer.data})
#	def delete(self, request, *args, **kwargs):
#		pk = kwargs.get("pk", None)
#		if not pk:
#			return Response({"error": "Method DELETE not allowed"})
#		return Response({"post":"delete post "+str(pk)})
#class WomenAPIUpdate(generics.UpdateAPIView):
#	queryset = Women.objects.all()
#	serializer_class = WomenSerializer
#class WomenAPIDetailView(generics.RetrieveUpdateDestroyAPIView):
#	queryset = Women.objects.all()
#	serializer_class = WomenSerializer
#class WomenViewSet(viewsets.ModelViewSet):
#class WomenViewSet(viewsets.ReadOnlyModelViewSet):
#class WomenViewSet(mixins.CreateModelMixin,
#	mixins.RetrieveModelMixin,
#	mixins.UpdateModelMixin,
#	mixins.ListModelMixin,
#	GenericViewSet):
	#queryset = Women.objects.all()
#	serializer_class = WomenSerializer
#	def get_queryset(self):
		#return Women.objects.all()[:3]
#		pk=self.kwargs.get("pk")
#		if not pk:
#			return Women.objects.all()[:3]
#		return Women.objects.filter(pk=pk)
#	@action(methods=['get'], detail=True)
#	def category(self, request, pk=None):
		#cats = Category.objects.all()
		#return Response({'cats': [c.name for c in cats]})
#		cats = Category.objects.get(pk=pk)
#		return Response({'cats': cats.name})
class WomenAPIUpdate(generics.RetrieveUpdateAPIView):
	queryset = Women.objects.all()
	serializer_class = WomenSerializer
	#permissions_classes=(IsOwnerOrReadOnly, )
	permissions_classes=(IsAuthenticated, )
	#authentication_classes = (TokenAuthentication, )
class WomenAPIDestroy(generics.RetrieveDestroyAPIView):
	queryset = Women.objects.all()
	serializer_class = WomenSerializer
	permissions_classes=(IsAdminOrReadOnly, )