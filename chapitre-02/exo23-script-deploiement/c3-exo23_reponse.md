# Exercice 23 — Script des quatre étapes

**Étudiant :** Pee Steve Anthony  
**Matricule :** 25P812  
**Sprint :** 2  
**Chapitre :** 3 — Construction et déploiement avec Jenga


## Énoncé

Écrire un script qui enchaîne construire, empaqueter, signer et installer, en s'arrêtant à la première erreur.

## Script Windows `deploy.bat`

```bat
@echo off
setlocal

echo [1/4] Construction...
jenga build
if errorlevel 1 (
    echo ECHEC a l'etape 1 : construction
    exit /b 1
)

echo [2/4] Empaquetage...
jenga package
if errorlevel 1 (
    echo ECHEC a l'etape 2 : empaquetage
    exit /b 1
)

echo [3/4] Signature...
jenga sign
if errorlevel 1 (
    echo ECHEC a l'etape 3 : signature
    exit /b 1
)

echo [4/4] Installation...
jenga deploy
if errorlevel 1 (
    echo ECHEC a l'etape 4 : installation
    exit /b 1
)

echo Deploiement termine avec succes.
exit /b 0
```

## Exemple de sortie simulée

```text
[1/4] Construction...
Build succeeded.

[2/4] Empaquetage...
Package created.

[3/4] Signature...
Signature applied.

[4/4] Installation...
Installation succeeded.

Deploiement termine avec succes.
```

## Test avec une erreur

```text
[1/4] Construction...
Build failed.
ECHEC a l'etape 1 : construction
```

Le script s'arrête immédiatement.

## Test sur une autre machine

Le camarade doit disposer de son propre environnement Jenga, de sa chaîne de compilation, de ses outils Android et de son appareil. Le but est de corriger les éléments dépendants de la machine plutôt que de coder des chemins personnels en dur.

Le script est adapté à Windows. Une version shell serait nécessaire sur Linux/macOS.
