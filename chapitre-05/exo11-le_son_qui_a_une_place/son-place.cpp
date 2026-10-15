// son-place.cpp - Exercice 11 : une pluie en boucle, placee a la fenetre, et l'auditeur sur la camera.
// Usage autonome : son-place <camX> <camY> <camZ>   (par defaut : 0 1.7 0). Ajoutez "--sans" pour tester sans positional.
// Dans la salle : appelez DemarrerPluie() une fois au demarrage avec la position de la camera.
#include "NKAudio/NkAudio.h"

#include <chrono>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <thread>

using namespace nkentseu::audio;

// Distances choisies : minDistance 1 m (en dessous, le son ne grossit plus), maxDistance 15 m
// (la salle fait 4 m de large : au-dela de 15 m la pluie se tait), rolloffFactor 1 (loi 1/d).
static const float kMinDistance = 1.0f;
static const float kMaxDistance = 15.0f;

static bool DemarrerPluie(float camX, float camY, float camZ, bool positional) {
    AudioEngineConfig cfg;
    cfg.sampleRate = 48000;
    AudioEngine& moteur = AudioEngine::Instance();
    if (!moteur.Initialize(cfg)) {
        return false;
    }
    // L'auditeur prend la place de la camera, une fois : position, puis regard (avant) et haut.
    moteur.SetListenerPosition(camX, camY, camZ);
    moteur.SetListenerOrientation(0.f, 0.f, -1.f,   // direction du regard
                                  0.f, 1.f,  0.f);  // haut

    auto pluie = AudioGenerator::GenerateNoise(4.f, WaveformType::NOISE_PINK);
    VoiceParams p;
    p.looping = true;
    p.source3d.positional     = positional;      // le champ qu'on oublie : sans lui, le son reste au centre
    p.source3d.position       = {-1.98f, 1.40f, -0.90f};   // premiere fenetre
    p.source3d.minDistance    = kMinDistance;
    p.source3d.maxDistance    = kMaxDistance;
    p.source3d.rolloffFactor  = 1.0f;
    moteur.Play(pluie, p);                      // reglages donnes AVANT Play
    return true;
}

int main(int argc, char** argv) {
    const float x = (argc > 3) ? static_cast<float>(std::atof(argv[1])) : 0.f;
    const float y = (argc > 3) ? static_cast<float>(std::atof(argv[2])) : 1.7f;
    const float z = (argc > 3) ? static_cast<float>(std::atof(argv[3])) : 0.f;
    const bool positional = !(argc > 4 && std::strcmp(argv[4], "--sans") == 0);
    if (!DemarrerPluie(x, y, z, positional)) {
        std::cerr << "moteur de son : initialisation ratee\n";
        return 1;
    }
    std::this_thread::sleep_for(std::chrono::seconds(10));   // ecoutez au casque
    AudioEngine::Instance().Shutdown();
    return 0;
}
