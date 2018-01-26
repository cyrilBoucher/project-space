
#include "Light.h"

//Constructors and destructors
ps::Light::Light(void)
{
	m_Position = Point3(0.0, 0.0, 0.0);
	m_Color = Color(1.0f, 1.0f, 1.0f, 1.0f);
	m_Direction = Vec3(0.0, 0.0, -1.0);
	m_Type = 1;
}

ps::Light::Light(const Point3 & position, const Color & color, const Vec3 & direction, const int & type)
{
	m_Position = position;
	m_Color = color;
	m_Direction = direction;
	m_Type = type;
}

ps::Light::~Light(void)
{
}

//Getters and setters
const ps::Point3 & ps::Light::getPosition(void) const
{
	return m_Position;
}

void ps::Light::setPosition(const ps::Point3 & position)
{
	m_Position = position;
}

const ps::Color & ps::Light::getColor(void) const
{
	return m_Color;
}

void ps::Light::setColor(const ps::Color & color)
{
	m_Color = color;
}

const ps::Vec3 & ps::Light::getDirection(void) const
{
	return m_Direction;
}

void ps::Light::setDirection(const ps::Vec3 & direction)
{
	m_Direction = direction;
}

const int & ps::Light::getType(void) const
{
	return m_Type;
}

void ps::Light::setType(const int & type)
{
	m_Type = type;
}