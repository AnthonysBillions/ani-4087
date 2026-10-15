// mur.cpp - Exercice 4 : une texture sur un seul mur de la salle.
// A integrer dans MaSalle : appeler InitialiserMurTexture() UNE fois avant la boucle,
// puis PaveMurTexture() a la place de Pave() pour le seul mur concerne.
#include "NKRenderer/Materials/NkMaterial.h"

using namespace nkentseu;

// Une seule instance, creee avant la boucle (pas a chaque image).
static NkMaterial* gMatMur = nullptr;

template <typename TRenderer>
bool InitialiserMurTexture(TRenderer* renderer) {
    // Le chemin part du dossier d'ou le programme est lance : lancer depuis le dossier du projet.
    auto tex = renderer->GetTextures()->Load("murs/mur.jpg");
    gMatMur = NkMaterial::Create(renderer->GetMaterials(), NkMaterialType::NK_PBR_METALLIC);
    if (gMatMur == nullptr) {
        return false;
    }
    gMatMur->SetAlbedoMap(tex);
    gMatMur->SetTriplanarTileSize(1.0f);   // facultatif : la texture se repete tous les metres
    return true;
}

// Variante de Pave : memes parametres que votre Pave, plus le materiau.
// Reprenez ici le corps de votre Pave existant ; la seule difference est la ligne du materiau.
template <typename TDrawCall>
void PaveMurTexture(TDrawCall& dc /*, vos parametres de Pave : centre, dimensions, ... */) {
    // ... remplissage habituel de dc (transformation, maillage) comme dans Pave() ...
    dc.material = gMatMur->GetInstHandle();
    // ... soumission du dc comme dans Pave() ...
}

// Dans la salle :
//   InitialiserMurTexture(renderer);        // avant la boucle
//   boucle { ...  PaveMurTexture(dc, ...mur de droite...);  les autres murs : Pave(...) comme avant }
