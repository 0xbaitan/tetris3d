#version 330 core

layout (location=0) in vec3 pos;
layout (location=1) in vec3 in_normals;
layout (location=2) in vec2 in_tex_coords;

out vec3 normals;
out vec2 tex_coords;



uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main() {
    gl_Position = projection * view * model * vec4(pos, 1.0f);
    normals = in_normals;
    tex_coords = in_tex_coords;
    
}