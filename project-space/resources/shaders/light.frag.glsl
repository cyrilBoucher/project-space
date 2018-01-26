#version 330 core

uniform int myrenderStyle;

uniform int draw_silhouette;

in vec4 _pos;
in vec3 _normal;
in vec2 _tex_coord;

//Light attributes
uniform vec4 light_position;
uniform vec4 light_color;
uniform vec3 light_direction;
uniform int light_type;

//Material attributes
struct material {
	vec4 kd;
	vec4 ka;
	vec4 ks;
	float ns;
};
uniform material mat;
uniform vec4 ks;// = vec4(1,1,1,1); 
uniform	vec4 kd; //= obj_color;
uniform	vec4 ka; //= vec4(0,0,0,0);
uniform	float Ns;//=40;

// Textures
uniform sampler2D tex;

//Matrices for viewing
uniform mat3 mynormal_matrix;
uniform mat4 myview_matrix;

// fragment attributes
vec3 normal, pos;

// eye to fragment vector
vec3 eyepos = vec3(0,0,0);

// color and lights
vec3 light_direction_transformed;

vec4 define_obj_color(int renderstyle);

vec4 compute_silhouette(vec4 obj_color)
{
	vec4 color = obj_color;
	vec3 view_direction = normalize(pos - eyepos);

	if (abs(dot(normal, view_direction)) < 0.1)
	{
		color *= 0.4;
	}
	return color;
}

vec4 computeColor(vec3 normal, vec3 light, vec3 mypos_to_eye, vec4 color) {
	vec4 diffuse_color = color * kd * max(0,dot(normal, light));
	vec4 specular_color = color * ks * pow(dot(mypos_to_eye, normalize(reflect(light, normal))), Ns);
	
	return diffuse_color ;//+ specular_color;
}

vec4 compute_fragment_color()
{
	vec4 light_position_exact_tmp = myview_matrix * light_position;
	vec3 light_position_exact = light_position.xyz / light_position.w;
	vec3 pos_to_eye = normalize(eyepos - pos);

	if ( dot(normal, pos_to_eye) < 0)
		normal = -normal;

	vec3 light_to_pos = normalize(pos - light_position_exact);

	vec4 color_;

	switch(light_type)
	{
		
		case 1: // Point light
			color_ = computeColor(normal, -light_to_pos, pos_to_eye, light_color);
			break;

		case 2: // Directional light
			color_ = computeColor(normal, light_position_exact, pos_to_eye, light_color);
			break;

		case 3: // Spot light
			color_ = computeColor(normal, -light_to_pos, pos_to_eye, light_color * dot(-light_to_pos, light_position_exact));
			break;
	}

	return color_ + ka;
} 

void main (void)
{   
	

	// init variables
	//light_direction_transformed = normalize(mynormal_matrix * light_direction);
	normal = normalize(mynormal_matrix * _normal);
	vec4 pos_4 = myview_matrix * _pos;
	pos = pos_4.xyz / pos_4.w;

	// rendering options
	//vec4 obj_color = define_obj_color(myrenderStyle);

	// compute color
	gl_FragColor = compute_fragment_color();

	//gl_FragColor = texture2D(tex, _tex_coord.st);

	//if asked, compute silhouette
	if (draw_silhouette == 1)
	{
		gl_FragColor = compute_silhouette(gl_FragColor);
	}
}

vec4 define_obj_color(int renderstyle)
{
	vec4 color = vec4(0,0,0,0);
	switch(renderstyle)
	{
		case 0:
			color = vec4(1,0,0,0);
			break;
		case 1:
			color = vec4(135.0/255,184.0/255, 41.0/255,0);
			break;

		case 2:
			color = vec4(0,1,0,0);
			break;
	}
	return color;
}