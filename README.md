# SuperBomberTek

This project is a 2nd end year project done at Epitech in C++ language.  
It consists in creating a Bomberman-like in a group of 4 to 6 people.  

**Group members:**  
  - [@Exylar](https://github.com/Exylar)
  - [@HeyShafty](https://github.com/HeyShafty)
  - [@Kilio22](https://github.com/Kilio22)
  - [@SuperZikoure](https://github.com/SuperZikoure)
  - [@zoraneus](https://github.com/zoraneus)

For this project, we needed to use **Irrlicht 3D library** for the display side and the **SFML library** for sounds & musics side.  
**All assets are unique**, except musics which have been remixed by us.

For this project, we've implemented an **ECS architecture**.  
I really loved coding this project because first I was in a group in which everybody were motivated by the project and secondly, implementing the architecture cited above was really interesting, I've learned a lot about templates, game programming design patterns, games architecture etc...

### Here's an extract of the subject :

The game you must implement is a Bomberman-like game.  
Bomberman is one of the most famous video games of all time.  

With over 70 franchises, ranging from the first version on MSX, ZX Spectrum and Sharp MZ-700 in 1983 to the lastest versions on modern consoles, over 10 million units have been sold.  

Our gameplay reference is Neo Bomberman, released on the Neo Geo and MVS systems in 1997.  

**Here's the required features :**  
  - Local multi-player with the possibility the play with a friend + AI’s controlled bots.  
  - A main game menu (to start a new game or load an existing one).  
  - Your game must feature 3D graphics but a 2D gameplay.  
  - Your game must feature procedurally generated maps.  
  - Save/Load a game  
  - Animation and sounds to give life to the game (especially during various interactions)  
  - Think about bomb explosion, player walking, background music, . . .  
  - Some Power-ups  
  - Bomb Up  
  - Speed Up  
  - Fire Up  
  - Wall Pass  

The goal of this project is not only to code a video game, but it’s to code a full finished video game. This
means that the efforts you make to polish your game will count as much as the technical aspect.  

Do your best to avoid clunky animations or graphical glitches, manage your camera in a way that the “outside” of the game is never visible, pay attention to game design, level design and sound design, add variations in ennemies and environnements, etc.

## How to compile & run it ?

- **Linux:**  
Make sure that **cmake**, **irrlicht library** and **SFML library** are installed on your pc, if not, please install them using your package manager, then run the following command at the root of the repository:  
  ```sh
  mkdir build && cd build && cmake ../ && make && ./bomberman
  ```

- **Windows**:  
Make sure that **cmake** are installed on your PC and the ``cmake`` command can be run in powershell. If not please install cmake, then run the following commands at the root of the repository using powershell:  
  ```sh
  $> mkdir build
  $> cd build
  $> cmake ../
  $> cmake --build .
  ```
  The executable can be found in DEBUG/bomberman.exe.  
  **You'll need to move the executable in the ``bin`` directory to run it**.
