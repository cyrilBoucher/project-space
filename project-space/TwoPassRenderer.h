#pragma once
#include "Renderer.h"

#include "ScreenPlane.h"

namespace ps
{
	class PROJECT_SPACE_EXPORT TwoPassRenderer :
		public Renderer
	{
	public:
		TwoPassRenderer(void);
		TwoPassRenderer(const int & screen_width, const int & screen_height);
		~TwoPassRenderer(void);

		void reshapeFramebuffer();

		void initPostProcessingProgram(const char* vertex_shader_path, const char* fragment_shader_path);

		virtual void render(std::vector<Object*> & objects_to_render);

	private:
		GLuint m_FrameBuffer;
		GLuint m_DepthBuffer;
		ScreenPlane m_ScreenPlane;

		void setFramebuffer(const int & width, const int & height);
	};
}

