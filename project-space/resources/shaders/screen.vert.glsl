#version 330 core

out vec2 _tex_coord;

layout(location = 0) in vec4 position;
layout(location = 2) in vec2 tex_coord;

void main() {
    gl_Position = position; 
	_tex_coord = tex_coord;
}
