#version 330 core

in vec2 _tex_coord;

uniform sampler2D sun_texture;

void main (void)
{   
	vec4 color = texture2D(sun_texture, _tex_coord.st);
	gl_FragColor = vec4(color.r, color.g, color.b, color.r);
}