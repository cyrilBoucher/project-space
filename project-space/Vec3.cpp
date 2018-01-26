
#include "Vec3.h"
#include <iostream>
#include <math.h>

//Constructors and destructors
ps::Vec3::Vec3(void)
{
	m_Dx = 0.0;
	m_Dy = 0.0;
	m_Dz = 0.0;
}

ps::Vec3::Vec3(const double & dx, const double & dy, const double & dz)
{
    m_Dx = dx;
    m_Dy = dy;
    m_Dz = dz;
}


ps::Vec3::~Vec3(void)
{
}

//Operators
double ps::Vec3::operator*(const ps::Vec3 & v1) const
{
    return (v1.m_Dx*m_Dx + v1.m_Dy*m_Dy + v1.m_Dz*m_Dz);
}

ps::Vec3 ps::Vec3::operator^(const ps::Vec3 & v1) const
{
	return crossproduct(v1);
}

ps::Vec3 ps::Vec3::operator+(ps::Vec3 & v1)
{
	return ps::Vec3(m_Dx+v1.m_Dx, m_Dy+v1.m_Dy, m_Dz+v1.m_Dz);
}

ps::Vec3 ps::Vec3::operator-() const
{
	return ps::Vec3(-m_Dx, -m_Dy, -m_Dz);
}

ps::Vec3 ps::Vec3::operator*(double s)
{
	return ps::Vec3(m_Dx*s, m_Dy*s, m_Dz*s);
}

//Getters and setters
const double & ps::Vec3::getDx(void) const
{
	return m_Dx;
}
void ps::Vec3::setDx(const double & dx)
{
	m_Dx = dx;
}

const double & ps::Vec3::getDy(void) const
{
	return m_Dy;
}
void ps::Vec3::setDy(const double & dy)
{
	m_Dy = dy;
}

const double & ps::Vec3::getDz(void) const
{
	return m_Dz;
}
void ps::Vec3::setDz(const double & dz)
{
	m_Dz = dz;
}

//Methods
void ps::Vec3::crossproduct(const ps::Vec3 & v1, const ps::Vec3 & v2)
{
	m_Dx = v1.m_Dy * v2.m_Dz - v1.m_Dz * v2.m_Dy;
	m_Dy = v1.m_Dz * v2.m_Dx - v1.m_Dx * v2.m_Dz;
	m_Dz = v1.m_Dx * v2.m_Dy - v1.m_Dy * v2.m_Dx;
}

ps::Vec3 ps::Vec3::crossproduct(const ps::Vec3 & v1) const
{
	ps::Vec3 result;
	result.crossproduct(*this, v1);
	return result;
}

double ps::Vec3::length(void)
{
    return sqrt( m_Dx*m_Dx + m_Dy*m_Dy + m_Dz*m_Dz ); 
}

void ps::Vec3::normalize(void)
{
    double l = length();
    m_Dx = m_Dx/l;
    m_Dy = m_Dy/l;
    m_Dz = m_Dz/l;
}

void ps::Vec3::rotate(ps::Vec3 & lp, double theta)
{
	//rotate vector *this around the line defined by lp through the origin by theta degrees.
	const double cos_theta = cos(theta);
	const double dot = *this*lp;
	ps::Vec3 cross = crossproduct(lp);
	m_Dx *= cos_theta; m_Dy *= cos_theta; m_Dz *= cos_theta; 
	m_Dx += lp.m_Dx * dot * (1.0-cos_theta); m_Dy += lp.m_Dy * dot * (1.0-cos_theta); m_Dz += lp.m_Dz * dot * (1.0-cos_theta);
	m_Dx -= cross.m_Dx*sin(theta); m_Dy -= cross.m_Dy*sin(theta); m_Dz -= cross.m_Dz*sin(theta);
}

bool ps::Vec3::isNullVector(void) const
{
	return (m_Dx == 0.0 && m_Dy == 0.0 && m_Dz == 0.0);
}

void ps::Vec3::print(char *s)
{
	  std::cout << s << m_Dx << ", " << m_Dy << ", " << m_Dz << "\n";
}
