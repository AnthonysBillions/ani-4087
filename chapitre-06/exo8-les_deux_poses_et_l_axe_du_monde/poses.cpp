#include <cmath>
#include <cstdio>
struct V{double x,y,z;};
V add(V a,V b){return {a.x+b.x,a.y+b.y,a.z+b.z};} V mul(V a,double s){return {a.x*s,a.y*s,a.z*s};}
V rz(V v,double a){return {v.x*cos(a)-v.y*sin(a),v.x*sin(a)+v.y*cos(a),v.z};}
V ry(V v,double a){return {v.x*cos(a)+v.z*sin(a),v.y,-v.x*sin(a)+v.z*cos(a)};}
int main(){const double pi=acos(-1), ipd=.063, h=ipd/2; V head{.30,1.70,1.20}; struct P{const char*n; V (*rot)(V,double); double a;}; P poses[]={{"neutre",nullptr,0},{"roulis 30",rz,30*pi/180},{"lacet 90",ry,90*pi/180}}; for(auto p:poses){V right{1,0,0}; if(p.rot)right=p.rot(right,p.a); V gl=add(head,mul(right,-h)), gr=add(head,mul(right,h)); V gw{head.x-h,head.y,head.z}, dw{head.x+h,head.y,head.z}; printf("%s, tete : G (%.4f, %.4f, %.4f) D (%.4f, %.4f, %.4f)\n",p.n,gl.x,gl.y,gl.z,gr.x,gr.y,gr.z); printf("%s, monde : G (%.4f, %.4f, %.4f) D (%.4f, %.4f, %.4f)\n",p.n,gw.x,gw.y,gw.z,dw.x,dw.y,dw.z); printf("%s : ecart %.1f mm\n",p.n,1000*sqrt((gl.x-gw.x)*(gl.x-gw.x)+(gl.y-gw.y)*(gl.y-gw.y)+(gl.z-gw.z)*(gl.z-gw.z))); }}
