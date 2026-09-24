# Exercice 27 — État `unauthorized`

**Étudiant :** Pee Steve Anthony  
**Matricule :** 25P812  
**Sprint :** 2  
**Chapitre :** 3 — Construction et déploiement avec Jenga


## Énoncé

Provoquer l'état `unauthorized`, comparer la réponse de Jenga et celle de `adb devices`, puis accepter l'autorisation et recommencer.

## 1. Appareil non autorisé

### Jenga

Commande :

```text
jenga --list-devices
```

### Sortie simulée

```text
No device available.
```

### ADB

Commande :

```text
adb devices
```

### Sortie simulée

```text
List of devices attached
R58N123456A    unauthorized
```

Les deux sorties ne donnent donc pas le même niveau de détail.

## 2. Après acceptation de l'autorisation

### Jenga

```text
jenga --list-devices
```

Sortie simulée :

```text
R58N123456A
```

### ADB

```text
adb devices
```

Sortie simulée :

```text
List of devices attached
R58N123456A    device
```

## Explication

Le message de Jenga est trompeur parce que l'appareil est bien connecté physiquement, mais il n'est pas encore autorisé pour le débogage USB.

`adb devices` permet de distinguer explicitement :

```text
device
unauthorized
```

Une formulation plus précise serait :

```text
Device detected but not authorized for USB debugging.
Please accept the authorization dialog on the device.
```

Le cours souligne justement que, dans ce cas, la boîte de dialogue d'autorisation peut être visible sur le casque lui-même.

Les sorties sont simulées ; le numéro de série et le texte exact dépendent de l'appareil.
