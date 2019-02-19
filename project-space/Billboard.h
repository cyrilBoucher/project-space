#pragma once
#include "Plane.h"

namespace ps
{
	class PROJECT_SPACE_EXPORT Billboard :
		public Plane
	{
	public:
		Billboard(void);
		Billboard(const Point3 & position, const float & width, const float & height);
		~Billboard(void);

		void updatePosition(const Point3 & cam_pos);

	private:
		Point3 m_Position;
		float m_Width;
		float m_Height;
	};
}

