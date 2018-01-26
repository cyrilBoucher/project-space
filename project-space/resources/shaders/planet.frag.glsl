#version 330 core

struct material {
	vec4 kd;
	vec4 ka;
	vec4 ks;
	float ns;
};

uniform material mat;

void main (void)
{   
	gl_FragColor = mat.kd;
}