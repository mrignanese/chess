# Chess
Simple C++ application to play chess. Chessboard and pieces are rendered using OpenGL graphic API.

## Features

## Requirements
This project uses OpenGL and the following libraries are needed:
- [GLFW](https://www.glfw.org/): C library for OpenGL used to create the window, receiving inputs and events
- [GLEW](https://glew.sourceforge.net/): C/C++ extension library to access OpenGL functionalities to render chessboard and pieces
- [GLM](https://glm.g-truc.net/0.9.9/api/index.html): mathematics library
- [ImGui](https://github.com/ocornut/imgui):

### Installing dependencies on Ubuntu
```bash
sudo apt update
sudo apt install libglfw3-dev libglew-dev libglm-dev
```

## Build and run
To build the source code a Makefile is used:
```bash
make # make clean to delete all build files
./application
```