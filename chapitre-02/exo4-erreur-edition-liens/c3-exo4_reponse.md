# Exercice 4 — Dépendance manquante et édition de liens

**Étudiant :** Pee Steve Anthony  
**Matricule :** 25P812  
**Sprint :** 2  
**Chapitre :** 3 — Construction et déploiement avec Jenga


## Énoncé

Ajouter un module qui dépend lui-même d'un autre, puis retirer ce second module de la liste des bibliothèques. Identifier l'erreur et l'étape de construction concernée.

## Principe

Si `ModuleA` utilise `ModuleB`, mais que `ModuleB` n'est plus fourni au lieur, le compilateur peut accepter les déclarations rencontrées dans les en-têtes. Le problème apparaît ensuite lorsqu'il faut résoudre les fonctions réellement utilisées.

## Message de rendu simulé

```text
Linking MaSalle.exe
error: undefined reference to `ModuleB::fonction()'
error: linker command failed with exit code 1
Build failed.
```

## Étape concernée

L'erreur appartient à **l'édition de liens**.

Elle ne correspond pas :

- au préprocesseur ;
- à la compilation ;
- à l'assemblage.

Le symptôme important est la présence d'un symbole ou d'une fonction non résolu(e) au moment du lien.

## Méthode de diagnostic

Le cours donne une méthode simple :

1. construire ;
2. lire le nom du symbole manquant ;
3. chercher quelle bibliothèque fournit ce symbole ;
4. ajouter cette bibliothèque dans `links` ;
5. reconstruire.

Dans cet exercice, retirer la dépendance provoque donc volontairement une erreur d'édition de liens.

La sortie est simulée pour le rendu : le message exact dépend du compilateur et de la plateforme.
