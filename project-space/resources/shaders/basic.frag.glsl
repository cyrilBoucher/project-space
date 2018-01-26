#version 330 core

struct material {
	vec4 kd;
	vec4 ka;
	vec4 ks;
	float ns;
};

struct light {
	vec3 position;
	vec4 color;
	vec3 direction;
	int type;
};

uniform material mat;

uniform light scene_light;

void main (void)
{   
	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);//mat.kd;
}