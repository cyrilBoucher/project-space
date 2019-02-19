#pragma once

#include <GL/glew.h>

namespace ps
{
	class TextureCubeMap
	{
	public:
		TextureCubeMap(void);
		~TextureCubeMap(void);

		const GLuint & getTexName(void) const;

		bool readTexture(char *filename);

		bool createTexture(int width, int height, GLint internal_format, const GLvoid** textures);

	private:
		int m_Width;
		int m_Height;
		int m_PixelSize;

		GLuint m_TexName;
	};
}

