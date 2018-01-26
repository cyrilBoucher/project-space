#pragma once
#include "Color.h"

#include <GL/glew.h>

namespace ps
{
	class Material
	{
	public:
		Material(void);
		~Material(void);

		const Color & getKa(void) const;
		void setKa(const Color & ka);

		const Color & getKd(void) const;
		void setKd(const Color & kd);

		const Color & getKs(void) const;
		void setKs(const Color & ks);

		const GLfloat & getSh(void) const;
		void setSh(const GLfloat & sh);

	private:
		Color m_Ka;
		Color m_Kd;
		Color m_Ks;
		GLfloat m_Sh;
	};
}

