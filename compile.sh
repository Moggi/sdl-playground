#!/bin/bash
clang++ -o $1 game.cpp gameobject.cpp player.cpp -std=c++11 -L/usr/local/lib -I/usr/local/include -lSDL2 -lSDL2_image -lSDL2_ttf -framework OpenGL "./$1.cpp" && ./$1
