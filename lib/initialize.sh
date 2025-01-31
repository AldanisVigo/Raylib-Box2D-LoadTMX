#!/bin/bash

git clone https://github.com/terroo/loadtmx.git
cd loadtmx
git clone https://github.com/leethomason/tinyxml2.git
cd tinyxml2
cmake -S .
make
cd ..
cd ..
git clone https://github.com/erincatto/box2d.git
cd box2d && cmake -S . && make
cd ..
git clone https://github.com/raysan5/raylib.git
cd raylib && cmake -S . && make
echo "All required libraries have been installed and compiled"

