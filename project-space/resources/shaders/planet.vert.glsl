#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 normal;
layout(location = 2) in vec2 tex_coord;

uniform mat4 model_matrix;
uniform mat4 projection_matrix;
uniform mat4 view_matrix;

void main() {
    gl_Position = projection_matrix * view_matrix * model_matrix * position; 
}
