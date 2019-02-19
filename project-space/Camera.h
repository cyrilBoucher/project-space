#pragma once

#include "Point3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 

namespace ps
{
	class PROJECT_SPACE_EXPORT Camera
	{
	public:
		Camera(void);
		~Camera(void);

		const Point3 & getEye(void) const;
		const Point3 & getCenter(void) const;

		const Vec3 & getForward(void) const;
		const Vec3 & getUp(void) const;
		const Vec3 & getRight(void) const;

		glm::mat4 & getProjectionMatrix(void);
		glm::mat4 & getViewMatrix(void);
		glm::mat3 & getNormalMatrix(void);

		void getLookAt(Point3& eye, Point3& center, Vec3& up);
		void setLookAt(const Point3& eye, const Point3& center, const Vec3& up);

		void getFrustum(float& left, float& right, float& bottom, float& top, float& znear, float& zfar);
		void setFrustum(float& left, float& right, float& bottom, float& top, float& znear, float& zfar);

		void getPerspective(float& fovy, float& ratio, float& znear, float& zfar);
		void setPerspective(float& fovy, float& ratio, float& znear, float& zfar);

		void getViewport(unsigned int& width, unsigned int& height);
		void setViewport(unsigned int& width, unsigned int& height);

		void move(float f_coeff, float r_coeff, float u_coeff);
		void rotate(Vec3 axis, float angle);
	private:
		unsigned int m_ViewportWidth;
		unsigned int m_ViewportHeight;

		Point3 m_Eye;
		Point3 m_Center;

		Vec3 m_Forward;
		Vec3 m_Up;
		Vec3 m_Right;

		float m_LeftCP;
		float m_RightCP;
		float m_BottomCP;
		float m_TopCP;
		float m_ZNear;
		float m_ZFar;

		float m_Fovy;
		float m_Ratio;

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat3 m_NormalMatrix;
	};
}

