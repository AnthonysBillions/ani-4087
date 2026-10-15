// panneau.cpp - Exercice 7 : le mot "Sortie" au-dessus de la porte, police embarquee du moteur.
// Etape 1 (hors ligne) : fabriquer panneau.png a partir de l'atlas. Etape 2 : le poser sur un pave.
#include "NKFont/NkFont.h"
#include "NKFont/Embedded/NkFontEmbedded.h"
#include "NKImage/Core/NkImage.h"
#include "NKRenderer/Materials/NkMaterial.h"

#include <cmath>
#include <cstdint>
#include <iostream>

using namespace nkentseu;

static const char* kTexte = "Sortie";

// Melange la couleur du texte avec celle du fond selon la couverture (0..255).
static uint8_t Melanger(uint8_t fond, uint8_t texte, int couverture) {
    return static_cast<uint8_t>((fond * (255 - couverture) + texte * couverture) / 255);
}

int main() {
    NkFontAtlas atlas;
    NkFont* police = NkFontEmbedded::AddToAtlas(atlas, NkEmbeddedFontId::Inter, 32.f);
    if (police == nullptr || !atlas.Build()) {
        std::cerr << "atlas : construction ratee\n";
        return 1;
    }

    unsigned char* pixels = nullptr;
    int texW = 0;
    int texH = 0;
    atlas.GetTexDataAsAlpha8(&pixels, &texW, &texH);   // 1 octet par pixel = couverture
    if (pixels == nullptr) {
        std::cerr << "atlas : pas de pixels\n";
        return 1;
    }

    // Taille de l'image : somme des avances x (ascent - descent).
    float largeurF = 0.f;
    for (const char* c = kTexte; *c != '\0'; ++c) {
        const NkFontGlyph* g = police->FindGlyph(static_cast<unsigned>(*c));
        if (g != nullptr) {
            largeurF += g->advanceX;
        }
    }
    const int largeur = static_cast<int>(std::ceil(largeurF));
    const int hauteur = static_cast<int>(std::ceil(police->ascent - police->descent));
    const int base    = static_cast<int>(std::ceil(police->ascent));   // ligne de base, depuis le haut

    // Fond vert, 0xRRGGBBAA. Texte blanc.
    NkImage image = NkImage::Create(largeur, hauteur, 4, 0x1B7F3BFF);
    uint8_t* dst = image.Pixels();
    const uint8_t texteRGB[3] = {255, 255, 255};

    float curseur = 0.f;
    for (const char* c = kTexte; *c != '\0'; ++c) {
        const NkFontGlyph* g = police->FindGlyph(static_cast<unsigned>(*c));
        if (g == nullptr) {
            continue;
        }
        const int xa = static_cast<int>(std::floor(curseur + g->x0));
        const int xb = static_cast<int>(std::ceil(curseur + g->x1));
        const int ya = static_cast<int>(std::floor(base + g->y0));
        const int yb = static_cast<int>(std::ceil(base + g->y1));

        for (int y = ya; y < yb; ++y) {
            for (int x = xa; x < xb; ++x) {
                if (x < 0 || x >= largeur || y < 0 || y >= hauteur) {
                    continue;
                }
                // Fraction dans le rectangle de la lettre -> coordonnees u,v dans l'atlas.
                const float fx = (x + 0.5f - (curseur + g->x0)) / (g->x1 - g->x0);
                const float fy = (y + 0.5f - (base + g->y0)) / (g->y1 - g->y0);
                const float u  = g->u0 + fx * (g->u1 - g->u0);
                const float v  = g->v0 + fy * (g->v1 - g->v0);
                int ax = static_cast<int>(u * texW);
                int ay = static_cast<int>(v * texH);
                if (ax < 0) ax = 0;
                if (ay < 0) ay = 0;
                if (ax >= texW) ax = texW - 1;
                if (ay >= texH) ay = texH - 1;
                const int couverture = pixels[ay * texW + ax];
                uint8_t* p = dst + (y * largeur + x) * 4;
                p[0] = Melanger(p[0], texteRGB[0], couverture);
                p[1] = Melanger(p[1], texteRGB[1], couverture);
                p[2] = Melanger(p[2], texteRGB[2], couverture);
            }
        }
        curseur += g->advanceX;
    }

    // Si le mot est a l'envers ou en miroir : image.FlipVertical() / image.FlipHorizontal().
    if (!image.SavePNG("panneau.png")) {
        std::cerr << "ecriture de panneau.png ratee\n";
        return 1;
    }
    std::cout << "atlas : " << atlas.texWidth << " x " << atlas.texHeight << "\n";
    std::cout << "image : " << largeur << " x " << hauteur << "\n";
    return 0;
}

// ---- Etape 2, dans la salle (avant la boucle puis dans la boucle) ----
// auto tex = renderer->GetTextures()->Load(NkPath::LocateResource("panneau.png"));
// auto* mat = NkMaterial::Create(renderer->GetMaterials(), NkMaterialType::NK_PBR_METALLIC);
// mat->SetAlbedoMap(tex);
// Pave de 20 cm de haut, largeur = 0.20 * largeur/hauteur de l'image, centre (-0.70, 2.20, -1.993),
// epaisseur 0.01 : sa face arriere est a z = -1.998, decollee de 2 mm du mur (z = -2) -> pas de clignotement.
// dc.material = mat->GetInstHandle();
// Camera 3 m : (-0.70, 1.70, 1.00) ; camera 50 cm : (-0.70, 2.20, -1.50) ; elle regarde (-0.70, 2.20, -2.00).
