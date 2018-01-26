
#include "Spaceship.h"

#include "shaders.h"
#include "trig.h"


ps::Spaceship::Spaceship(void)
	: CompositeObject()
{
	readMesh("objects/SmallSpaceFighter.obj");
	
	computeNormals();

	GLuint vertex_shader = initshaders(GL_VERTEX_SHADER, "shaders/spaceship.vert.glsl") ;
    GLuint fragment_shader = initshaders(GL_FRAGMENT_SHADER, "shaders/spaceship.frag.glsl") ;
	m_Program.init(vertex_shader, fragment_shader);

	createObjectBuffers();

	m_LightingFlag = true;
}

ps::Spaceship::Spaceship(const Point3 & position, const float & size, const Vec3 & direction)
	: CompositeObject()
{
	readMesh("objects/SmallSpaceFighter.obj");
	
	computeNormals();

	GLuint vertex_shader = initshaders(GL_VERTEX_SHADER, "shaders/spaceship.vert.glsl") ;
    GLuint fragment_shader = initshaders(GL_FRAGMENT_SHADER, "shaders/spaceship.frag.glsl") ;
	m_Program.init(vertex_shader, fragment_shader);

	createObjectBuffers();

	//Setting model matrix
	glm::mat4 scale_matrix, rotation_matrix, translation_matrix;

	scale_matrix = glm::scale(scale_matrix, glm::vec3(size, size, size));

	Vec3 proj_direction = Vec3(direction.getDx(), 0.0, direction.getDz());
	proj_direction.normalize();

	float forward_angle = radToDeg(acos(proj_direction * Vec3(0.0, 0.0, -1.0)));
	Vec3 forward_rot_axis = proj_direction.crossproduct(Vec3(0.0, 0.0, -1.0));

	if(!forward_rot_axis.isNullVector())
	{
		rotation_matrix = glm::rotate(rotation_matrix, -forward_angle, glm::vec3(forward_rot_axis.getDx(), forward_rot_axis.getDy(), forward_rot_axis.getDz()));
	}

	float up_angle = radToDeg(acos(direction * proj_direction));

	Vec3 up_rot_axis;
	if(direction.getDy() < 0.0)
	{
		up_rot_axis = Vec3(-1.0, 0.0, 0.0);
	}
	else
	{
		up_rot_axis = Vec3(1.0, 0.0, 0.0);
	}
	

	if(!up_rot_axis.isNullVector())
	{
		rotation_matrix = glm::rotate(rotation_matrix, up_angle, glm::vec3(up_rot_axis.getDx(), up_rot_axis.getDy(), up_rot_axis.getDz()));
	}

	translation_matrix = glm::translate(translation_matrix, glm::vec3(position.getX(), position.getY(), position.getZ()));

	setModelMatrix(translation_matrix, rotation_matrix, scale_matrix);

	m_LightingFlag = true;
}


ps::Spaceship::~Spaceship(void)
{
}

void ps::Spaceship::renderObject(void)
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	for(std::vector<SingleObject *>::iterator it_sub = m_Parts.begin(); it_sub != m_Parts.end(); it_sub++)
	{
		Material material = (*it_sub)->getMaterial();
		m_Program.setUniform("mat", material);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,(*it_sub)->getIndicesBuffer());

		glDrawElements(GL_TRIANGLES, (*it_sub)->getIndices().size(), GL_UNSIGNED_INT, 0);

	}
}
