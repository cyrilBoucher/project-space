
#include "Color.h"

//Constructors and destructors
ps::Color::Color(void)
{
	m_R = m_G = m_B = m_A = 0.0f;
}

ps::Color::Color(const GLfloat & r, const GLfloat & g, const GLfloat & b)
{
	setRGBA(r,g,b,1.0f);
}

ps::Color::Color(const GLfloat & r, const GLfloat & g, const GLfloat & b, const GLfloat & a)
{
	setRGBA(r,g,b,a);
}

ps::Color::Color(const ps::Color &copy)
{
	m_R = copy.m_R;
	m_G = copy.m_G;
	m_B = copy.m_B;
	m_A = copy.m_A;
}

ps::Color::~Color(void)
{
}

//Getters and setters
const GLfloat & ps::Color::getR(void) const
{
	return m_R;
}

void ps::Color::setR(const GLfloat & r)
{
	m_R = r;
}

const GLfloat & ps::Color::getG(void) const
{
	return m_G;
}

void ps::Color::setG(const GLfloat & g)
{
	m_G = g;
}

const GLfloat & ps::Color::getB(void) const
{
	return m_B;
}

void ps::Color::setB(const GLfloat & b)
{
	m_B = b;
}

const GLfloat & ps::Color::getA(void) const
{
	return m_A;
}

void ps::Color::setA(const GLfloat & a)
{
	m_A = a;
}

void ps::Color::setRGBA(const GLfloat & r, const GLfloat & g, const GLfloat & b, const GLfloat & a)
{
	m_R = r;
	m_G = g;
	m_B = b;
	m_A = a;
}

//Operators
ps::Color& ps::Color::operator=(const Color &right)
{
	m_R = right.m_R;
	m_G = right.m_G;
	m_B = right.m_B;
	m_A = right.m_A;

	return *this;
}