# Exercice 14 — Filtre Android

**Étudiant :** Pee Steve Anthony  
**Matricule :** 25P812  
**Sprint :** 2  
**Chapitre :** 3 — Construction et déploiement avec Jenga


## Énoncé

Ajouter au projet un filtre pour Android avec ses bibliothèques et ses définitions. Montrer que `jenga info` ne permet pas de prouver que le filtre est actif, puis indiquer comment le vérifier.

## Extrait du projet

```python
with filter("system:Android"):
    defines(["NK_PLATFORM_ANDROID"])

    links([
        "log",
        "android"
    ])
```

## Première constatation

Commande :

```text
jenga info
```

Le cours indique que sa sortie reste identique que la condition du filtre soit vraie ou fausse concernant les définitions. `jenga build --verbose` n'est pas non plus présenté comme une preuve suffisante dans cet exercice.

### Rendu simulé

```text
System: Windows

Project: MaSalle
Configuration: Debug
Sources:
  src/main.cpp
```

Puis après modification du système ciblé, la partie générale de `jenga info` peut rester identique.

## Vérification réelle

Pour vérifier l'activation du filtre pour Android, il faut demander explicitement une construction pour Android avec une commande qui accepte `--platform`, par exemple :

```text
jenga build --platform Android
```

Le résultat de la construction permet alors de vérifier que la configuration Android est effectivement sélectionnée.

## Conclusion

`jenga info` décrit le projet mais ne constitue pas la preuve demandée ici. La vérification doit être faite en ciblant explicitement Android lors de la construction.
