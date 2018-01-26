#pragma once

#include "Object.h"
#include "Camera.h"
#include <vector>

namespace ps
{
	class PROJECT_SPACE_EXPORT Renderer
	{
	public:
		Renderer(void);
		Renderer(Camera * camera);
		~Renderer(void);

		Camera * getCamera(void);
		void setCamera(Camera * camera);

		void addLight(const Light * light);

		virtual void render(std::vector<Object*> & objects_to_render);

	protected:
		Camera * m_Camera;
		std::vector<const Light*> m_Lights;
	};
}

