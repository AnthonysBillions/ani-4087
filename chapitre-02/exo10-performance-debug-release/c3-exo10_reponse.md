# Exercice 10 — Mesure d'un calcul lourd

**Étudiant :** Pee Steve Anthony  
**Matricule :** 25P812  
**Sprint :** 2  
**Chapitre :** 3 — Construction et déploiement avec Jenga


## Énoncé

Écrire une boucle de calcul lourd, la chronométrer, puis comparer Debug et Release. Une image de casque dure environ 11 ms.

## Exemple de programme

```cpp
#include <chrono>
#include <iostream>

int main()
{
    volatile double resultat = 0.0;

    auto debut = std::chrono::high_resolution_clock::now();

    for (long long i = 0; i < 50000000; ++i)
    {
        resultat += (i % 1000) * 0.000001;
    }

    auto fin = std::chrono::high_resolution_clock::now();

    double ms =
        std::chrono::duration<double, std::milli>(fin - debut).count();

    std::cout << "Temps : " << ms << " ms" << std::endl;
    std::cout << "Resultat : " << resultat << std::endl;

    return 0;
}
```

## Rapport simulé

| Configuration | Temps mesuré |
|---|---:|
| Debug | 620 ms |
| Release | 95 ms |

## Analyse

Le budget donné par le cours pour une image de casque est de **11 ms**.

La mesure Debug, ici simulée à 620 ms, aurait conduit à une très mauvaise décision si on l'avait prise comme mesure représentative du programme final. Elle mélange le coût du calcul avec les caractéristiques de la configuration Debug.

La bonne pratique enseignée est donc de mesurer les performances avec la configuration Release.

Les temps sont des valeurs simulées et doivent être remplacés par les mesures réelles.
