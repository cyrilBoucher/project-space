
#include "TwoPassRenderer.h"

#include "shaders.h"

#include <sstream>

ps::TwoPassRenderer::TwoPassRenderer(void)
{
	setFramebuffer(600, 400);

	m_ScreenPlane.createObjectBuffers();
}

ps::TwoPassRenderer::TwoPassRenderer(const int & screen_width, const int & screen_height)
{
	setFramebuffer(screen_width, screen_height);

	m_ScreenPlane.createObjectBuffers();
}


ps::TwoPassRenderer::~TwoPassRenderer(void)
{
}

void ps::TwoPassRenderer::setFramebuffer(const int & width, const int & height)
{
	// Create framebuffer and texture
	glGenFramebuffers(1, &m_FrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);

	m_ScreenPlane.getTexture().createTexture(width, height, GL_RGB);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ScreenPlane.getTexture().getTexName(), 0);

	glGenRenderbuffers(1, &m_DepthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_DepthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthBuffer);
}

void ps::TwoPassRenderer::reshapeFramebuffer()
{
	if(m_Camera)
	{
		int fb_width, fb_height;
		unsigned int viewport_width, viewport_height;

		fb_width = m_ScreenPlane.getTexture().getWidth();
		fb_height = m_ScreenPlane.getTexture().getHeight();

		m_Camera->getViewport(viewport_width, viewport_height);

		if(fb_width != viewport_width || fb_height != viewport_height)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);

			m_ScreenPlane.getTexture().setData(viewport_width, viewport_height, GL_RGB, NULL);

			glBindRenderbuffer(GL_RENDERBUFFER, m_DepthBuffer);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, viewport_width, viewport_height);
		}
	}
	
}

void ps::TwoPassRenderer::initPostProcessingProgram(const char* vertex_shader_path, const char* fragment_shader_path)
{
	GLuint vertex_shader, fragment_shader;

	vertex_shader = initshaders(GL_VERTEX_SHADER, "shaders/screen.vert.glsl") ;
    fragment_shader = initshaders(GL_FRAGMENT_SHADER, "shaders/screen.frag.glsl") ;
	m_ScreenPlane.getProgram().init(vertex_shader, fragment_shader);
}

void ps::TwoPassRenderer::render(std::vector<Object*> & objects_to_render)
{
	glClearColor(0.4, 0.4, 0.4, 1.0);

	glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);
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
			program.setUniform("normal_matrix", m_Camera->getNormalMatrix());

			if(!m_Lights.empty())
			{
				if((*it_obj)->receivesLighting())
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
		}

		program.setUniform("model_matrix", (*it_obj)->getModelMatrix());

		(*it_obj)->renderObject();
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_ScreenPlane.getProgram().use();

	m_ScreenPlane.renderObject();

	glFlush();
}
