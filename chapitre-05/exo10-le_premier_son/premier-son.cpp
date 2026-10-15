// premier-son.cpp - Exercice 10 : faire jouer un son au demarrage, sans position dans l'espace.
// Projet lie a NKAudio : kit R3D (Kits/R3D/R3D.jenga, user3d(), Kits/R3D/Resources).
#include "NKAudio/NkAudio.h"

#include <chrono>
#include <iostream>
#include <thread>

using namespace nkentseu::audio;

int main() {
    AudioEngineConfig cfg;
    cfg.sampleRate = 48000;
    AudioEngine& moteur = AudioEngine::Instance();
    if (!moteur.Initialize(cfg)) {
        std::cerr << "moteur de son : initialisation ratee\n";
        return 1;
    }
    std::cout << "dorsal : "    << moteur.GetBackendName() << "\n";
    std::cout << "frequence : " << moteur.GetSampleRate()  << "\n";
    std::cout << "tampon : "    << moteur.GetBufferSize()  << "\n";
    std::cout << "latence : "   << moteur.GetLatencyMs()   << "\n";

    auto son = AudioGenerator::GenerateTone(440.f, 1.f);   // ou AudioLoader::Load("mon-son.wav")
    VoiceParams params;                                      // pas de source3d : son non spatialise
    moteur.Play(son, params);

    // Boucle de rendu de la salle : ici, une attente. Le son joue sur un autre fil.
    for (int i = 0; i < 150; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    moteur.Shutdown();
    AudioLoader::Free(son);   // apres Shutdown : une voix qui joue encore lit ses donnees
    return 0;
}
