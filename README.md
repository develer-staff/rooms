Rooms SDK
=========
Manages point-and-click adventure games.

The SDK is composed of two main parts:
- The Engine static library with a frontend specialized for de device that runs the game
- A graphic editor to create adventures

## Build instructions
To build Rooms Engine you need qmake (at least version 2.01) and a C++ compiler.

Rooms Engine has an optional builtin Python scripting engine.  
To build Rooms Engine with Python support you have to pass to the qmake 
command line the following option: `PYTHON_VERSION=x.x` where x.x is the 
Python library version.

### Build Example: 
If you are on a unix machine with Python 2.7 and the Qt5 libraries installed 
and you want to run the game with the qt5-frontend 
you can compile Rooms Engine with the following commands:
```
cd path/to/rooms/engine
qmake PYTHON_VERSION=2.7 && make

cd qt5-frontend
qmake PYTHON_VERSION=2.7 && make
```
Now you have an executable named engine.exe which can run the game
