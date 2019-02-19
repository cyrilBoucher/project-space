#pragma once
#include "SingleObject.h"

namespace ps
{
	class Cube :
		public SingleObject
	{
	public:
		Cube(void);
		~Cube(void);

	protected:
		static const unsigned int NB_VERTS;
		static const unsigned int NB_COORDS;
		static const unsigned int NB_TRIANGLES;

		static const GLfloat m_CubeCoords[];

		static const GLuint m_CubeIndices[];
	};
}

