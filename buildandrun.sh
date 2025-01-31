#!/bin/bash
cd lib
./initialize.sh
cd ..
cd Classes
./initialize.sh
cd ..
mkdir build
cd build
cmake -S ../
make
./main
