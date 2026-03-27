# BeeBusy

BeeBusy is an arcade style, high score game about running your garden while also keeping the local bee population healthy. You plant flowers in empty plantpots which the bees will come and use for pollen, removing them from your garden. Your aim is to keep your garden alive to keep the bees working and keep your garden healthy. If you run out of plants, you lose.

## Development

BeeBusy was built to be a very short project where I could work on a game outside of a game engine like Unity. I also didn't want to have to make all of the graphics programming myself as this is something I have tried and failed multiple times with OpenGL. This time I decided to use `raylib` which is a minimal framework for working on games that handles all of the OpenGL functions for you as well as much more. Raylib has hooks for many languages but I decided to work in C++ for this project as my skills were getting a bit rusty and unlike C, C++ has class functionality which is perfect for game dev.

One of the first troubles I had was setting up raylib with Visual Studio Code and a compiler. On my main PC I had the `mingw` compiler and `CMake` set up and running already but when I wanted to move across to my laptop I didn't have these tools ready and had to set them up again which was a surprisingly harder task than expected. After trying 3 installations of `mingw` I finally got my game to compile on my laptop with `CMake` which was a huge relief.

After the initial setup I was able to slowly flesh out the game from the inital window example available on the raylib website. I had to think about how I wanted to structure the project and I decided to dedicate almost everything into it's own class. I think I may have went a bit overkill but I needed to practice working on and organising more complex systems.

## What I would do differently

## Additional notes

## Credits