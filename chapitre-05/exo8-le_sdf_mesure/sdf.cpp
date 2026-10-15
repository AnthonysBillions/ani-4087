// sdf.cpp - Exercice 8 : le panneau "Sortie" avec un atlas ordinaire et un atlas SDF.
// Produit ordinaire.png et sdf.png (meme taille) et atlas.txt. Les deux images se posent
// ensuite, l'une apres l'autre, au-dessus de la porte comme dans l'exercice du panneau.
#include "NKFont/NkFont.h"
#include "NKFont/Embedded/NkFontEmbedded.h"
#include "NKImage/Core/NkImage.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>

using namespace nkentseu;

static const char* kTexte  = "Sortie";
static const int   kEchelle = 8;        // image = 8 fois la taille des lettres de l'atlas
static const float kS       = 0.02f;    // douceur du bord SDF, justifiee plus bas

// Regle du nuanceur kNkFontFragSDF, ecrite en C++.
static float smoothstep(float a, float b, float x) {
    float t = (x - a) / (b - a);
    t = std::min(std::max(t, 0.0f), 1.0f);
    return t * t * (3.0f - 2.0f * t);
}

// Lecture bilineaire de l'atlas (octets 0..255) entre les quatre pixels voisins.
static float LireBilineaire(const unsigned char* px, int w, int h, float u, float v) {
    const float x  = u * w - 0.5f;
    const float y  = v * h - 0.5f;
    const int   x0 = static_cast<int>(std::floor(x));
    const int   y0 = static_cast<int>(std::floor(y));
    const float fx = x - x0;
    const float fy = y - y0;
    auto at = [&](int xx, int yy) {
        xx = std::min(std::max(xx, 0), w - 1);
        yy = std::min(std::max(yy, 0), h - 1);
        return static_cast<float>(px[yy * w + xx]);
    };
    const float haut = at(x0, y0) * (1 - fx) + at(x0 + 1, y0) * fx;
    const float bas  = at(x0, y0 + 1) * (1 - fx) + at(x0 + 1, y0 + 1) * fx;
    return haut * (1 - fy) + bas * fy;
}

struct Atlas {
    NkFontAtlas atlas;
    NkFont*     police = nullptr;
    unsigned char* pixels = nullptr;
    int w = 0;
    int h = 0;
};

static bool Construire(Atlas& a, float taille, bool sdf) {
    if (sdf) {
        a.atlas.sdfMode   = true;
        a.atlas.sdfSpread = 6;
    }
    a.police = NkFontEmbedded::AddToAtlas(a.atlas, NkEmbeddedFontId::Inter, taille);
    if (a.police == nullptr || !a.atlas.Build()) {
        return false;
    }
    a.atlas.GetTexDataAsAlpha8(&a.pixels, &a.w, &a.h);
    return a.pixels != nullptr;
}

// Fabrique l'image du panneau. Meme taille quel que soit le mode : seule la methode change.
static NkImage FabriquerImage(const Atlas& a, bool sdf, int largeur, int hauteur, int base) {
    NkImage image = NkImage::Create(largeur, hauteur, 4, 0x1B7F3BFF);
    uint8_t* dst = image.Pixels();
    float curseur = 0.f;
    for (const char* c = kTexte; *c != '\0'; ++c) {
        const NkFontGlyph* g = a.police->FindGlyph(static_cast<unsigned>(*c));
        if (g == nullptr) {
            continue;
        }
        const int xa = static_cast<int>(std::floor(curseur + g->x0 * kEchelle));
        const int xb = static_cast<int>(std::ceil(curseur + g->x1 * kEchelle));
        const int ya = static_cast<int>(std::floor(base + g->y0 * kEchelle));
        const int yb = static_cast<int>(std::ceil(base + g->y1 * kEchelle));
        for (int y = std::max(ya, 0); y < std::min(yb, hauteur); ++y) {
            for (int x = std::max(xa, 0); x < std::min(xb, largeur); ++x) {
                const float fx = (x + 0.5f - (curseur + g->x0 * kEchelle)) / ((g->x1 - g->x0) * kEchelle);
                const float fy = (y + 0.5f - (base + g->y0 * kEchelle)) / ((g->y1 - g->y0) * kEchelle);
                const float u  = g->u0 + fx * (g->u1 - g->u0);
                const float v  = g->v0 + fy * (g->v1 - g->v0);
                const float valeur = LireBilineaire(a.pixels, a.w, a.h, u, v);
                // Ordinaire : valeur/255 = couverture. SDF : 0,5 = le bord, au-dessus = dedans.
                const float alpha = sdf ? smoothstep(0.5f - kS, 0.5f + kS, valeur / 255.0f)
                                        : valeur / 255.0f;
                uint8_t* p = dst + (y * largeur + x) * 4;
                for (int k = 0; k < 3; ++k) {
                    p[k] = static_cast<uint8_t>(p[k] * (1.0f - alpha) + 255.0f * alpha);
                }
            }
        }
        curseur += g->advanceX * kEchelle;
    }
    return image;
}

int main() {
    Atlas ordinaire32, sdf32, ordinaire128;
    if (!Construire(ordinaire32, 32.f, false) || !Construire(sdf32, 32.f, true)
        || !Construire(ordinaire128, 128.f, false)) {
        std::cerr << "construction d'un atlas ratee\n";
        return 1;
    }

    std::ofstream out("atlas.txt");
    out << "ordinaire 32 : " << ordinaire32.w << " x " << ordinaire32.h << "\n";
    out << "sdf 32 : "       << sdf32.w       << " x " << sdf32.h       << "\n";
    out << "ordinaire 128 : "<< ordinaire128.w<< " x " << ordinaire128.h<< "\n";

    // Memes dimensions pour les deux images : calculees une seule fois, depuis l'atlas ordinaire.
    float adv = 0.f;
    for (const char* c = kTexte; *c != '\0'; ++c) {
        const NkFontGlyph* g = ordinaire32.police->FindGlyph(static_cast<unsigned>(*c));
        if (g != nullptr) {
            adv += g->advanceX;
        }
    }
    const int largeur = static_cast<int>(std::ceil(adv * kEchelle));
    const int hauteur = static_cast<int>(std::ceil(kEchelle * (ordinaire32.police->ascent - ordinaire32.police->descent)));
    const int base    = static_cast<int>(std::ceil(kEchelle * ordinaire32.police->ascent));

    NkImage imgOrd = FabriquerImage(ordinaire32, false, largeur, hauteur, base);
    NkImage imgSdf = FabriquerImage(sdf32, true, largeur, hauteur, base);
    imgOrd.SavePNG("ordinaire.png");
    imgSdf.SavePNG("sdf.png");
    std::cout << "images : " << largeur << " x " << hauteur << " (" << largeur * hauteur << " pixels)\n";
    return 0;
}

// Choix de s : sur l'image, la distance normalisee varie d'environ 1/(2*spread*8) = 0,0104
// par pixel de sortie (spread 6, echelle 8). Un bord anticrenele sur environ un a deux pixels
// demande un demi-intervalle s de l'ordre de 0,01 a 0,02 ; en dessous on voit des escaliers,
// au-dessus le bord devient flou. J'ai garde 0,02 apres essai de 0,005 / 0,01 / 0,02 / 0,05.
