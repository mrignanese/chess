# Renderer Module
This folder contains graphics-related classes used to render the chessboard and the pieces. All the classes contained in the `renderer` folder are used to abstract OpenGL functions call. Every OpenGL function call is wrapped around `GLCall` macro, defined in `GLError.h`. The macro is used to facilitate debugging.

## Vertex Buffer
Class abstraction of OpenGL Vertex Buffer Objects (VBOs). \
**Purpose**: used to store raw vertex attributes (vertex positions, texture coordinates) in memory. It is the buffer that holds the geometry.

## Index Buffer
Class abstraction of OpenGL Index Buffer Objects (IBO). \
**Purpose**: used to store indices that are used to access elements of a VBO, to reuse vertex data and reduce duplication in the vertex buffer. The draw call is done using `glDrawElements` to reduce memory.

## Vertex Buffer Layout
Manages the description of vertex attributes in a VBO. For this specific case the vertex buffer contains:
- first attribute: 2 floats for the vertex positions (x and y of a single vertex of a square)
- second attribute: 2 floats for the texture coordinates (x and y of the texture)

**Purpose**: describes how many components each vertex attribute has (e.g., 2 floats for position, 2 floats for texture coords), and the stride/offset between them.

## Vertex Array
Class abstraction of OpenGL Vertex Array Object (VAO). \
**Purpose**: stores the configuration of vertex attributes: which VBOs are bound to which attribute slots and how they are formatted. \
VAOs capture the attribute state so the GPU knows how to interpret vertex data during rendering.

## Shader
Handles compilation, linking, and use of an OpenGL shader program. \
**Purpose**: shader files (in `resources/shaders/` folder) are parsed using `Shader::ParseShader` method. Vertex shader and fragment shader are compiled (by `Shader::CompileShader` method) and linked in one single program by the `Shader::CreateShader` method. `Shader class` also provides uniform setters. \
Shaders express how vertices are transformed and how pixels (fragments) get colored.

## Texture
Class abstraction for OpenGL texture object. \
**Purpose**: loads image data (PNG, JPG, etc.) and uploads it to the GPU, then sets filtering and wrapping modes. This class is used to renderer pieces. PNG files are stored in `resources/textures/pieces` 
