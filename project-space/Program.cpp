
#include "Program.h"

#include <iostream>

// Constructors and destructors
ps::Program::Program(void)
{
}


ps::Program::~Program(void)
{
}

// Getters and setters
const GLuint & ps::Program::getId(void)
{
	return m_ProgramId;
}

// Methods
void ps::Program::setUniform(const std::string& name, const ps::Material& material)
{
	Color kd, ka, ks;
	float ns;

	kd = material.getKd();
	ka = material.getKa();
	ks = material.getKs();
	ns = material.getSh();

	setUniform(name + ".kd", kd);
	setUniform(name + ".ka", ka);
	setUniform(name + ".ks", ks);
	setUniform(name + ".ns", ns);
}

void ps::Program::setUniform(const std::string& name, const Light& light)
{
	Point3 position;
	Color color;
	Vec3 direction;
	int type;

	position = light.getPosition();
	color = light.getColor();
	direction = light.getDirection();
	type = light.getType();

	setUniform(name + ".position", Color(position.getX(), position.getY(), position.getZ(), 1.0f)/*glm::vec4(position.getX(), position.getY(), position.getZ(), 1.0)*/); //Don't know why it doesn't work with glm::vec4
	setUniform(name + ".color", color);
	/*setUniform(name + ".direction", direction);
	setUniform(name + ".type", type);*/
}

void ps::Program::setUniform(GLuint location, int value)
{
	glUniform1i(location, value);
}

void ps::Program::setUniform(GLuint location, float value)
{
	glUniform1f(location, value);
}

void ps::Program::setUniform(GLuint location, const glm::mat4& matrix4)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, &matrix4[0][0]);
}

void ps::Program::setUniform(GLuint location, const glm::mat3& matrix3)
{
	glUniformMatrix3fv(location, 1, GL_FALSE, &matrix3[0][0]);
}

void ps::Program::setUniform(GLuint location, const ps::Vec3& vector3)
{
	glUniform3d(location, vector3.getDx(), vector3.getDy(), vector3.getDz());
}

void ps::Program::setUniform(GLuint location, const glm::vec4& vector4)
{
	glUniform4d(location, vector4.x, vector4.y, vector4.z, vector4.w);
}

void ps::Program::setUniform(GLuint location, const ps::Point3& point3)
{
	glUniform3d(location, point3.getX(), point3.getY(), point3.getZ());
}

void ps::Program::setUniform(GLuint location, const ps::Color& color)
{
	glUniform4f(location, color.getR(), color.getG(), color.getB(), color.getA());
}

void ps::Program::init(GLuint vertex_shader, GLuint fragment_shader)
{
	m_ProgramId = glCreateProgram(); 
  
	glAttachShader(m_ProgramId, vertex_shader); 
	glAttachShader(m_ProgramId, fragment_shader); 
	glLinkProgram(m_ProgramId);
}

void ps::Program::use()
{
	GLint linked ; 

	glGetProgramiv(m_ProgramId, GL_LINK_STATUS, &linked); 
	if (linked)
	{
		glUseProgram(m_ProgramId);
	}
	else 
	{ 
		handleErrors();
		throw 4; 
	}
}

void ps::Program::handleErrors(void)
{
	GLint length; 
	GLchar * log; 
	glGetProgramiv(m_ProgramId, GL_INFO_LOG_LENGTH, &length);
	log = new GLchar[length+1];
	glGetProgramInfoLog(m_ProgramId, length, &length, log);
	std::cout << "Compile Error, Log Below\n" << log << "\n"; 
	delete [] log;
}

