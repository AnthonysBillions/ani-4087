# Exercice 15 — Clé de signature

**Étudiant :** Pee Steve Anthony  
**Matricule :** 25P812  
**Sprint :** 2  
**Chapitre :** 3 — Construction et déploiement avec Jenga


## Énoncé

Fabriquer une clé de signature, noter son emplacement et son mot de passe hors du dépôt. Rendre la commande sans le mot de passe.

## Commande de rendu simulée

Exemple avec un outil de génération de clé :

```text
keytool -genkeypair -v -keystore C:\Users\PeeSteve\.android\ma-salle-release.jks -alias ma-salle -keyalg RSA -keysize 2048 -validity 10000
```

Le mot de passe n'est volontairement pas écrit ici.

## Emplacement

Exemple :

```text
C:\Users\PeeSteve\.android\ma-salle-release.jks
```

Le fichier de clé ne doit pas être placé dans le dépôt Git.

## Mot de passe

Le mot de passe doit être conservé dans un gestionnaire de mots de passe ou dans un emplacement sécurisé séparé du dépôt.

## Pourquoi ?

Le cours insiste sur ce point : une clé de signature ne doit pas être perdue ni commitée dans le dépôt. Une mise à jour doit utiliser la même clé que la version précédente.

La commande et le chemin ci-dessus constituent un **exemple de rendu** ; le chemin réel doit correspondre à la clé créée pendant l'exercice.
