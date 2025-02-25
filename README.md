# 🕹️ cub3d

Bienvenue sur **cub3d** 🎮 !  
Ce projet consiste à créer un mini-jeu en 3D, inspiré des premiers jeux de type FPS, à l'aide de la librairie **mlx** de **42**. Le but est de générer une vue en 3D basée sur un fichier de configuration de type `.cub`, en affichant une carte et en permettant à l'utilisateur de se déplacer dedans.

## 🚀 Fonctionnalités

- Affichage en 3D d'une carte à partir d'un fichier `.cub`.
- Mouvement du joueur avec les touches directionnelles ⬆️ ⬇️ ⬅️ ➡️.
- Utilisation d'images pour les textures des murs 🖼️.
- Calculs de raycasting pour l'affichage 3D 🔫.
  
## 🔧 Prérequis

Avant de lancer le projet, assure-toi que tu as les éléments suivants installés sur ton système :

- [MinilibX](https://github.com/42Paris/minilibx-linux) 📚
- Clang pour la compilation 🖥️
- Make pour automatiser le build 🛠️

## ⚡ Installation

1. Clone le repository :
```bash
git clone https://github.com/ton-username/cub3d.git
cd cub3d
```

2. Compile le projet :
```bash
make
```

2. Lance le jeu avec :
```bash
./cub3d ./assets/map/toto.cub
```
