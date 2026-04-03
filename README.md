# 🐍 Projet Snake Qt

Un jeu Snake développé en C++ avec le framework Qt.

## 🎮 Modes de jeu

- **Mode Niveaux** : Parcours plusieurs niveaux avec des murs et des obstacles.
  Mange 3 fruits pour passer au niveau suivant !
- **Mode Infini** : Terrain sans murs, le serpent peut traverser les bords
  et réapparaître de l'autre côté. Mange indéfiniment !

## 🛠️ Technologies utilisées

- C++
- Qt 5.15
- FMOD (gestion du son)
- Code::Blocks (IDE)

## 🚀 Comment lancer le projet

1. Ouvre le fichier `.cbp` avec **Code::Blocks**
2. Compile avec **Build → Build**
3. Lance avec **Build → Run**

## 📁 Structure du projet
├── main.cpp
├── menu.cpp / menu.hpp
├── jeu.cpp / jeu.hpp
├── snakewindow.cpp / snakewindow.hpp
├── Sound/
└── README.md