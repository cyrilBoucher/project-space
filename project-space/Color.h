#pragma once

#include <GL/glew.h>

namespace ps
{
	class Color
	{
	public:
		Color(void);
		Color(const GLfloat & r, const GLfloat & g, const GLfloat & b);
		Color(const GLfloat & r, const GLfloat & g, const GLfloat & b, const GLfloat & a);
		Color(const Color &copy);
		~Color(void);

		const GLfloat & getR(void) const;
		void setR(const GLfloat & r);

		const GLfloat & getG(void) const;
		void setG(const GLfloat & r);

		const GLfloat & getB(void) const;
		void setB(const GLfloat & r);

		const GLfloat & getA(void) const;
		void setA(const GLfloat & r);

		void setRGBA(const GLfloat & r, const GLfloat & g, const GLfloat & b, const GLfloat & a);

		Color& operator=(const Color &right);

	private:
		GLfloat m_R;
		GLfloat m_G;
		GLfloat m_B;
		GLfloat m_A;
	};
}

