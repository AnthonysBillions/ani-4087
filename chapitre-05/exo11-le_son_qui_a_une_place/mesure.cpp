// mesure.cpp - Exercice 11 : ce que le moteur envoie a chaque oreille. Ni fenetre, ni sortie sonore.
#include "NKAudio/NkAudio.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace nkentseu::audio;

static const int kTrames = 48000;
static const int kBloc   = 256;

struct Rms {
    double gauche;
    double droite;
};

// Rend 48 000 trames par blocs de 256 ; les echantillons sont ranges G, D, G, D...
static Rms Mesurer(AudioEngine& moteur) {
    std::vector<float> bloc(kBloc * 2);
    double sg = 0.0;
    double sd = 0.0;
    long   n  = 0;
    for (int fait = 0; fait < kTrames; fait += kBloc) {
        moteur.RenderToBuffer(bloc.data(), kBloc);
        for (int i = 0; i < kBloc; ++i) {
            sg += static_cast<double>(bloc[2 * i])     * bloc[2 * i];
            sd += static_cast<double>(bloc[2 * i + 1]) * bloc[2 * i + 1];
        }
        n += kBloc;
    }
    return {std::sqrt(sg / n), std::sqrt(sd / n)};
}

int main() {
    AudioEngineConfig cfg;
    cfg.sampleRate = 48000;
    cfg.backend    = AudioBackendType::NULL_OUTPUT;
    AudioEngine& moteur = AudioEngine::Instance();
    if (!moteur.Initialize(cfg)) {
        std::cerr << "moteur de son : initialisation ratee\n";
        return 1;
    }
    moteur.SetListenerPosition(0.f, 0.f, 0.f);
    moteur.SetListenerOrientation(0.f, 0.f, -1.f,    // avant
                                  0.f, 1.f,  0.f);   // haut

    auto pluie = AudioGenerator::GenerateNoise(4.f, WaveformType::NOISE_PINK);

    struct Position { const char* nom; float x, y, z; };
    const Position positions[] = {
        {"gauche", -2.f, 0.f,  0.f},
        {"devant",  0.f, 0.f, -2.f},
        {"droite",  2.f, 0.f,  0.f},
    };

    std::ofstream out("mesures.txt");
    for (const Position& pos : positions) {
        for (int positional = 1; positional >= 0; --positional) {
            VoiceParams p;
            p.looping = true;
            p.source3d.positional    = (positional == 1);
            p.source3d.position      = {pos.x, pos.y, pos.z};
            p.source3d.minDistance   = 1.0f;
            p.source3d.maxDistance   = 15.0f;
            p.source3d.rolloffFactor = 1.0f;
            auto voix = moteur.Play(pluie, p);
            const Rms m = Mesurer(moteur);
            moteur.Stop(voix);                       // la source ne bouge pas pendant une mesure
            out << pos.nom << " " << positional << " : G " << m.gauche << " D " << m.droite << "\n";
            std::cout << pos.nom << " " << positional << " : G " << m.gauche << " D " << m.droite << "\n";
        }
    }
    moteur.Shutdown();
    AudioLoader::Free(pluie);
    return 0;
}
