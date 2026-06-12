# 🐍 Snake — Application desktop C++ / Qt

Jeu Snake développé en **C++ orienté objet** avec le framework **Qt 5**, dans le cadre d'un projet académique à l'INSA Centre-Val de Loire.

L'objectif pédagogique était de pratiquer la **programmation orientée objet**, la **séparation logique/interface**, et la **compilation multi-plateforme** (Linux, macOS, Windows).

---

## ✨ Fonctionnalités

- **Mode Niveaux** — progression à travers plusieurs niveaux avec murs et obstacles ; manger 3 fruits débloque le niveau suivant.
- **Mode Infini** — terrain sans bords, le serpent traverse l'écran et réapparaît de l'autre côté.
- **Menu interactif** avec boutons personnalisés (`SnakeButton`).
- **Effets sonores** via la bibliothèque FMOD.

---

## 🏗️ Architecture

Le code est organisé en **5 modules** avec séparation stricte logique métier / interface :

| Module | Rôle |
|---|---|
| `main.cpp` | Point d'entrée, initialisation Qt |
| `menu.cpp` / `menu.hpp` | Menu principal, sélection du mode de jeu |
| `jeu.cpp` / `jeu.hpp` | Logique du jeu (déplacement, collisions, score) |
| `snakewindow.cpp` / `snakewindow.hpp` | Fenêtre de jeu, rendu graphique |
| `snakebutton.cpp` / `snakebutton.hpp` | Composant bouton personnalisé |

---

## 🛠️ Technologies

- **C++** (C++11)
- **Qt 5.15** (widgets, signaux/slots)
- **FMOD** (audio)
- **Makefiles** dédiés Linux / macOS / Windows

---

## 🚀 Compilation & exécution

### Linux
```bash
make -f Makefile_linux
./snake
```

### macOS
```bash
make -f Makefile_macos
./snake
```

### Windows
Ouvrir `snake_win1.cbp` avec **Code::Blocks**, puis **Build → Run**.

### Prérequis
- Qt 5.15 installé (`qt5-default` sur Debian/Ubuntu, `brew install qt@5` sur macOS).
- Compilateur C++ supportant C++11 (g++, clang).
- FMOD (les DLL nécessaires sont gérées par les Makefiles).

---

## 📁 Structure du projet

```
.
├── main.cpp
├── menu.cpp / menu.hpp
├── jeu.cpp / jeu.hpp
├── snakewindow.cpp / snakewindow.hpp
├── snakebutton.cpp / snakebutton.hpp
├── data/              # ressources graphiques
├── sound/             # effets sonores
├── Makefile_linux
├── Makefile_macos
└── snake_win1.cbp     # projet Code::Blocks Windows
```

---

## 👤 Auteur

**PHAM Duc Thang** — élève-ingénieur INSA Centre-Val de Loire
[GitHub](https://github.com/Thangcomplex) · [LinkedIn](https://www.linkedin.com/in/DucThangPHAM)
