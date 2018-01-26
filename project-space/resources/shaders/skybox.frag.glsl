#version 330 core

in vec3 _tex_coord;

uniform samplerCube cube_texture;

void main (void)
{   
	gl_FragColor = texture(cube_texture, _tex_coord);
}