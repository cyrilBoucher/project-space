
#include "Camera.h"

#include "trig.h"

#include <math.h>

ps::Camera::Camera(void)
{
}


ps::Camera::~Camera(void)
{
}

const ps::Point3 & ps::Camera::getEye(void) const
{
	return m_Eye;
}

const ps::Point3 & ps::Camera::getCenter(void) const
{
	return m_Center;
}

const ps::Vec3 & ps::Camera::getForward(void) const
{
	return m_Forward;
}

const ps::Vec3 & ps::Camera::getUp(void) const
{
	return m_Up;
}

const ps::Vec3 & ps::Camera::getRight(void) const
{
	return m_Right;
}

glm::mat4 & ps::Camera::getProjectionMatrix(void)
{
	return m_ProjectionMatrix;
}

glm::mat4 & ps::Camera::getViewMatrix(void)
{
	return m_ViewMatrix;
}

glm::mat3 & ps::Camera::getNormalMatrix(void)
{
	return m_NormalMatrix;
}

void ps::Camera::getLookAt(ps::Point3& eye, ps::Point3& center, ps::Vec3& up)
{
	eye = m_Eye;
	center = m_Center;
	up = m_Up;
}

void ps::Camera::setLookAt(ps::Point3& eye, ps::Point3& center, ps::Vec3& up)
{
	m_Eye = eye;
	m_Center = center;
	m_Up = up;
	m_Up.normalize();

	m_Forward = m_Center - m_Eye;
	m_Forward.normalize();

	m_Right = m_Forward.crossproduct(m_Up);
	m_Right.normalize();

	m_ViewMatrix = glm::lookAt(glm::vec3(m_Eye.getX(), m_Eye.getY(), m_Eye.getZ()), 
								glm::vec3(m_Eye.getX() + m_Forward.getDx(), m_Eye.getY() + m_Forward.getDy(), m_Eye.getZ() + m_Forward.getDz()), 
								glm::vec3(m_Up.getDx(), m_Up.getDy(), m_Up.getDz()));

	m_NormalMatrix = glm::transpose(glm::inverse(glm::mat3(m_ViewMatrix)));
}

void ps::Camera::getFrustum(float& left, float& right, float& bottom, float& top, float& znear, float& zfar)
{
	left = m_LeftCP;
	right = m_RightCP;
	bottom = m_BottomCP;
	top = m_TopCP;
	znear = m_ZNear;
	zfar = m_ZFar;
}

void ps::Camera::setFrustum(float& left, float& right, float& bottom, float& top, float& znear, float& zfar)
{
	m_LeftCP = left;
	m_RightCP = right;
	m_BottomCP = bottom;
	m_TopCP = top;
	m_ZNear = znear;
	m_ZFar = zfar;

	m_ProjectionMatrix = glm::frustum(m_LeftCP, m_RightCP, m_BottomCP, m_TopCP, m_ZNear, m_ZFar);
}

void ps::Camera::getPerspective(float& fovy, float& ratio, float& znear, float& zfar)
{
	fovy = m_Fovy;
	ratio = m_Ratio;
	znear = m_ZNear;
	zfar = m_ZFar;
}

void ps::Camera::setPerspective(float& fovy, float& ratio, float& znear, float& zfar)
{
	m_Fovy = fovy;
	m_Ratio = ratio;
	m_ZNear = znear;
	m_ZFar = zfar;

	double half_fov = degToRad((double)m_Fovy) / 2.0;
	double tangent = tan(half_fov);

	float right = znear * (float)tangent;
	float top = right * ratio;

	m_LeftCP = -right;
	m_RightCP = right;
	m_BottomCP = -top;
	m_TopCP = top;

	m_ProjectionMatrix = glm::perspective(m_Fovy, m_Ratio, m_ZNear, m_ZFar);
}

void ps::Camera::getViewport(unsigned int& width, unsigned int& height)
{
	width = m_ViewportWidth;
	height = m_ViewportHeight;
}

void ps::Camera::setViewport(unsigned int& width, unsigned int& height)
{
	m_ViewportWidth = width;
	m_ViewportHeight = height;

	m_Ratio = m_ViewportWidth/(float)m_ViewportHeight;

	m_ProjectionMatrix = glm::perspective(m_Fovy, m_Ratio, m_ZNear, m_ZFar);
}

void ps::Camera::move(float f_coeff, float r_coeff, float u_coeff)
{
	m_Eye += m_Forward*f_coeff + m_Right*r_coeff + m_Up*u_coeff;

	m_ViewMatrix = glm::lookAt(glm::vec3(m_Eye.getX(), m_Eye.getY(), m_Eye.getZ()), 
								glm::vec3(m_Eye.getX() + m_Forward.getDx(), m_Eye.getY() + m_Forward.getDy(), m_Eye.getZ() + m_Forward.getDz()), 
								glm::vec3(m_Up.getDx(), m_Up.getDy(), m_Up.getDz()));

	m_NormalMatrix = glm::transpose(glm::inverse(glm::mat3(m_ViewMatrix)));
}

void ps::Camera::rotate(ps::Vec3 axis, float angle)
{
	ps::Vec3 eye_vector = m_Eye - m_Center;

	m_Forward.rotate(axis, angle);
	/*m_Up.rotate(axis, angle);
	eye_vector.rotate(axis, angle);

	m_Eye = m_Center + eye_vector;*/

	m_Right = m_Forward.crossproduct(m_Up);

	m_Forward.normalize();
	m_Right.normalize();
	m_Up.normalize();

	m_ViewMatrix = glm::lookAt(glm::vec3(m_Eye.getX(), m_Eye.getY(), m_Eye.getZ()), 
								glm::vec3(m_Eye.getX() + m_Forward.getDx(), m_Eye.getY() + m_Forward.getDy(), m_Eye.getZ() + m_Forward.getDz()), 
								glm::vec3(m_Up.getDx(), m_Up.getDy(), m_Up.getDz()));

	m_NormalMatrix = glm::transpose(glm::inverse(glm::mat3(m_ViewMatrix)));
}
