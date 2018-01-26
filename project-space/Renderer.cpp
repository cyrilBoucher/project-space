
#include "Renderer.h"

#include "shaders.h"

#include <sstream>

ps::Renderer::Renderer(void)
{
}

ps::Renderer::Renderer(Camera * camera)
{
	setCamera(camera);
}

ps::Renderer::~Renderer(void)
{
}

ps::Camera * ps::Renderer::getCamera(void)
{
	return m_Camera;
}

void ps::Renderer::setCamera(Camera * camera)
{
	if(camera)
	{
		m_Camera = camera;
	}
}

void ps::Renderer::addLight(const Light * light)
{
	if(light)
	{
		m_Lights.push_back(light);
	}
}

void ps::Renderer::render(std::vector<Object*> & objects_to_render)
{
	glClearColor(0.4f, 0.4f, 0.4f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLuint prev_prog_id = -1;

	for(std::vector<Object*>::iterator it_obj = objects_to_render.begin(); it_obj != objects_to_render.end(); it_obj++)
	{
		Program & program = (*it_obj)->getProgram();

		if(program.getId() != prev_prog_id)
		{
			program.use();
			program.setUniform("projection_matrix", m_Camera->getProjectionMatrix());
			program.setUniform("view_matrix", m_Camera->getViewMatrix());

			if(!m_Lights.empty())
			{
				int light_number = 1;
				for(std::vector<const Light*>::const_iterator it_l = m_Lights.begin(); it_l != m_Lights.end(); it_l++)
				{
					std::string light_number_s;
					std::ostringstream convertion;

					convertion << light_number;
					light_number_s = convertion.str();

					Light light = *(*it_l);
					program.setUniform("light_source" + light_number_s, light);
					light_number++;
				}
			}
		}

		program.setUniform("model_matrix", (*it_obj)->getModelMatrix());

		(*it_obj)->renderObject();

		prev_prog_id = program.getId();
	}

	glFlush();
}
