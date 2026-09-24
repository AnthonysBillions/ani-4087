# Exercice 13 — Toolchains disponibles

**Étudiant :** Pee Steve Anthony  
**Matricule :** 25P812  
**Sprint :** 2  
**Chapitre :** 3 — Construction et déploiement avec Jenga


## Énoncé

Lancer `jenga info -v` et rendre le tableau `Available Toolchains` en entier. Dire ce qui est présent et ce qui manque.

## Commande

```text
jenga info -v
```

### Tableau de rendu simulé

```text
Available Toolchains

Name              System       Architecture
------------------------------------------------
MSVC              Windows      x64
GCC               Windows      x64
Clang             Windows      x64
Android           Android      arm64-v8a
```

## Lecture

Dans cette simulation, les toolchains Windows sont présentes ainsi que la toolchain Android.

Pour réaliser réellement l'exercice, il faut conserver **l'intégralité du tableau obtenu sur la machine**, car la disponibilité dépend de l'installation locale.

Le cours demande précisément de lancer `jenga info -v` avant de supposer que la chaîne Android existe.

Si Android n'apparaît pas, les commandes suivantes de construction, packaging et déploiement Android ne pourront pas fonctionner correctement.

La sortie ci-dessus est simulée et doit être remplacée par la sortie réelle.
