# Exercice 6 — Filtre conditionnel

**Étudiant :** Pee Steve Anthony  
**Matricule :** 25P812  
**Sprint :** 2  
**Chapitre :** 3 — Construction et déploiement avec Jenga


## Énoncé

Écrire un filtre dont la condition est fausse sur la machine, puis la rendre vraie et prouver qu'elle est appliquée. Ne pas utiliser `jenga info` pour cette preuve : le cours précise que sa sortie reste identique concernant les définitions.

## 1. Fichier de projet

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

        with filter("system:Linux"):
            defines(["PLATEFORME_TEST"])
```

Sur une machine Windows, la condition `system:Linux` est fausse.

## 2. `main.cpp`

```cpp
#include <iostream>

int main()
{
#ifdef PLATEFORME_TEST
    std::cout << "PLATEFORME_TEST est defini" << std::endl;
#else
    std::cout << "PLATEFORME_TEST n'est pas defini" << std::endl;
#endif

    return 0;
}
```

## 3. Condition fausse

### Sortie simulée

```text
PLATEFORME_TEST n'est pas defini
```

La définition n'est pas appliquée puisque la plateforme est Windows.

## 4. Condition vraie

Pour tester le comportement inverse, le filtre est temporairement remplacé par :

```python
with filter("system:Windows"):
    defines(["PLATEFORME_TEST"])
```

### Sortie simulée

```text
PLATEFORME_TEST est defini
```

## 5. Pourquoi ne pas utiliser `jenga info` ?

Le cours précise que `jenga info` ne montre pas les définitions issues de ce filtre. Même `jenga build --verbose` n'apporte pas la preuve attendue.

La bonne méthode consiste donc à faire constater l'effet par le programme lui-même.

La sortie est simulée pour le rendu ; le principe et les messages attendus suivent l'exercice.
