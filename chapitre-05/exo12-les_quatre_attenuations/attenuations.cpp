// attenuations.cpp - Exercice 12 : gain des quatre modeles d'attenuation a cinq distances.
// Ni fenetre ni sortie sonore. Ecrit mesures.txt (40 lignes).
#include "NKAudio/NkAudio.h"

#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>

using namespace nkentseu::audio;

static const int kTrames = 48000;
static const int kBloc   = 256;

// Racine de la moyenne des carres sur les DEUX oreilles ensemble.
static double MesurerRms(AudioEngine& moteur) {
    std::vector<float> bloc(kBloc * 2);
    double somme = 0.0;
    long   n     = 0;
    for (int fait = 0; fait < kTrames; fait += kBloc) {
        moteur.RenderToBuffer(bloc.data(), kBloc);
        for (int i = 0; i < kBloc * 2; ++i) {
            somme += static_cast<double>(bloc[i]) * bloc[i];
        }
        n += kBloc * 2;
    }
    return std::sqrt(somme / n);
}

static double MesurerUneFois(AudioEngine& moteur, const AudioSample& son, AttenuationModel modele,
                             float rolloff, float distance) {
    VoiceParams p;
    p.looping = true;
    p.source3d.positional        = true;
    p.source3d.minDistance       = 1.0f;
    p.source3d.maxDistance       = 100.0f;
    p.source3d.rolloffFactor     = rolloff;
    p.source3d.attenuationModel  = modele;
    p.source3d.position          = {0.f, 0.f, -distance};   // devant l'auditeur
    auto voix = moteur.Play(son, p);
    const double rms = MesurerRms(moteur);
    moteur.Stop(voix);                                       // la source reste immobile pendant la mesure
    return rms;
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
    moteur.SetListenerOrientation(0.f, 0.f, -1.f, 0.f, 1.f, 0.f);

    auto son = AudioGenerator::GenerateTone(440.f, 2.f, WaveformType::SINE, 48000, 0.1f);

    const AttenuationModel modeles[] = {AttenuationModel::NONE, AttenuationModel::INVERSE,
                                        AttenuationModel::LINEAR, AttenuationModel::EXPONENTIAL};
    const char*  noms[]      = {"NONE", "INVERSE", "LINEAR", "EXPONENTIAL"};
    const float  distances[] = {0.5f, 1.f, 2.f, 4.f, 8.f};
    const float  rolloffs[]  = {1.f, 2.f};

    std::ofstream out("mesures.txt");
    for (float rolloff : rolloffs) {
        double reference[5];
        for (int d = 0; d < 5; ++d) {
            reference[d] = MesurerUneFois(moteur, son, AttenuationModel::NONE, rolloff, distances[d]);
        }
        for (int m = 0; m < 4; ++m) {
            for (int d = 0; d < 5; ++d) {
                const double rms  = (m == 0) ? reference[d]
                                             : MesurerUneFois(moteur, son, modeles[m], rolloff, distances[d]);
                const double gain = rms / reference[d];       // rapporte a NONE a la meme distance
                char ligne[96];
                std::snprintf(ligne, sizeof(ligne), "%s, rolloff %d, %g m : %.3f",
                              noms[m], static_cast<int>(rolloff), distances[d], gain);
                out << ligne << "\n";
                std::cout << ligne << "\n";
            }
        }
    }
    moteur.Shutdown();
    AudioLoader::Free(son);
    return 0;
}
