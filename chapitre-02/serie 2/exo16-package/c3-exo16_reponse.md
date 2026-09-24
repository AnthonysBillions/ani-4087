# Exercice 16 — Empaqueter et signer

**Étudiant :** Pee Steve Anthony  
**Matricule :** 25P812  
**Sprint :** 2  
**Chapitre :** 3 — Construction et déploiement avec Jenga


## Énoncé

Empaqueter le programme et le signer. Rendre la taille du paquet et la liste de son contenu.

## Commandes

```text
jenga package
jenga sign
```

## Sortie simulée

```text
Packaging MaSalle
Output: build/Android/MaSalle.apk

Package created successfully.
Size: 2.31 MB
```

Puis :

```text
Signing build/Android/MaSalle.apk
Signature applied successfully.
```

## Contenu simulé de l'APK

```text
AndroidManifest.xml
classes.dex
lib/
lib/arm64-v8a/
resources.arsc
assets/
META-INF/
META-INF/MANIFEST.MF
META-INF/...
```

Un APK est une archive. Il peut donc être inspecté avec un outil d'archive.

## Remarque

La taille et le contenu exacts dépendent du projet et de la chaîne Android utilisée. Les valeurs ci-dessus sont donc un **rendu simulé**, à remplacer par les résultats réels.
