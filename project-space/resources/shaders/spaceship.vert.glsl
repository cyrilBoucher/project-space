#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;

out vec4 _position;
out vec3 _normal;

uniform mat4 model_matrix;
uniform mat4 projection_matrix;
uniform mat4 view_matrix;
uniform mat3 normal_matrix;

void main() {
    gl_Position = projection_matrix * view_matrix * model_matrix * position; 
	_position = position;
	_normal = normal;
}
