# Exercice 18 — Lire le journal du système

**Étudiant :** Pee Steve Anthony  
**Matricule :** 25P812  
**Sprint :** 2  
**Chapitre :** 3 — Construction et déploiement avec Jenga


## Énoncé

Afficher trois lignes au démarrage puis les retrouver dans le journal système. Rendre la commande de filtrage.

## Exemple de programme

```cpp
#include <android/log.h>

int main()
{
    __android_log_print(ANDROID_LOG_INFO, "MaSalle", "Programme demarre");
    __android_log_print(ANDROID_LOG_INFO, "MaSalle", "Initialisation terminee");
    __android_log_print(ANDROID_LOG_INFO, "MaSalle", "Fenetre prete");

    return 0;
}
```

## Commande de filtrage

```text
adb logcat -s MaSalle:I *:S
```

Elle demande principalement les messages du tag `MaSalle` et masque les autres niveaux non souhaités.

## Sortie simulée

```text
I/MaSalle: Programme demarre
I/MaSalle: Initialisation terminee
I/MaSalle: Fenetre prete
```

Le but est de ne pas devoir chercher manuellement les trois lignes au milieu de tout le journal Android.
