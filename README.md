# Snake — Application desktop C++/Qt

Jeu Snake développé en C++ avec le framework Qt 5, intégrant la bibliothèque 
audio FMOD. Architecture orientée objet multi-fenêtres avec gestion d'événements 
clavier personnalisés.

## Fonctionnalités

- Architecture OO sur 4 classes (`Jeu`, `SnakeWindow`, `Menu`, `SnakeButton`)
- Deux modes de jeu :
  - **Mode Niveaux** : terrain avec murs, 3 fruits pour passer au niveau suivant
  - **Mode Infini** : terrain sans murs, traversée des bords (téléportation)
- Système de niveaux avec timer décompte
- Détection de collisions (murs, corps du serpent)
- Gestion audio temps réel via FMOD (effets sonores sur événements)
- Classe `SnakeButton` héritant de `QPushButton` avec événements clavier personnalisés

## Technologies

- **Langage** : C++
- **Framework GUI** : Qt 5.15 (QWidget, QFrame, signals/slots)
- **Audio** : FMOD
- **IDE** : Code::Blocks

## Concepts C++ démontrés

- Héritage et polymorphisme (QWidget, QFrame, QPushButton)
- Surcharge d'opérateurs (`==`, `!=`, `=` sur classe `Position` et `Jeu`)
- Constructeurs, constructeur de copie, destructeur
- Gestion de bibliothèques externes (FMOD)
- Énumérations typées (`Case`, `Direction`)

## Compilation

Projet Code::Blocks (`snake_win1.cbp` pour Windows, `snake_linux.cbp` pour Linux). 
Nécessite Qt 5 et FMOD installés sur le système.

## Structure du projet

- `main.cpp` — point d'entrée
- `menu.cpp / menu.hpp` — menu de sélection des modes
- `jeu.cpp / jeu.hpp` — logique du jeu, gestion du serpent et des fruits
- `snakewindow.cpp / snakewindow.hpp` — fenêtre principale et rendu
- `snakebutton.cpp / snakebutton.hpp` — bouton personnalisé avec gestion clavier

## Auteur

PHAM Duc Thang — Élève ingénieur INSA Centre Val de Loire
