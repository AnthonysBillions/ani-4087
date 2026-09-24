# Exercice 26 — Déploiement avec plusieurs appareils

**Étudiant :** Pee Steve Anthony  
**Matricule :** 25P812  
**Sprint :** 2  
**Chapitre :** 3 — Construction et déploiement avec Jenga


## Énoncé

Avec au moins deux appareils, lancer un déploiement sans `--target`, constater le message, puis installer successivement sur chacun en changeant uniquement le numéro de série.

## Déploiement sans cible

Commande :

```text
jenga deploy
```

### Sortie simulée

```text
error: multiple devices available
Please specify a target device with --target.
```

Le problème vient du fait que Jenga ne peut pas choisir automatiquement l'appareil lorsque plusieurs cibles sont disponibles.

## Appareil 1

```text
jenga deploy --target emulator-5554
```

### Sortie

```text
Target: emulator-5554
Installing MaSalle.apk
Installation succeeded.
```

## Appareil 2

```text
jenga deploy --target R58N123456A
```

### Sortie

```text
Target: R58N123456A
Installing MaSalle.apk
Installation succeeded.
```

## Vérification

Il faut vérifier physiquement l'écran de chaque appareil.

Les photographies demandées par l'exercice doivent être ajoutées au rendu réel. Elles ne peuvent pas être simulées honnêtement : une photo doit prouver l'installation sur les deux appareils.

Les messages ci-dessus sont des exemples de rendu.
