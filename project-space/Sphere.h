#pragma once
#include "SingleObject.h"

namespace ps
{
	class Sphere :
		public SingleObject
	{
	public:
		Sphere(void);
		Sphere(const Point3 & position, const float & radius);
		~Sphere(void);
	};
}

