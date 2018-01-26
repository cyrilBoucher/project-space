
#include "ScreenPlane.h"

ps::ScreenPlane::ScreenPlane(void)
{
	for(unsigned int i = 0; i < NB_VERTS; i++)
	{
		m_Vertices.push_back(m_PlaneCoords[i*NB_COORDS]);
		m_Vertices.push_back(m_PlaneCoords[i*NB_COORDS+1]);
		m_Vertices.push_back(m_PlaneCoords[i*NB_COORDS+2]);

		m_TexCoords.push_back(m_PlaneTexCoords[i*NB_TEX_COORDS]);
		m_TexCoords.push_back(m_PlaneTexCoords[i*NB_TEX_COORDS+1]);
	}

	for(unsigned int i = 0; i < NB_TRIANGLES*3; i++)
	{
		m_Indices.push_back(m_PlaneIndices[i]);
	}
}


ps::ScreenPlane::~ScreenPlane(void)
{
}
