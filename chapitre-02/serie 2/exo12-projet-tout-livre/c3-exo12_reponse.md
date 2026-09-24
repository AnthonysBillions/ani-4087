# Exercice 12 — Préparer le fichier de projet pour tout le livre

**Étudiant :** Pee Steve Anthony  
**Matricule :** 25P812  
**Sprint :** 2  
**Chapitre :** 3 — Construction et déploiement avec Jenga


## Énoncé

Préparer le fichier de projet pour les chapitres à venir en ajoutant une ligne commentée par chapitre indiquant ce qu'il faudra ajouter.

## Fichier `project.jenga`

```python
from Jenga import *

with workspace("MaSalleWks", location="."):
    configurations(["Debug", "Release"])

    with project("MaSalle"):
        windowedapp()
        language("C++")
        cppdialect("C++17")
        location(".")

        files(["src/**.cpp"])

        # Chapitre suivant : ajouter les modules de base nécessaires.
        # files(["src/core/**.cpp"])

        # Chapitre suivant : ajouter les ressources du programme.
        # files(["assets/**"])

        # Chapitre suivant : ajouter les bibliothèques graphiques.
        # links(["NKRHI"])

        # Chapitre suivant : ajouter les modules de fenêtre.
        # links(["NKWindow"])

        # Chapitre suivant : ajouter les modules XR.
        # links(["NKXR"])

        # Chapitre suivant : ajouter les définitions spécifiques à Windows.
        # with filter("system:Windows"):
        #     defines(["NK_PLATFORM_WINDOWS"])

        # Chapitre suivant : ajouter les dépendances Android.
        # with filter("system:Android"):
        #     defines(["NK_PLATFORM_ANDROID"])

        # Chapitre suivant : ajouter les bibliothèques Android.
        # with filter("system:Android"):
        #     links(["log", "android"])

        # Chapitre suivant : ajouter la configuration de packaging.
        # package(...)

        # Chapitre suivant : préparer la signature.
        # sign(...)

        # Chapitre suivant : préparer le déploiement.
        # deploy(...)
```

## Explication

Les lignes sont volontairement commentées. Elles constituent une préparation du projet sans modifier immédiatement la construction actuelle.

Le cours demande de les décocher une par une au fur et à mesure de l'avancement. Cela permet de garder une trace des éléments qui devront être ajoutés.

Les noms exacts des bibliothèques et fonctions des futurs chapitres qui ne sont pas fournis dans le document source ne sont pas présentés comme certains.
