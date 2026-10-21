// Banc de mesure autonome C++17 ; remplacez les fonctions de rotation par les
// appels NKMath pour mesurer le coût réel du SDK. Le volatile empêche l'élimination.
#include <chrono>
#include <cmath>
#include <cstdio>
volatile double sink=0;
int main(){constexpr int N=1000000; for(int pass=0;pass<3;++pass){
 auto t0=std::chrono::steady_clock::now(); double s=0; for(int i=0;i<N;++i){double y=(i%3600)*0.1*3.141592653589793/180, p=(i%900)*0.1*3.141592653589793/180; s+=cos(y/2)*cos(p/2); } auto t1=std::chrono::steady_clock::now(); sink=s; printf("matrices, essai %d : %.3f ms\n",pass+1,std::chrono::duration<double,std::milli>(t1-t0).count());
 auto q0=std::chrono::steady_clock::now(); s=0; for(int i=0;i<N;++i){double y=(i%3600)*0.1*3.141592653589793/180, p=(i%900)*0.1*3.141592653589793/180; s+=cos(y/2)*cos(p/2); } auto q1=std::chrono::steady_clock::now(); sink=s; printf("quaternions, essai %d : %.3f ms\n",pass+1,std::chrono::duration<double,std::milli>(q1-q0).count()); }}
