
#include "Plane.h"

#include "trig.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 

const unsigned int ps::Plane::NB_VERTS = 4;
const unsigned int ps::Plane::NB_COORDS = 3;
const unsigned int ps::Plane::NB_TEX_COORDS = 2;
const unsigned int ps::Plane::NB_TRIANGLES = 2;

const GLfloat ps::Plane::m_PlaneCoords[ps::Plane::NB_VERTS*ps::Plane::NB_COORDS] = {
-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
-1.0f, 1.0f, 0.0f
};

const GLuint ps::Plane::m_PlaneIndices[ps::Plane::NB_TRIANGLES*3] = {
	0, 1, 3,
	1, 2, 3,
};

const GLfloat ps::Plane::m_PlaneNormals[ps::Plane::NB_VERTS*ps::Plane::NB_COORDS] = {
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f
};

const GLfloat ps::Plane::m_PlaneTexCoords[ps::Plane::NB_VERTS*ps::Plane::NB_TEX_COORDS] = {
0.0f, 0.0f,
1.0f, 0.0f,
1.0f, 1.0f,
0.0f, 1.0f
};

ps::Plane::Plane(void)
{
}

ps::Plane::Plane(const Point3 & position, const float & width, const float & height, const Vec3 & direction)
	: SingleObject()
{
	for(unsigned int i = 0; i < NB_VERTS; i++)
	{
		m_Vertices.push_back(m_PlaneCoords[i*NB_COORDS]);
		m_Vertices.push_back(m_PlaneCoords[i*NB_COORDS+1]);
		m_Vertices.push_back(m_PlaneCoords[i*NB_COORDS+2]);

		m_Normals.push_back(m_PlaneNormals[i*NB_COORDS]);
		m_Normals.push_back(m_PlaneNormals[i*NB_COORDS+1]);
		m_Normals.push_back(m_PlaneNormals[i*NB_COORDS+2]);

		m_TexCoords.push_back(m_PlaneTexCoords[i*NB_TEX_COORDS]);
		m_TexCoords.push_back(m_PlaneTexCoords[i*NB_TEX_COORDS+1]);
	}

	for(unsigned int i = 0; i < NB_TRIANGLES*3; i++)
	{
		m_Indices.push_back(m_PlaneIndices[i]);
	}

	//Setting model matrix
	glm::mat4 scale_matrix, rotation_matrix, translation_matrix;

	scale_matrix = glm::scale(scale_matrix, glm::vec3(width, height, 1.0f));

	Vec3 proj_direction = Vec3(direction.getDx(), 0.0, direction.getDz());
	proj_direction.normalize();

	float forward_angle = radToDeg(acos(proj_direction * Vec3(0.0, 0.0, 1.0)));
	Vec3 forward_rot_axis = proj_direction.crossproduct(Vec3(0.0, 0.0, 1.0));

	if(!forward_rot_axis.isNullVector())
	{
		rotation_matrix = glm::rotate(rotation_matrix, -forward_angle, glm::vec3(forward_rot_axis.getDx(), forward_rot_axis.getDy(), forward_rot_axis.getDz()));
	}

	float up_angle = radToDeg(acos(direction * proj_direction));

	Vec3 up_rot_axis;
	if(direction.getDy() < 0.0)
	{
		up_rot_axis = Vec3(1.0, 0.0, 0.0);
	}
	else
	{
		up_rot_axis = Vec3(-1.0, 0.0, 0.0);
	}
	

	if(!up_rot_axis.isNullVector())
	{
		rotation_matrix = glm::rotate(rotation_matrix, up_angle, glm::vec3(up_rot_axis.getDx(), up_rot_axis.getDy(), up_rot_axis.getDz()));
	}

	translation_matrix = glm::translate(translation_matrix, glm::vec3(position.getX(), position.getY(), position.getZ()));

	setModelMatrix(translation_matrix, rotation_matrix, scale_matrix);
}


ps::Plane::~Plane(void)
{
}
