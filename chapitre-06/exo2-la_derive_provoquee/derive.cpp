// Démonstration numérique du défaut décrit : une valeur de delta conservée
// est réintégrée à chaque image, même lorsque la souris est immobile.
#include <cstdio>
int main() {
    constexpr double sensibilite = 0.002; // radian/compte, valeur de démonstration
    constexpr double brut = 2.0;          // dernier delta conservé (simulation)
    double yaw = 0.0;
    for (int seconde=1; seconde<=10; ++seconde) {
        for (int image=0; image<90; ++image) yaw += brut*sensibilite;
        std::printf("t = %.1f s, images = %d, brut = %.0f, lacet = %.1f deg.\n",
                    double(seconde), seconde*90, brut, yaw*180.0/3.141592653589793);
    }
}
