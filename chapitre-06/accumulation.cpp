// Motif de correction à intégrer au gestionnaire d'événements NKentseu.
// À chaque NkMouseRawEvent : accumRawDX += GetDeltaX(); accumRawDY += GetDeltaY();
// Une seule fois par image : appliquer(accumRawDX, accumRawDY);
// Puis remettre les deux accumulateurs à zéro. La troisième variante omet
// volontairement ce vidage pour reproduire la dérive.
#include <cstdio>
int main(){
  double acc=0, yawGood=0, yawNoClear=0, yawBug=0;
  constexpr double sens=0.002;
  for(int frame=1; frame<=5; ++frame){
    const double eventDelta = (frame==1 ? 2.0 : 0.0);
    // module fautif : relit le dernier delta conservé
    yawBug += 2.0*sens;
    // version correcte : n'ajoute que les événements réellement reçus
    acc += eventDelta; yawGood += acc*sens; acc=0;
    // oubli volontaire du vidage
    static double stuck=0; stuck += eventDelta; yawNoClear += stuck*sens;
    std::printf("image %d : fautif %.4f rad, correct %.4f rad, sans vidage %.4f rad\n",frame,yawBug,yawGood,yawNoClear);
  }
}
