#pragma once

#include "project-space/project-space-export.h"

namespace ps
{
	class PROJECT_SPACE_EXPORT Vec3
	{
	public:
		Vec3(void);
		Vec3(const double & dx, const double & dy, const double & dz);
		~Vec3(void);

		const double & getDx(void) const;
		void setDx(const double & dx);

		const double & getDy(void) const;
		void setDy(const double & dy);

		const double & getDz(void) const;
		void setDz(const double & dz);

		double operator*(const Vec3 & v1) const;
		Vec3 operator^(const Vec3 & v1) const;
		Vec3 operator+(Vec3 & v1);
		Vec3 operator-() const;
		Vec3 operator*(double s);
		void crossproduct(const Vec3 & v1, const Vec3 & v2);
		Vec3 crossproduct(const Vec3 & v1) const;
		void rotate(Vec3 & lp, double theta);
		double length(void);
		void normalize(void);
		bool isNullVector(void) const;
		void print(char *s);

	private:
		double m_Dx, m_Dy, m_Dz; 
	};
}

