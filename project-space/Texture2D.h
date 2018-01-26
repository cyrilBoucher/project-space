#pragma once

#include <GL/glew.h>

namespace ps
{
class Texture2D
{
	public:
		Texture2D(void);
		~Texture2D(void);

		const int & getWidth(void) const;

		const int & getHeight(void) const;

		const int & getPixelSize(void) const;

		const GLuint & getTexName(void) const;

		void setData(const int & width, const int & height, const GLint & internal_format, const GLvoid* data);
		void setData(const GLint & internal_format, const GLvoid* data);

		bool readTexture(char *filename);

		bool createTexture(int width, int height, GLint internal_format, const GLvoid* texture);
		bool createTexture(int width, int height, GLint internal_format);

	private:
		int m_Width;
		int m_Height;
		int m_PixelSize;

		GLuint m_TexName;

	};
}

