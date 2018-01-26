#include "Texture2D.h"

#include <cstdio>


ps::Texture2D::Texture2D(void)
{
}


ps::Texture2D::~Texture2D(void)
{
}

const int & ps::Texture2D::getWidth(void) const
{
	return m_Width;
}

const int & ps::Texture2D::getHeight(void) const
{
	return m_Height;
}

const int & ps::Texture2D::getPixelSize(void) const
{
	return m_PixelSize;
}

const GLuint & ps::Texture2D::getTexName(void) const
{
	return m_TexName;
}

void ps::Texture2D::setData(const int & width, const int & height, const GLint & internal_format, const GLvoid* data)
{
	glBindTexture (GL_TEXTURE_2D, m_TexName) ; 
	glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, internal_format, GL_UNSIGNED_BYTE, data);
}

void ps::Texture2D::setData(const GLint & internal_format, const GLvoid* data)
{
	glBindTexture (GL_TEXTURE_2D, m_TexName) ; 
	glTexImage2D(GL_TEXTURE_2D, 0, internal_format, m_Width, m_Height, 0, internal_format, GL_UNSIGNED_BYTE, data);
}

bool ps::Texture2D::readTexture(char *filename)
{ 
    FILE *inFile; 
	char buffer[100]; 
    GLubyte *mytexture; 
	unsigned char c; 
	int maxVal;

	if( (inFile = fopen(filename, "rb")) == NULL) {
		return 0;
	}

	//Read file type identifier (magic number)
	fgets(buffer, sizeof(buffer), inFile);
	if ((buffer[0] != 'P') || (buffer[1] != '6')) {
		fprintf (stderr, "not a binary ppm file %s\n", filename);
		return 0;
	}

	if(buffer[2] == 'A')
		m_PixelSize = 4;
	else
		m_PixelSize = 3;

	//Read image size
	do fgets(buffer, sizeof (buffer), inFile);
	while (buffer[0] == '#');
	sscanf (buffer, "%d %d", &m_Width, &m_Height);

	//Read maximum pixel value (usually 255)
	do fgets (buffer, sizeof (buffer), inFile);
	while (buffer[0] == '#');
	sscanf (buffer, "%d", &maxVal);

	//Allocate RGBA texture buffer
	int memSize = m_Width * m_Height * 4 * sizeof(GLubyte);
	mytexture = new GLubyte[memSize];

	// read RGB data and set alpha value
	for (int i = 0; i < memSize; i++) {
		if ((i % 4) < 3 || m_PixelSize == 4) {
			c = fgetc(inFile);
			mytexture[i]=(GLubyte) c;
        }
		else mytexture[i] = (GLubyte) 255; //Set alpha to opaque
    }
    fclose(inFile);

	createTexture(m_Width, m_Height, GL_RGBA, mytexture);

	delete[] mytexture;
}

bool ps::Texture2D::createTexture(int width, int height, GLint internal_format, const GLvoid* texture)
{
	glGenTextures(1, &m_TexName) ; 
    glBindTexture (GL_TEXTURE_2D, m_TexName) ; 

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) ; 
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR) ;
   
    setData(internal_format, texture);

	return true;
}

bool ps::Texture2D::createTexture(int width, int height, GLint internal_format)
{
	m_Width = width;
	m_Height = height;

	return createTexture(m_Width, m_Height, internal_format, NULL);
}
