
#include "Material.h"

//Constructors and setters
ps::Material::Material(void)
{
	m_Ka = Color();
	m_Kd = Color();
	m_Ks = Color();
	m_Sh = 1.0f;
}


ps::Material::~Material(void)
{
}

const ps::Color & ps::Material::getKa(void) const
{
	return m_Ka;
}

void ps::Material::setKa(const ps::Color & ka)
{
	m_Ka = ka;
}

const ps::Color & ps::Material::getKd(void) const
{
	return m_Kd;
}

void ps::Material::setKd(const ps::Color & kd)
{
	m_Kd = kd;
}

const ps::Color & ps::Material::getKs(void) const
{
	return m_Ks;
}

void ps::Material::setKs(const ps::Color & ks)
{
	m_Ks = ks;
}

const GLfloat & ps::Material::getSh(void) const
{
	return m_Sh;
}

void ps::Material::setSh(const GLfloat & sh)
{
	m_Sh = sh;
}
