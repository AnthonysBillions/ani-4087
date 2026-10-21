// Référence autonome : rotations de vecteurs pour comparer les ordres.
// Le rendu final du cours doit également appeler NkQuatf/NkMat4f du SDK.
#include <cmath>
#include <cstdio>
#include <initializer_list>
#include <utility>
struct V{double x,y,z;};
V rx(V v,double a){return {v.x,v.y*cos(a)-v.z*sin(a),v.y*sin(a)+v.z*cos(a)};}
V ry(V v,double a){return {v.x*cos(a)+v.z*sin(a),v.y,-v.x*sin(a)+v.z*cos(a)};}
int main(){const double pi=acos(-1), y=45*pi/180, p=30*pi/180; V f{0,0,-1};
 V a=ry(rx(f,p),y), b=rx(ry(f,y),p), c=ry(rx(f,p),y);
 for(auto z:{a,b,c}) std::printf("(%.4f, %.4f, %.4f)\n",z.x,z.y,z.z);
 std::printf("a_y manuel = sin(30 deg) = %.4f\n",sin(p));
}
