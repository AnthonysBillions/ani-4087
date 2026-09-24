# Exercice 9 — Motif de fichier et dossier inexistant

**Étudiant :** Pee Steve Anthony  
**Matricule :** 25P812  
**Sprint :** 2  
**Chapitre :** 3 — Construction et déploiement avec Jenga


## Énoncé

Ajouter à `files` un motif qui ne correspond à aucun fichier et à `includedirs` un dossier inexistant. Comparer `jenga info` et `jenga build`.

## Extrait

```python
files([
    "src/**.cpp",
    "src/fichier_qui_nexiste_pas.cpp"
])

includedirs([
    "include",
    "include/dossier_inexistant"
])
```

## `jenga info`

### Sortie simulée

```text
Project: MaSalle

Sources:
  src/main.cpp

Include directories:
  include
  include/dossier_inexistant

No fatal error.
```

## `jenga build`

### Sortie simulée

```text
[1/1] Compiling src/main.cpp
warning: include directory does not exist:
        include/dossier_inexistant

Build succeeded.
```

Selon la version de Jenga et du compilateur, un motif vide peut être signalé différemment, ou ne produire aucun fichier supplémentaire.

## Comparaison

Pour cet exercice, `jenga build` est la commande qui permet de voir le comportement concret pendant la construction. `jenga info` décrit davantage la configuration interprétée.

Le choix demandé par l'exercice est donc : **la sortie de `jenga build` aurait fait gagner du temps pour diagnostiquer le problème réellement rencontré pendant la construction.**

Les messages sont simulés : les avertissements exacts peuvent varier selon la version de Jenga.
