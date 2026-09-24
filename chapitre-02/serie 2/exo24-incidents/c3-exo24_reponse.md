# Exercice 24 — Journal des problèmes de déploiement

**Étudiant :** Pee Steve Anthony  
**Matricule :** 25P812  
**Sprint :** 2  
**Chapitre :** 3 — Construction et déploiement avec Jenga


## Énoncé

Tenir pendant le chapitre la liste des problèmes rencontrés avec le symptôme, ce que l'on croyait, la cause réelle et le temps perdu.

## Journal de rendu simulé

| Symptôme | Ce que je croyais | Ce que c'était réellement | Temps perdu |
|---|---|---|---:|
| `No .jenga workspace file found` | Jenga ne trouvait pas mon projet | Le bloc `workspace` manquait | 15 min |
| Bibliothèque introuvable au lien | Le compilateur était cassé | Une dépendance n'était pas dans `links` | 25 min |
| Définition ignorée | `jenga info` devait l'afficher | Les filtres ne sont pas affichés de cette manière | 20 min |
| Aucun appareil | Le téléphone n'était pas compatible | `adb devices` indiquait `unauthorized` | 30 min |
| Ressource introuvable sur Android | Le fichier avait disparu | `fopen` ne correspondait pas au stockage des ressources du paquet | 35 min |

## Analyse

Cette liste est utile parce qu'elle conserve non seulement la solution mais aussi l'erreur de raisonnement initiale.

Le chapitre insiste notamment sur le fait qu'il faut descendre d'un niveau lorsque l'outil de haut niveau masque la cause. Exemple : si Jenga ne voit pas l'appareil, la commande de diagnostic devient :

```text
adb devices
```

Le tableau est un **exemple de journal simulé**. Il doit être remplacé ou complété avec les problèmes réellement rencontrés.
