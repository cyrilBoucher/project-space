#include "Billboard.h"

#include "trig.h"


ps::Billboard::Billboard(void)
{
}

ps::Billboard::Billboard(const Point3 & position, const float & width, const float & height)
	: Plane(position, width, height, Vec3(0.0, 0.0, 1.0))
{
	m_Position = position;
	m_Width = width;
	m_Height = height;
}


ps::Billboard::~Billboard(void)
{
}

void ps::Billboard::updatePosition(const Point3 & cam_pos)
{
	Vec3 direction, proj_direction;
	proj_direction.setDx(cam_pos.getX() - m_Position.getX());
	proj_direction.setDz(cam_pos.getZ() - m_Position.getZ());
	proj_direction.normalize();

	//Setting model matrix
	glm::mat4 scale_matrix, rotation_matrix, translation_matrix;

	scale_matrix = glm::scale(scale_matrix, glm::vec3(m_Width, m_Height, 1.0f));

	float forward_angle = radToDeg(acos(proj_direction * Vec3(0.0, 0.0, 1.0)));
	Vec3 forward_rot_axis = proj_direction.crossproduct(Vec3(0.0, 0.0, 1.0));

	if(!forward_rot_axis.isNullVector())
	{
		rotation_matrix = glm::rotate(rotation_matrix, -forward_angle, glm::vec3(forward_rot_axis.getDx(), forward_rot_axis.getDy(), forward_rot_axis.getDz()));
	}

	direction = cam_pos - m_Position;
	direction.normalize();

	float up_angle = radToDeg(acos(direction * proj_direction));

	Vec3 up_rot_axis;
	if(direction.getDy() < 0.0)
	{
		up_rot_axis = Vec3(1.0, 0.0, 0.0);
	}
	else
	{
		up_rot_axis = Vec3(-1.0, 0.0, 0.0);
	}
	

	if(!up_rot_axis.isNullVector())
	{
		rotation_matrix = glm::rotate(rotation_matrix, up_angle, glm::vec3(up_rot_axis.getDx(), up_rot_axis.getDy(), up_rot_axis.getDz()));
	}

	translation_matrix = glm::translate(translation_matrix, glm::vec3(m_Position.getX(), m_Position.getY(), m_Position.getZ()));

	setModelMatrix(translation_matrix, rotation_matrix, scale_matrix);
}
