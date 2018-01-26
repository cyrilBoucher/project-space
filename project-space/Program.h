#pragma once

#include "Point3.h"
#include "Color.h"
#include "Light.h"
#include "Material.h"

#include <string>
#include <map>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 

namespace ps
{
	class PROJECT_SPACE_EXPORT Program
	{
	public:
		Program(void);
		~Program(void);

		const GLuint & getId(void);

		template<typename T>
		void setUniform(const std::string& name, T&& value);
		void setUniform(const std::string& name, Material& material);
		void setUniform(const std::string& name, Light& light);
		void setUniform(GLuint location, int & value);
		void setUniform(GLuint location, float & value);
		void setUniform(GLuint location, glm::mat4& matrix4);
		void setUniform(GLuint location, glm::mat3& matrix3);
		void setUniform(GLuint location, Vec3& vector3);
		void setUniform(GLuint location, glm::vec4& vector4);
		void setUniform(GLuint location, Point3& point3);
		void setUniform(GLuint location, Color& color);

		void init(GLuint vertex_shader, GLuint fragment_shader);
		void use();

	private: 
		GLuint m_ProgramId;

		std::map<std::string, GLuint> m_Uniforms;

		void handleErrors(void);
	};

	template<typename T>
	inline void ps::Program::setUniform(const std::string& name, T&& value)
	{
		GLuint location = -1;

		if(m_Uniforms.find(name) == m_Uniforms.end())
		{
			location = glGetUniformLocation(m_ProgramId, name.c_str());
		}
		else
		{
			location = m_Uniforms[name];
		}

		/*if(location == -1)
		{
			std::string error = "Program could not get location of uniform " + name;
			throw std::runtime_error(error);
		}*/

		if(location != -1)
		{
			m_Uniforms[name] = location;

			setUniform(location, std::forward<T>(value));
		}
	}
}



