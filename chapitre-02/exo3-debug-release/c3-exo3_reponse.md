# Exercice 3 — Debug et Release

**Étudiant :** Pee Steve Anthony  
**Matricule :** 25P812  
**Sprint :** 2  
**Chapitre :** 3 — Construction et déploiement avec Jenga


## Énoncé

Construire le projet en Debug puis en Release et comparer la taille des exécutables ainsi que le temps de construction.

## Commandes

```text
jenga build --config Debug
jenga build --config Release
```

## Tableau de rendu

| Configuration | Taille de l'exécutable | Temps de construction |
|---|---:|---:|
| Debug | 128 Ko | 0,42 s |
| Release | 32 Ko | 0,31 s |

Les quatre nombres demandés sont donc :

```text
Debug :    128 Ko ; 0,42 s
Release :   32 Ko ; 0,31 s
```

## Analyse

La configuration Debug conserve davantage d'informations utiles au développement et au débogage. La configuration Release est destinée à produire une version optimisée pour l'exécution.

Le cours insiste surtout sur un point : **il ne faut pas mesurer les performances du programme en Debug**. Une différence importante entre Debug et Release peut venir de la configuration de construction et non du programme lui-même.

Les valeurs numériques ci-dessus sont des **valeurs de rendu simulées**. Elles doivent être remplacées par les quatre valeurs obtenues avec Jenga sur la machine de travail.
