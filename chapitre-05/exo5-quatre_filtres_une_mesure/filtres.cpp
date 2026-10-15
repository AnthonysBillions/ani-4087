// filtres.cpp - Exercice 5 : reduire 2048 -> 256 avec les quatre filtres, mesurer, comparer.
// A construire en Release. A lancer depuis le dossier du projet, avec photo.jpg dedans.
#include "NKImage/Core/NkImage.h"
#include "NKTime/NkChrono.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace nkentseu;

static const int kRepetitions = 20;

struct Filtre {
    const char*    nom;
    NkResizeFilter filtre;
    const char*    fichier;
};

// Deux pixels different si au moins un canal differe. Adaptez les champs a votre NkImage.
static bool PixelsDifferent(const NkImage& a, const NkImage& b, int x, int y) {
    const auto pa = a.GetPixel(x, y);
    const auto pb = b.GetPixel(x, y);
    return pa.r != pb.r || pa.g != pb.g || pa.b != pb.b || pa.a != pb.a;
}

static long long CompterDifferences(const NkImage& a, const NkImage& b) {
    long long n = 0;
    for (int y = 0; y < a.Height(); ++y) {
        for (int x = 0; x < a.Width(); ++x) {
            if (PixelsDifferent(a, b, x, y)) {
                ++n;
            }
        }
    }
    return n;
}

int main() {
    NkImage photo;
    if (!photo.Load("photo.jpg")) {
        std::cerr << "photo.jpg introuvable\n";
        return 1;
    }

    // Source : 2048 x 2048, calculee une fois, gardee pour toutes les mesures.
    NkImage source = photo.Resize(2048, 2048, NkResizeFilter::NK_LANCZOS3);
    if (!source.IsValid() || source.Width() != 2048 || source.Height() != 2048) {
        std::cerr << "source 2048 x 2048 invalide\n";
        return 1;
    }

    const Filtre filtres[] = {
        {"NK_NEAREST",  NkResizeFilter::NK_NEAREST,  "nearest.png"},
        {"NK_BILINEAR", NkResizeFilter::NK_BILINEAR, "bilinear.png"},
        {"NK_BICUBIC",  NkResizeFilter::NK_BICUBIC,  "bicubic.png"},
        {"NK_LANCZOS3", NkResizeFilter::NK_LANCZOS3, "lanczos3.png"},
    };
    const int nbFiltres = 4;

    NkImage resultats[4];
    double  moyennes[4] = {0, 0, 0, 0};

    for (int f = 0; f < nbFiltres; ++f) {
        // Une reduction "a blanc" : la premiere paie des couts que les suivantes ne paient pas.
        (void)source.Resize(256, 256, filtres[f].filtre);

        double total = 0.0;
        for (int i = 0; i < kRepetitions; ++i) {
            NkChrono chrono;
            NkImage r = source.Resize(256, 256, filtres[f].filtre);
            total += static_cast<double>(chrono.Elapsed().ToMicroseconds());
            if (i == kRepetitions - 1) {
                resultats[f] = r;
            }
        }
        moyennes[f] = total / kRepetitions;
        resultats[f].SavePNG(filtres[f].fichier);
    }

    // Comparaison pixel par pixel avec le bilineaire (indice 1).
    std::ofstream out("mesures.txt");
    for (int f = 0; f < nbFiltres; ++f) {
        const long long diff = CompterDifferences(resultats[f], resultats[1]);
        out << filtres[f].nom << " : " << static_cast<long long>(moyennes[f] + 0.5)
            << " us, differences : " << diff << "\n";
        std::cout << filtres[f].nom << " : " << static_cast<long long>(moyennes[f] + 0.5)
                  << " us, differences : " << diff << "\n";
    }
    return 0;
}
