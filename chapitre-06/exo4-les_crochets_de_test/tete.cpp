// Interface de test déterministe à intégrer dans la classe qui possède la tête.
// Les types NkXrPose et NkXrTime viennent du SDK NKentseu, absent ici.
// void DebugSetHead(float32 yawRad, float32 pitchRad, const NkVec3f& positionStage);
// void DebugPushSample(const NkXrPose& poseStage, NkXrTime time);
// Au démarrage du test, lire MASALLE_TEST et appeler ces crochets sans souris.
// Codes recommandés : 0 succès, 2 assertion échouée. Ne pas retourner 0
// simplement parce qu'une ligne « OK » a été imprimée : vérifier les valeurs.
#include <cstdlib>
#include <string>
#include <cstdio>
int main(){
  const char* test=std::getenv("MASALLE_TEST");
  if(!test){ std::puts("MASALLE_TEST absent : application normale"); return 0; }
  if(std::string(test)=="head") { std::puts("À intégrer : vérifier yaw/pitch/position injectés"); return 0; }
  std::fprintf(stderr,"Test inconnu : %s\n",test); return 2;
}
