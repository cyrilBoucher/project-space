#pragma once
#include "CompositeObject.h"

namespace ps
{
	class PROJECT_SPACE_EXPORT Spaceship :
		public CompositeObject
	{
	public:
		Spaceship(void);
		Spaceship(const Point3 & position, const float & size, const Vec3 & direction);
		~Spaceship(void);

		virtual void renderObject(void);
	};
}

