#pragma once

#include "Point3.h"
#include "Color.h"

namespace ps
{
	class PROJECT_SPACE_EXPORT Light
	{
	public:
		Light(void);
		Light(const Point3 & position, const Color & color, const Vec3 & direction, const int & type);
	
		~Light(void);

		const Point3 & getPosition(void) const;
		void setPosition(const Point3 & position);

		const Color & getColor(void) const;
		void setColor(const Color & color);

		const Vec3 & getDirection(void) const;
		void setDirection(const Vec3 & direction);

		const int & getType(void) const;
		void setType(const int & type);

	private:
		Point3 m_Position;
		Color m_Color;
		Vec3 m_Direction;
		int m_Type;
	};
}

