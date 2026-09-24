# Exercice 19 — Crash volontaire et trace

**Étudiant :** Pee Steve Anthony  
**Matricule :** 25P812  
**Sprint :** 2  
**Chapitre :** 3 — Construction et déploiement avec Jenga


## Énoncé

Faire planter volontairement le programme sur l'appareil, retrouver la trace dans le journal et expliquer ce qu'elle apprend.

## Exemple

```cpp
int main()
{
    int* p = nullptr;
    *p = 42;
    return 0;
}
```

## Sortie de rendu simulée

```text
Fatal signal 11 (SIGSEGV), code 1 (SEGV_MAPERR)
backtrace:
  #00 pc ... main
  #01 pc ... libc.so
```

## Ce que la trace apprend

Elle permet notamment d'identifier :

- qu'un signal fatal a provoqué l'arrêt ;
- le type général du signal ;
- une partie de la pile d'appels ;
- le point où le programme s'est arrêté si les symboles sont disponibles.

## Ce qu'elle n'apprend pas automatiquement

Une trace brute ne donne pas nécessairement la cause logique complète du bug. Elle ne dit pas à elle seule pourquoi le pointeur est nul ni quelle décision dans le programme a conduit à cette situation.

La sortie est simulée ; la trace exacte dépend de l'appareil, de l'architecture, des symboles et de la version Android.
