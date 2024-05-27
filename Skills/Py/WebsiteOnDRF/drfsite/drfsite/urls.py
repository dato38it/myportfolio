from django.contrib import admin
from django.urls import path, include, re_path
#from women.views import WomenAPIView
from women.views import *
from rest_framework import routers
from rest_framework_simplejwt.views import TokenObtainPairView, TokenRefreshView, TokenVerifyView
#class MyCustomRouter(routers.SimpleRouter):
#    routes = [
#        routers.Route(url=r'^{prefix}$',
#                      mapping={'get': 'list'},
#                      name='{basename}-list',
#                      detail=False,
#                      initkwargs={'suffix': 'List'}),
#        routers.Route(url=r'^{prefix}/{lookup}$',
#                      mapping={'get': 'retrieve'},
#                      name='{basename}-detail',
#                      detail=True,
#                      initkwargs={'suffix': 'Detail'})
#    ]
#router=routers.SimpleRouter()
#router=routers.DefaultRouter()
#router=MyCustomRouter()
#router.register(r'women', WomenViewSet)
#router.register(r'women', WomenViewSet, basename='men')
#router.register(r'women', WomenViewSet, basename='women')
#print(router.urls)
urlpatterns = [
    path('admin/', admin.site.urls),
    #path('api/v1/womenlist/', WomenAPIView.as_view()),
    #path('api/v1/womenlist/', WomenAPIList.as_view()),
    #path('api/v1/womenlist/<int:pk>/', WomenAPIView.as_view()),
    #path('api/v1/womenlist/<int:pk>/', WomenAPIUpdate.as_view()),
    #path('api/v1/womendetail/<int:pk>/', WomenAPIDetailView.as_view()),
    #path('api/v1/womenlist/', WomenViewSet.as_view({'get':'list'})),
    #path('api/v1/womendetail/<int:pk>/', WomenViewSet.as_view({'put':'update'})),
    #path('api/v1/', include(router.urls)),
    path('api/v1/women/', WomenAPIList.as_view()),
    path('api/v1/women/<int:pk>/', WomenAPIUpdate.as_view()),
    path('api/v1/womendelete/<int:pk>/', WomenAPIDestroy.as_view()),
    path('api/v1/drf-auth/', include('rest_framework.urls')),
    path('api/v1/auth/', include('djoser.urls')),
    re_path(r'^auth/', include('djoser.urls.authtoken')),
    path('api/v1/token/verify/', TokenVerifyView.as_view(), name='token_verify'),
    path('api/v1/token/', TokenObtainPairView.as_view(), name='token_obtain_pair'),
    path('api/v1/token/refresh/', TokenRefreshView.as_view(), name='token_refresh'),
]
