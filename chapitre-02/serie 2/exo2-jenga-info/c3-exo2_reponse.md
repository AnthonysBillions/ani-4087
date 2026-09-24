# Exercice 2 — Lire `jenga info`

**Étudiant :** Pee Steve Anthony  
**Matricule :** 25P812  
**Sprint :** 2  
**Chapitre :** 3 — Construction et déploiement avec Jenga


## Énoncé

Lancer `jenga info` sur le projet et lire toute sa sortie. Expliquer ce qu'elle apprend qui n'était pas écrit explicitement dans le fichier de projet.

## Commande

```text
jenga info
```

### Sortie de rendu simulée

```text
Jenga 2.8.0

Workspace
  Name: MaSalleWks
  Location: .

Projects
  MaSalle
    Type: windowedapp
    Language: C++
    C++ dialect: C++17
    Location: .
    Configurations: Debug, Release
    Sources:
      src/main.cpp

System
  Windows

Output
  Debug
  Release
```

## Ce que `jenga info` apporte

Le fichier de projet donne les choix faits par l'auteur, mais `jenga info` montre la manière dont Jenga les interprète.

Il permet notamment de vérifier :

- le nom réel de l'espace de travail ;
- le projet détecté ;
- le type d'application ;
- les configurations disponibles ;
- le système cible détecté ;
- les sources retenues par le motif `src/**.cpp` ;
- les informations de sortie calculées par Jenga.

Le cours insiste sur l'intérêt de vérifier les informations de l'outil plutôt que de supposer que le fichier est interprété comme prévu.

La sortie ci-dessus est une **simulation de rendu** et doit être remplacée par la sortie réelle de `jenga info`.
