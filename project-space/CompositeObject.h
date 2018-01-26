#pragma once
#include "Object.h"
#include "SingleObject.h"

namespace ps
{
	class PROJECT_SPACE_EXPORT CompositeObject :
		public Object
	{
	public:
		CompositeObject(void);
		~CompositeObject(void);

		std::vector<SingleObject *>& getParts(void);

		virtual void readMesh(char *filename);

		virtual void computeNormals(void);

		virtual void createObjectBuffers(void);

		virtual void renderObject(void);

		void setTextures(std::map<GLuint, Texture2D> textures);

	protected:
		std::vector<SingleObject *> m_Parts;
	};
}

