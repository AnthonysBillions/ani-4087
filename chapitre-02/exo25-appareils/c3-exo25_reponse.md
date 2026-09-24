# Exercice 25 — Liste détaillée des appareils

**Étudiant :** Pee Steve Anthony  
**Matricule :** 25P812  
**Sprint :** 2  
**Chapitre :** 3 — Construction et déploiement avec Jenga


## Énoncé

Lister les appareils avec `--list-devices`, puis avec `--detailed`, et relever l'ABI.

## Première commande

```text
jenga --list-devices
```

### Sortie simulée

```text
SERIAL
emulator-5554
R58N123456A
```

## Deuxième commande

```text
jenga --list-devices --detailed
```

### Sortie simulée

```text
SERIAL          STATE       MODEL             ABI
emulator-5554   device      Pixel_7_API_35    x86_64
R58N123456A     device      Android Phone     arm64-v8a
```

## Ce que la seconde commande apprend

La première donne essentiellement la liste des appareils détectés.

La seconde apporte des informations supplémentaires comme :

- l'état de l'appareil ;
- le modèle ;
- l'ABI.

## ABI

Dans cet exemple :

```text
emulator-5554 -> x86_64
R58N123456A   -> arm64-v8a
```

Si un seul appareil est disponible, il faut utiliser un second appareil ou un émulateur pour réaliser exactement l'objectif pédagogique de l'exercice.

Les sorties sont simulées.
