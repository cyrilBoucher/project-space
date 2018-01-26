#version 330 core

in vec2 _tex_coord;

uniform sampler2D first_pass_texture;

void main (void)
{   
	gl_FragColor = texture2D(first_pass_texture, _tex_coord.st);
}