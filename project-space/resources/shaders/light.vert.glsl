#version 330 core

out vec4 _pos;
out vec3 _normal;
out vec2 _tex_coord;

layout(location = 0) in vec4 vertex_modelspace;
layout(location = 1) in vec3 normal_modelspace;
layout(location = 2) in vec2 tex_coord_modelspace;

uniform mat4 myprojection_matrix;
uniform mat4 myview_matrix;

void main() {
    gl_Position = myprojection_matrix * myview_matrix * vertex_modelspace; 
	_pos = vertex_modelspace;
	_normal = normal_modelspace; 
	_tex_coord = tex_coord_modelspace;
}
