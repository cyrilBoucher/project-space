
#include "Cube.h"

const unsigned int ps::Cube::NB_VERTS = 8;
const unsigned int ps::Cube::NB_COORDS = 3;
const unsigned int ps::Cube::NB_TRIANGLES = 12;

const GLfloat ps::Cube::m_CubeCoords[ps::Cube::NB_VERTS*ps::Cube::NB_COORDS] = {
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,

	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f
};

const GLuint ps::Cube::m_CubeIndices[ps::Cube::NB_TRIANGLES*3] = {
	0, 1, 3,
	1, 2, 3,

	1, 5, 2,
	5, 6, 2,

	3, 2, 7,
	2, 6, 7,

	4, 0, 7,
	0, 3, 7,

	5, 4, 6,
	4, 7, 6,

	1, 5, 0,
	5, 4, 0
};

ps::Cube::Cube(void)
	: SingleObject()
{
	for(unsigned int i = 0; i < NB_VERTS; i++)
	{
		m_Vertices.push_back(m_CubeCoords[i*NB_COORDS]);
		m_Vertices.push_back(m_CubeCoords[i*NB_COORDS+1]);
		m_Vertices.push_back(m_CubeCoords[i*NB_COORDS+2]);
	}

	for(unsigned int i = 0; i < NB_TRIANGLES*3; i++)
	{
		m_Indices.push_back(m_CubeIndices[i]);
	}
}


ps::Cube::~Cube(void)
{
}
