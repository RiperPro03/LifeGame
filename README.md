# Life Game

## Introduction

Le **Jeu de la Vie** est un automate cellulaire inventé par le mathématicien **John Horton Conway** en 1970. Il s'agit d'un jeu à zéro joueur où l'évolution d'une grille de cellules est déterminée par des règles simples. Chaque cellule peut être vivante ou morte, et son état à la génération suivante dépend de ses voisins.

### Règles du Jeu
1. Une cellule vivante avec moins de 2 voisins vivants meurt (sous-population).
2. Une cellule vivante avec 2 ou 3 voisins vivants reste vivante (survie).
3. Une cellule vivante avec plus de 3 voisins vivants meurt (surpopulation).
4. Une cellule morte avec exactement 3 voisins vivants devient vivante (reproduction).

Ce projet implémente le Jeu de la Vie avec des fonctionnalités supplémentaires, comme des **cellules obstacles** qui ne changent jamais d'état et un mode **grille torique** où les bords sont connectés.

---

## Comment jouer

### Prérequis
- Assurez-vous d'avoir un compilateur C++ compatible avec les bibliothèques utilisées (comme SFML pour l'affichage graphique).
- Placez un fichier texte contenant la grille initiale dans le répertoire du programme.

### Instructions
1. **Lancer le programme** :
    - Exécutez le fichier binaire généré après compilation.

2. **Configurer les paramètres et générateur de grille** :
    - Vous serez invité à configurer les paramètres (taille des cellules, délai entre générations, taille de la grille à générer).
    - Si vous choisissez de ne pas configurer, des valeurs par défaut seront utilisées.

3. **Charger une grille** :
    - Entrez le chemin du fichier contenant la grille initiale.
    - Le fichier doit contenir uniquement :
        - `1` pour une cellule vivante.
        - `0` pour une cellule morte.
        - `2` pour une cellule obstacle morte.
        - `3` pour une cellule obstacle vivante.

4. **Choisir le mode torique** :
    - Activez ou désactivez le mode torique (les bords de la grille sont connectés).

5. **Choisir le mode d'affichage** :
    - Choisissez entre :
        - **Mode console** : Affiche les générations dans la console.
        - **Mode graphique** : Affiche les générations dans une fenêtre graphique (SFML).

6. **Observer l'évolution** :
    - Le jeu s'exécute jusqu'à ce qu'il atteigne un état stable ou que toutes les cellules soient mortes.

7. **Quitter le programme** :
    - Vous pouvez quitter à tout moment en suivant les instructions affichées.

---

## Fonctionnalités principales

- Chargement de grilles personnalisées depuis un fichier texte.
- Mode torique permettant une connectivité des bords.
- Cellules obstacles qui ne changent jamais d'état.
- Affichage en mode console ou graphique (SFML).
- Sauvegarde automatique des générations dans des fichiers texte.

---

## Exemple de fichier grille

Voici un exemple de fichier texte pour initialiser une grille :
```plaintext
5 10
0 0 1 0 0 0 0 0 0 0
0 1 1 1 0 0 0 0 0 0
0 0 1 0 0 2 3 0 0 0
1 1 1 1 1 1 1 1 1 1
0 0 0 3 2 0 0 0 1 1
```
- `5` et `10` : Dimensions de la grille (5 lignes, 10 colonnes).
- `1` : Cellule vivante.
- `0` : Cellule morte.
- `2` : Cellule obstacle morte.
- `3` : Cellule obstacle vivante.

---

## Auteurs
- [Christopher Asin](https://www.github.com/RiperPro03)


- [Florian RENARD](https://github.com/foxTBT)

---

## Diagrammes

Voici les diagrammes qui décrivent l'architecture et le fonctionnement du projet :

1. **Diagramme de classes**  
   ![Diagramme de classes](https://i.imgur.com/hEnywei.png)

2. **Diagramme de séquence**  
   ![Diagramme de séquence](https://i.imgur.com/vcZia2Q.png)

3. **Diagramme d'activité**  
   ![Diagramme d'activité](https://i.imgur.com/LgByHiM.png)

4. **Diagramme de cas d'utilisation**  
   ![Diagramme de cas d'utilisation](https://i.imgur.com/wst2wed.png)

