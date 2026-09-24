# Exercice 21 — Une seconde sur PC et sur appareil

**Étudiant :** Pee Steve Anthony  
**Matricule :** 25P812  
**Sprint :** 2  
**Chapitre :** 3 — Construction et déploiement avec Jenga


## Énoncé

Écrire une boucle prenant environ une seconde sur la machine, la chronométrer, puis refaire la mesure sur l'appareil. Analyser le budget de 11 ms.

## Exemple

```cpp
#include <chrono>
#include <iostream>

int main()
{
    volatile double x = 1.0;

    auto start = std::chrono::high_resolution_clock::now();

    for (long long i = 0; i < 100000000; ++i)
    {
        x = x * 1.0000001 + 0.0000001;
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::cout
        << std::chrono::duration<double, std::milli>(end - start).count()
        << " ms\n";

    return 0;
}
```

## Rapport simulé

| Plateforme | Temps |
|---|---:|
| PC | 1010 ms |
| Appareil Android | 2480 ms |

## Analyse

Le calcul qui dure environ une seconde sur le PC prend ici environ 2,48 secondes sur l'appareil.

Le cours donne un budget d'environ **11 ms par image de casque**. Un calcul de plusieurs centaines de millisecondes ou de plusieurs secondes ne peut donc pas être placé directement dans la boucle de rendu à chaque image.

Il faut alors réduire le coût, répartir le travail ou le faire en dehors du chemin critique de rendu.

Les temps sont simulés et doivent être remplacés par les mesures réelles.
