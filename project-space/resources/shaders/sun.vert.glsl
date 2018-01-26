#version 330 core

out vec2 _tex_coord;

layout(location = 0) in vec4 position;
layout(location = 2) in vec2 tex_coord;

uniform mat4 model_matrix;
uniform mat4 projection_matrix;
uniform mat4 view_matrix;

void main() {
    gl_Position = projection_matrix * view_matrix * model_matrix * position; 
	_tex_coord = tex_coord;
}
