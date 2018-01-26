#pragma once
#include "SingleObject.h"

#include "Point3.h"

namespace ps
{
	class PROJECT_SPACE_EXPORT Plane :
		public SingleObject
	{
	public:
		Plane(void);
		Plane(const Point3 & position, const float & width, const float & height, const Vec3 & direction);
		~Plane(void);

	protected:
		static const unsigned int NB_VERTS;
		static const unsigned int NB_COORDS;
		static const unsigned int NB_TEX_COORDS;
		static const unsigned int NB_TRIANGLES;

		static const GLfloat m_PlaneCoords[];

		static const GLuint m_PlaneIndices[];

		static const GLfloat m_PlaneNormals[];

		static const GLfloat m_PlaneTexCoords[];
	};
}

