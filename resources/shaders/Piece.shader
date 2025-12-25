#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 textureCoord;

// output data from the vertex shader to the fragment
out vec2 v_TextureCoord;

uniform mat4 u_MVP;

void main() {
    gl_Position = u_MVP * position;
    v_TextureCoord = textureCoord;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TextureCoord; // taken from vertex shader

uniform sampler2D u_Texture;

void main() {
    vec4 textureColor = texture(u_Texture, v_TextureCoord);
    color = textureColor;
}
