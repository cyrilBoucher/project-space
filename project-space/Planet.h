#pragma once
#include "sphere.h"

namespace ps
{
	class Planet :
		public Sphere
	{
	public:
		Planet(void);
		Planet(const Point3 & position, const float & radius, const float & rotation_speed, const Vec3 & rotation_axis);
		~Planet(void);

		void update(double delta_t);

	protected:
		Point3 m_Position;
		float m_Radius;
		float m_Angle;
		float m_RotationSpeed;
		Vec3 m_RotationAxis;
	};
}

