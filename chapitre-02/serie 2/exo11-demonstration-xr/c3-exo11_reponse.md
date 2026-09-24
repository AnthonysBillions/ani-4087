# Exercice 11 — Fichier de projet de la démonstration XR

**Étudiant :** Pee Steve Anthony  
**Matricule :** 25P812  
**Sprint :** 2  
**Chapitre :** 3 — Construction et déploiement avec Jenga


## Énoncé

Lire le fichier de projet de la démonstration XR du moteur, y compris les commentaires, puis expliquer ce qu'il construit, ses dépendances, les différences entre systèmes et les trois pièges documentés.

## Ce qu'il construit

D'après le chapitre, la démonstration XR correspond à une application qui doit fonctionner avec les modules du moteur nécessaires à la fenêtre, au rendu graphique et à la réalité virtuelle.

Les modules cités dans le cours sont notamment :

- `NKCore` pour les types de base ;
- `NKMath` pour les vecteurs et quaternions ;
- `NKWindow` pour la fenêtre ;
- `NKRHI` pour l'accès au rendu graphique ;
- `NKXR` pour la réalité virtuelle.

Le projet doit être construit dans un `workspace` et utiliser un type d'application adapté à une application avec fenêtre.

## Dépendances

Le chapitre rappelle que `links` sert à lier des bibliothèques existantes alors que `dependson` sert à imposer la construction préalable d'un autre projet.

L'ordre des bibliothèques est également important : la liste doit aller du plus dépendant vers le plus fondamental, avec `NKPlatform` à la fin selon la règle donnée dans le cours.

## Ce qui change selon le système

Le fichier utilise des filtres.

Windows :

```python
with filter("system:Windows"):
    links(["user32", "gdi32", "opengl32", "dinput8", "dxguid", "winmm"])
```

Linux :

```python
with filter("system:Linux"):
    links(["pthread", "X11", "Xext", "GL"])
```

Le même projet peut donc rester commun tandis que les bibliothèques spécifiques au système changent.

## Trois pièges documentés

### 1. Oublier le workspace

Sans le bloc `workspace`, Jenga peut répondre :

```text
No .jenga workspace file found
```

**Conséquence :** le projet ne peut pas être construit comme workspace valide.

### 2. Oublier une dépendance transitive

Le cours cite `NKGLSlang` et `NKSPIRVCross` comme dépendances nécessaires à `NKSL`, mais qui peuvent devoir être nommées explicitement par l'exécutable.

**Conséquence :** l'édition de liens échoue avec des symboles manquants.

### 3. Mauvais `define` dans un en-tête

Un module peut avoir été compilé avec un `define` alors que l'utilisateur de l'en-tête ne l'a pas.

**Conséquence :** le programme compile contre une déclaration différente et le problème peut apparaître ensuite au lien.

## Conclusion

Le fichier de démonstration montre que le projet n'est pas seulement une liste de fichiers : il décrit aussi les dépendances, les bibliothèques, les plateformes et les conditions de construction.

Cette réponse est fondée sur les éléments du chapitre fourni. Le fichier exact de la démonstration XR n'étant pas joint, les noms de fichiers propres à cette démonstration ne sont pas inventés.
