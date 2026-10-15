// formats.cpp - Exercice 1 : une meme photo ecrite dans cinq formats, puis relue.
// Lancer depuis le dossier du projet, avec photo.jpg dedans.
#include "NKImage/Core/NkImage.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace nkentseu;

struct Format {
    std::string nom;
    std::string fichier;
    bool (*ecrire)(NkImage&, const char*);
};

static bool EcrirePNG(NkImage& i, const char* f)  { return i.SavePNG(f); }
static bool EcrireJPEG(NkImage& i, const char* f) { return i.SaveJPEG(f); }
static bool EcrireBMP(NkImage& i, const char* f)  { return i.SaveBMP(f); }
static bool EcrireTGA(NkImage& i, const char* f)  { return i.SaveTGA(f); }
static bool EcrireQOI(NkImage& i, const char* f)  { return i.SaveQOI(f); }

int main() {
    NkImage photo;
    if (!photo.Load("photo.jpg")) {
        std::cerr << "Impossible de charger photo.jpg (verifiez le dossier de lancement)\n";
        return 1;
    }

    const std::vector<Format> formats = {
        {"png",  "sortie.png",  EcrirePNG},
        {"jpeg", "sortie.jpg",  EcrireJPEG},
        {"bmp",  "sortie.bmp",  EcrireBMP},
        {"tga",  "sortie.tga",  EcrireTGA},
        {"qoi",  "sortie.qoi",  EcrireQOI},
    };

    std::ofstream rapport("formats.txt");
    for (const Format& f : formats) {
        if (!f.ecrire(photo, f.fichier.c_str())) {
            rapport << f.nom << " : ecriture ratee\n";
            continue;
        }
        NkImage relue;
        if (!relue.Load(f.fichier.c_str()) || !relue.IsValid()) {
            rapport << f.nom << " : " << std::filesystem::file_size(f.fichier) << " octets, illisible\n";
            continue;
        }
        const auto octets = std::filesystem::file_size(f.fichier);
        rapport << f.nom << " : " << octets << " octets, "
                << relue.Width() << " x " << relue.Height() << "\n";
        std::cout << f.nom << " : " << octets << " octets, "
                  << relue.Width() << " x " << relue.Height() << "\n";
    }
    return 0;
}
