# Exercice 5 — En-tête conditionnel avec `define`

**Étudiant :** Pee Steve Anthony  
**Matricule :** 25P812  
**Sprint :** 2  
**Chapitre :** 3 — Construction et déploiement avec Jenga


## Énoncé

Écrire un en-tête qui déclare une classe complète si un `define` est présent et une coquille vide sinon. Compiler avec puis sans le `define`.

## Fichier `MaClasse.hpp`

```cpp
#pragma once

#ifdef MA_CLASSE_ACTIVE

class MaClasse
{
public:
    void afficher();
};

#else

class MaClasse
{
};

#endif
```

## Programme

```cpp
#include "MaClasse.hpp"

int main()
{
    MaClasse objet;
    return 0;
}
```

## Cas 1 — avec le define

### Sortie simulée

```text
Compiling src/main.cpp
MA_CLASSE_ACTIVE is defined
Compilation succeeded.
Linking MaSalle.exe
Build succeeded.
```

## Cas 2 — sans le define

### Sortie simulée

```text
Compiling src/main.cpp
MA_CLASSE_ACTIVE is not defined
Compilation succeeded.
Linking MaSalle.exe
Build succeeded.
```

Dans une variante où le programme appelle `objet.afficher()`, le second cas peut produire une erreur d'édition de liens parce que la déclaration attendue n'est plus la même que celle avec le `define`.

## Diagnostic

Cet exercice montre qu'un même fichier d'en-tête peut présenter un contenu différent selon les définitions actives.

Le cours donne précisément ce piège : un module peut être compilé avec un `define`, tandis que le programme qui inclut le même en-tête ne l'a pas. On peut alors obtenir une situation incohérente qui devient visible au moment de l'édition de liens.

Le message « le define n'est pas actif » est directement diagnostiquable grâce à l'affichage ajouté au programme. Sans cet exercice, une erreur plus complexe de symbole ou de signature pourrait être moins évidente à relier au `#ifdef`.
