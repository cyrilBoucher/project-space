#pragma once

#include "project-space/project-space-export.h"
#include "Cube.h"

#include "TextureCubeMap.h"

namespace ps
{
	class PROJECT_SPACE_EXPORT Skybox :
		public Cube
	{
	public:
		Skybox(void);
		Skybox(const GLfloat & size);
		~Skybox(void);

		virtual void renderObject(void);

	private:
		TextureCubeMap m_Texture;
	};
}

