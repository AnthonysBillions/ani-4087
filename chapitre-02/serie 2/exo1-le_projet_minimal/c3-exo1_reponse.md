# Exercice 1 — Le projet minimal

**Étudiant :** Pee Steve Anthony  
**Matricule :** 25P812  
**Sprint :** 2  
**Chapitre :** 3 — Construction et déploiement avec Jenga


## Énoncé

Écrire le fichier de projet de la salle et faire construire un programme minimal contenant une fonction `main` qui retourne zéro.

## 1. Fichier `project.jenga`

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
```

Le bloc `workspace` est nécessaire : le cours précise qu'un projet doit toujours vivre dans un espace de travail.

## 2. Fichier `src/main.cpp`

```cpp
int main()
{
    return 0;
}
```

## 3. Construction

Commande utilisée :

```text
jenga build
```

### Sortie de rendu simulée

```text
Jenga 2.8.0
Workspace: MaSalleWks
Project: MaSalle
Configuration: Debug
System: Windows

[1/1] Compiling src/main.cpp
[1/1] Linking MaSalle.exe
Build succeeded.
```

## 4. Explication

Le projet est volontairement minimal. `windowedapp()` indique que le programme est une application avec fenêtre et non une application console. `language("C++")` et `cppdialect("C++17")` fixent le langage et sa version.

La construction comporte notamment la compilation puis l'édition de liens. Pour cet exercice, il n'y a qu'un seul fichier source et aucune bibliothèque supplémentaire à ajouter.

La sortie ci-dessus est une **sortie de rendu simulée**, car le fichier fourni ne contient pas une capture de mon environnement Jenga. Sur la machine utilisée pour rendre le devoir, cette sortie doit être remplacée par la sortie réelle de `jenga build`.
