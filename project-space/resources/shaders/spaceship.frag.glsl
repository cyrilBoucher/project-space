#version 330 core

in vec4 _position;
in vec3 _normal;

struct material {
	vec4 kd;
	vec4 ka;
	vec4 ks;
	float ns;
};

struct light {
	vec4 position;
	vec4 color;
	vec3 direction;
	int type;
};

uniform mat4 view_matrix;
uniform mat3 normal_matrix;

uniform material mat;
uniform light light_source1;

void main (void)
{   
	vec3 normal_transformed = normal_matrix * _normal;

	vec4 pos_transformed_4 = view_matrix * _position;
	vec3 pos_transformed_3 = pos_transformed_4.xyz / pos_transformed_4.w;

	vec4 lightpos_transformed_4 = view_matrix * light_source1.position;
	vec3 lightpos_transformed_3 = lightpos_transformed_4.xyz / lightpos_transformed_4.w;

	vec3 pos_to_eye = normalize(-pos_transformed_3);

	if ( dot(normal_transformed, pos_to_eye) < 0.0)
	{
		normal_transformed = -normal_transformed;
	}

	vec3 light_to_pos = normalize(pos_transformed_3 - lightpos_transformed_3);

	vec4 ambient_component = mat.ka;
	vec4 diffuse_component = vec4(light_source1.color.rgb * mat.kd.rgb * max(0, dot(normal_transformed, -light_to_pos)), 1.0);
	vec4 specular_component = vec4(light_source1.color.rgb * mat.ks.rgb * pow(dot(pos_to_eye, normalize(reflect(-light_to_pos, normal_transformed))), mat.ns), 1.0);

	gl_FragColor = mat.kd;/*ambient_component + diffuse_component + specular_component;*/
}