#include <cmath>
#include <cstdio>
#include <initializer_list>
#include <utility>
struct V{double x,y,z;};
V rx(V v,double a){return {v.x,v.y*cos(a)-v.z*sin(a),v.y*sin(a)+v.z*cos(a)};}
V ry(V v,double a){return {v.x*cos(a)+v.z*sin(a),v.y,-v.x*sin(a)+v.z*cos(a)};}
int main(){double pi=acos(-1), p=30*pi/180; for(double d:{0,45,90,135,180}){double y=d*pi/180; V f{0,0,-1}; V good=ry(rx(f,p),y), bad=rx(ry(f,y),p); auto h=[](V v){return atan2(v.y,sqrt(v.x*v.x+v.z*v.z))*180/acos(-1);}; printf("lacet*tangage, lacet %.0f : hauteur %.2f deg\n",d,h(good)); printf("tangage*lacet, lacet %.0f : hauteur %.2f deg\n",d,h(bad)); }}
