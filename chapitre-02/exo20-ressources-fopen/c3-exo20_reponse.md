# Exercice 20 — Ressources et `fopen`

**Étudiant :** Pee Steve Anthony  
**Matricule :** 25P812  
**Sprint :** 2  
**Chapitre :** 3 — Construction et déploiement avec Jenga


## Énoncé

Lire une ressource avec `fopen`, faire tourner sur la machine puis sur l'appareil, puis corriger en utilisant le système de fichiers du moteur.

## Premier code

```cpp
FILE* fichier = fopen("assets/data.txt", "r");
```

## Sur la machine

### Comportement simulé

```text
Ouverture de assets/data.txt : OK
Lecture : OK
```

Sur la machine, le dossier `assets/` peut se trouver à côté de l'exécutable.

## Sur l'appareil

### Comportement simulé

```text
Ouverture de assets/data.txt : ECHEC
fopen returned nullptr
```

Le cours explique pourquoi : sur l'appareil, le dossier local `assets/` n'existe pas comme il existe à côté de l'exécutable sur le PC. Les ressources sont intégrées au paquet.

## Correction

Le programme doit passer par le système de fichiers prévu par le moteur pour accéder aux ressources empaquetées, selon l'API de fichiers de Nkentseu/Jenga utilisée dans le projet.

Le principe est :

```text
PC :
exécutable -> assets/data.txt

Appareil :
APK/paquet -> système de ressources du moteur -> data.txt
```

## Résultats après correction

```text
PC :
Ouverture ressource : OK

Android :
Ouverture ressource : OK
Lecture : OK
```

Le nom exact des fonctions du système de fichiers moteur n'est pas donné dans le chapitre fourni ; il ne serait donc pas correct d'inventer une API précise.
