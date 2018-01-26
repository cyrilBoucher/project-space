
#include "Sun.h"

#include "shaders.h"

ps::Sun::Sun(void)
{
}

ps::Sun::Sun(const Point3 & position, const float & width, const float & height)
	: Billboard(position, width, height)
{
	m_SunLight = new Light(position, Color(1.0, 1.0, 1.0, 1.0), Vec3(), 0);

	m_Texture.readTexture("textures/sun3.ppm");

	GLuint vertex_shader = initshaders(GL_VERTEX_SHADER, "shaders/sun.vert.glsl") ;
    GLuint fragment_shader = initshaders(GL_FRAGMENT_SHADER, "shaders/sun.frag.glsl") ;
	m_Program.init(vertex_shader, fragment_shader);
}


ps::Sun::~Sun(void)
{
}

const ps::Light * ps::Sun::getLight(void) const
{
	return m_SunLight;
}

void ps::Sun::setLight(Light * light)
{
	m_SunLight = light;
}

void ps::Sun::renderObject(void)
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[2]);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture.getTexName());

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_IndicesBuffer);

	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
}
