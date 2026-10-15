// inexistant.cpp - Exercice 2 : charger une image qui n'existe pas, deux fois.
// A lancer depuis le dossier du projet : le journal est ecrit dans logs/app.log.
#include "NKImage/Core/NkImage.h"
#include "NKRenderer/Materials/NkMaterial.h"

#include <iostream>

using namespace nkentseu;

// --- Partie 1 : NkImage, cinq lignes ---
void ChargerImageAbsente() {
    NkImage img;
    const bool charge = img.Load("murs/nexistepas.png");
    std::cout << "charge : " << charge << ", valide : " << img.IsValid()
              << ", largeur : " << img.Width() << ", hauteur : " << img.Height() << "\n";
}

// --- Partie 2 : le meme chemin, comme texture d'un mur de la salle ---
// A appeler une seule fois, avant la boucle, avec le renderer de la salle.
// Retourne le materiau : le pave du mur le recevra par dc.material = mat->GetInstHandle().
template <typename TRenderer>
auto CreerMurAbsent(TRenderer* renderer) {
    auto tex = renderer->GetTextures()->Load("murs/nexistepas.png");   // ne plante pas
    auto* mat = NkMaterial::Create(renderer->GetMaterials(), NkMaterialType::NK_PBR_METALLIC);
    mat->SetAlbedoMap(tex);                                             // texture "vide" : le mur ne change pas
    return mat;
}
