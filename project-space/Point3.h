#pragma once
#include "Vec3.h"

namespace ps
{
	class PROJECT_SPACE_EXPORT Point3
	{
	public:
		Point3(void);
		Point3(const double & x, const double & y, const double & z);
		~Point3(void);

		const double & getX(void) const;
		void setX(const double & x);

		const double & getY(void) const;
		void setY(const double & y);

		const double & getZ(void) const;
		void setZ(const double & z);

		double dist(const Point3 & p1);
		Point3 operator+(Vec3 & v1);
		Point3 & operator+=(Vec3 & v1);
		Vec3 operator-(const Point3 & right) const;
		void rotate(Vec3 & lp, double theta);
		void print(char *s);

	private:
		double m_X, m_Y, m_Z; 
	};
}

