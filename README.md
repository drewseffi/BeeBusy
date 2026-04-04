# BeeBusy

BeeBusy is an arcade style, high score game about running your garden while also keeping the local bee population healthy. You plant flowers in empty plantpots which the bees will come and use for pollen, removing them from your garden. Your aim is to keep your garden alive to keep the bees working and keep your garden healthy. If you run out of plants, you lose.

## Development

BeeBusy was built to be a very short project where I could work on a game outside of a game engine like Unity. I also didn't want to have to make all of the graphics programming myself as this is something I have tried and failed multiple times with OpenGL. This time I decided to use `raylib` which is a minimal framework for working on games that handles all of the OpenGL functions for you as well as much more. Raylib has hooks for many languages but I decided to work in C++ for this project as my skills were getting a bit rusty and unlike C, C++ has class functionality which is perfect for game dev.

One of the first troubles I had was setting up raylib with Visual Studio Code and a compiler. On my main PC I had the `mingw` compiler and `CMake` set up and running already but when I wanted to move across to my laptop I didn't have these tools ready and had to set them up again which was a surprisingly harder task than expected. After trying 3 installations of `mingw` I finally got my game to compile on my laptop with `CMake` which was a huge relief.

After the initial setup I was able to slowly flesh out the game from the inital window example available on the raylib website. I had to think about how I wanted to structure the project and I decided to dedicate almost everything into it's own class. I think I may have went a bit overkill but I needed to practice working on and organising more complex systems.

## What I would do differently

I would look into game engine structure as I have far too much written in the `main.cpp` file and I would like to seperate that out. This is one of the main reasons that this has become a fairly messy project that even I get lost in while scrolling to find something.

I would've liked to have more UI elements in the game but I need to come up with a better solution for placement of entities and UI elements as there is a lot of "magic numbers" being used to align text or entities correctly. A full UI system would be hard but would be very rewarding to use. For example being able to chose how the origin of an element is aligned like "top-left, center, bottom-right" would be great as sometimes you know where the top-left needs to start and sometimes you know where the center needs to start.

Have less "game variables" that the entire games logic depends on as this leads to the code being rather scattered and isn't very modular.

## Afterthoughts

Even though this was a rather small game with an extremely limited scope, having to hand build all systems and functions from scratch (except for the raylib functions) was quite a burden and I would, in the future, potentially use a game engine even for a small task like this.

Although the idea of building a game in C++ with raylib was a bit challenging, I can see the enjoyment of having your own engine and getting to build the systems from the ground up. I may work on an "engine" as a hobby project but I would be building it to build an engine, not a game. I would also want to build tools around it such as a map editor and asset importer for example.

Raylib was an absolute wonder to work with as it took away all of the need to work with OpenGL (or any other graphics library) and allowed me to work on what was really important to this project rather than trying to render to the screen correctly.

## Credits

All sound effects were created using the website [jsfxr](https://sfxr.me/), with all music and art being made by myself.
