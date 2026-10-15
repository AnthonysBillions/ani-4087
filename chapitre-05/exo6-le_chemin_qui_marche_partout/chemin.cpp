// chemin.cpp - Exercice 6 : un chemin qui marche depuis n'importe quel dossier.
// On ne donne plus "murs/beton.png" tel quel a Load : on le fait localiser par le moteur.
#include "NKFileSystem/NkPath.h"
#include "NKRenderer/Materials/NkMaterial.h"

#include <iostream>

using namespace nkentseu;

template <typename TRenderer>
NkMaterial* ChargerMurLocalise(TRenderer* renderer) {
    // LocateResource rend une chaine vide quand il ne trouve rien : on la teste avant Load.
    auto chemin = NkPath::LocateResource("murs/beton.png");
    if (chemin.Empty()) {
        std::cerr << "ressource introuvable : murs/beton.png\n";
        return nullptr;
    }
    auto tex = renderer->GetTextures()->Load(chemin);
    NkMaterial* mat = NkMaterial::Create(renderer->GetMaterials(), NkMaterialType::NK_PBR_METALLIC);
    if (mat != nullptr) {
        mat->SetAlbedoMap(tex);
    }
    return mat;
}
