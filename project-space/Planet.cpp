
#include "Planet.h"


ps::Planet::Planet(void)
{
}

ps::Planet::Planet(const Point3 & position, const float & radius, const float & rotation_speed, const Vec3 & rotation_axis)
	: Sphere(position, radius)
{
	m_Position = position;
	m_Radius = radius;
	m_RotationSpeed = rotation_speed; //Specified in degrees
	m_RotationAxis = rotation_axis;

	m_Angle = 0.0;

	//Setting model matrix
	glm::mat4 scale_matrix, rotation_matrix, translation_matrix;

	scale_matrix = glm::scale(scale_matrix, glm::vec3(m_Radius, m_Radius, m_Radius));

	rotation_matrix = glm::rotate(rotation_matrix, m_Angle, glm::vec3(m_RotationAxis.getDx(), m_RotationAxis.getDy(), m_RotationAxis.getDz()));

	translation_matrix = glm::translate(translation_matrix, glm::vec3(m_Position.getX(), m_Position.getY(), m_Position.getZ()));

	setModelMatrix(translation_matrix, rotation_matrix, scale_matrix);
}


ps::Planet::~Planet(void)
{
}

void ps::Planet::update(double delta_t)
{
	m_Angle += (float)fmod((m_RotationSpeed*delta_t),360.0);

	//Setting model matrix
	glm::mat4 scale_matrix, rotation_matrix, translation_matrix;

	scale_matrix = glm::scale(scale_matrix, glm::vec3(m_Radius, m_Radius, m_Radius));

	rotation_matrix = glm::rotate(rotation_matrix, m_Angle, glm::vec3(m_RotationAxis.getDx(), m_RotationAxis.getDy(), m_RotationAxis.getDz()));

	translation_matrix = glm::translate(translation_matrix, glm::vec3(m_Position.getX(), m_Position.getY(), m_Position.getZ()));

	setModelMatrix(translation_matrix, rotation_matrix, scale_matrix);
}
