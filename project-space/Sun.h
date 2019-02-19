#pragma once
#include "Billboard.h"

namespace ps
{
	class PROJECT_SPACE_EXPORT Sun :
		public Billboard
	{
	public:
		Sun(void);
		Sun(const Point3 & position, const float & width, const float & height);
		~Sun(void);

		const Light * getLight(void) const;
		void setLight(Light * light);

		virtual void renderObject(void);
	private:
		Light * m_SunLight;
	};
}

