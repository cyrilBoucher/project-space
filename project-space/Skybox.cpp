
#include "Skybox.h"

#include "shaders.h"

ps::Skybox::Skybox(void)
	: Cube()
{
	m_Texture.readTexture("textures/jajspace1");

	GLuint vertex_shader = initshaders(GL_VERTEX_SHADER, "shaders/skybox.vert.glsl") ;
    GLuint fragment_shader = initshaders(GL_FRAGMENT_SHADER, "shaders/skybox.frag.glsl") ;
	m_Program.init(vertex_shader, fragment_shader);

	createObjectBuffers();
}

ps::Skybox::Skybox(const GLfloat & size)
	: Cube()
{
	m_Texture.readTexture("textures/jajspace1");

	GLuint vertex_shader = initshaders(GL_VERTEX_SHADER, "shaders/skybox.vert.glsl") ;
    GLuint fragment_shader = initshaders(GL_FRAGMENT_SHADER, "shaders/skybox.frag.glsl") ;
	m_Program.init(vertex_shader, fragment_shader);

	createObjectBuffers();

	//Setting model matrix
	glm::mat4 scale_matrix, rotation_matrix, translation_matrix;

	scale_matrix = glm::scale(scale_matrix, glm::vec3(size, size, size));

	setModelMatrix(translation_matrix, rotation_matrix, scale_matrix);
}


ps::Skybox::~Skybox(void)
{
}

void ps::Skybox::renderObject(void)
{
	glDepthMask(GL_FALSE);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_Texture.getTexName());

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_IndicesBuffer);

	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);

	glDepthMask(GL_TRUE);
}
