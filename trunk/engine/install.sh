#!/bin/bash
g++ -c src/*.cpp
mv *.o build/
ar rcs librooms.a build/*.o

