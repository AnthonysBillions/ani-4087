# Exercice 22 — APK et AAB

**Étudiant :** Pee Steve Anthony  
**Matricule :** 25P812  
**Sprint :** 2  
**Chapitre :** 3 — Construction et déploiement avec Jenga


## Énoncé

Produire un APK et un AAB du même programme, comparer leurs tailles et contenus, puis expliquer pourquoi une boutique peut préférer l'AAB.

## Commandes de rendu

```text
jenga package --format apk
jenga package --format aab
```

## Rapport simulé

| Format | Taille |
|---|---:|
| APK | 2,31 MB |
| AAB | 2,08 MB |

## APK

Un APK est directement installable sur l'appareil. Il contient les éléments nécessaires au paquet installé.

## AAB

Un Android App Bundle est destiné à la distribution. Il contient les informations et ressources permettant de produire des APK adaptés aux appareils ciblés.

## Comparaison

Le format AAB peut donc contenir les ressources et variantes nécessaires à la génération de paquets spécifiques. Une boutique peut ainsi sélectionner les éléments utiles à l'appareil du téléchargement au lieu de distribuer systématiquement un paquet contenant toutes les variantes.

La taille exacte et la liste exacte des fichiers dépendent du projet. Les chiffres sont simulés pour le rendu.
