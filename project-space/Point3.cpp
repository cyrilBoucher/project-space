
#include "Point3.h"
#include <iostream>
#include <math.h>


//Constructors and destructors
ps::Point3::Point3(void)
{
	m_X = 0.0;
	m_Y = 0.0;
	m_Z = 0.0;
}

ps::Point3::Point3(const double & x, const double & y, const double & z)
{
    m_X = x;
    m_Y = y;
    m_Z = z; 
}


ps::Point3::~Point3(void)
{
}

//Operators
ps::Point3 ps::Point3::operator+(ps::Vec3 & v1)
{
	return ps::Point3(m_X+v1.getDx(), m_Y+v1.getDy(), m_Z+v1.getDz());
}

ps::Point3 & ps::Point3::operator+=(ps::Vec3 & v1)
{
	m_X += v1.getDx();
	m_Y += v1.getDy();
	m_Z += v1.getDz();
	return *this;
}

ps::Vec3 ps::Point3::operator-(const ps::Point3 & right) const
{
	return ps::Vec3(m_X-right.getX(), m_Y-right.getY(), m_Z-right.getZ());
}

//Getters and setters
const double & ps::Point3::getX(void) const
{
	return m_X;
}

void ps::Point3::setX(const double & x)
{
	m_X = x;
}

const double & ps::Point3::getY(void) const
{
	return m_Y;
}

void ps::Point3::setY(const double & y)
{
	m_Y = y;
}

const double & ps::Point3::getZ(void) const
{
	return m_Z;
}

void ps::Point3::setZ(const double & z)
{
	m_Z = z;
}

//Methods
double ps::Point3::dist(const ps::Point3 & p1)
{
    return sqrt(  (p1.m_X-m_X)*(p1.m_X-m_X) + (p1.m_Y-m_Y)*(p1.m_Y-m_Y) + (p1.m_Z-m_Z)*(p1.m_Z-m_Z)  ); 
}

void ps::Point3::rotate(ps::Vec3 & lp, double theta)
{
	ps::Vec3 tmp(m_X, m_Y, m_Z);
	tmp.rotate(lp, theta);
	m_X = tmp.getDx(); m_Y = tmp.getDy(); m_Z = tmp.getDz();
}

void ps::Point3::print(char *s)
{
	  std::cout << s << m_X << ", " << m_Y << ", " << m_Z << "\n";
}
