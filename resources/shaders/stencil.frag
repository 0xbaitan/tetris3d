#version 330 core

in vec3 normals;
in vec2 tex_coords;

out vec4 fragment_color;

void main() { 
    fragment_color = vec4(0.0f, 0.0f, 1.0f ,1.0f);
 }