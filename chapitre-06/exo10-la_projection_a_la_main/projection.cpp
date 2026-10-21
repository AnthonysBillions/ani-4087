#include <cmath>
#include <cstdio>
#include <initializer_list>
#include <utility>
#include <algorithm>
struct M{double m[4][4]{};};
M Projection(double l,double r,double u,double d,double n,double f){M a{}; double tl=tan(l),tr=tan(r),tu=tan(u),td=tan(d),w=tr-tl,h=tu-td; a.m[0][0]=2/w; a.m[1][1]=2/h; a.m[2][0]=(tr+tl)/w; a.m[2][1]=(tu+td)/h; a.m[2][2]=-(f+n)/(f-n); a.m[2][3]=-1; a.m[3][2]=-2*f*n/(f-n); return a;}
int main(){double pi=acos(-1),v=70*pi/180,aspect=1280.0/720.0; double top=v/2,bottom=-v/2,halfW=atan(tan(v/2)*aspect); M s=Projection(-halfW,halfW,top,bottom,.05,100); M q=Projection(-52*pi/180,45*pi/180,48*pi/180,-50*pi/180,.05,100); for(auto pair:{std::pair<const char*,M>{"symetrique",s},{"quest",q}}){double mx=0; for(int row=0;row<4;++row){printf("%s, ligne %d :",pair.first,row); for(int col=0;col<4;++col){printf(" %.6f",pair.second.m[col][row]);} puts("");} printf("%s : plus grand ecart %.6f\n",pair.first,mx);}}
