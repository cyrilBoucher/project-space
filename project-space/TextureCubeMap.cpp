
#include "TextureCubeMap.h"
#include <string.h>
#include <string>

ps::TextureCubeMap::TextureCubeMap(void)
{
}


ps::TextureCubeMap::~TextureCubeMap(void)
{
}

const GLuint & ps::TextureCubeMap::getTexName(void) const
{
	return m_TexName;
}

bool ps::TextureCubeMap::readTexture(char *filename)
{
	if ( (filename == NULL) ||  (strlen(filename) <= 0) ) return false;

	std::string filenames[6];

	filenames[0] = std::string(filename) + "_top.ppm";
	filenames[1] = std::string(filename) + "_bottom.ppm";
	filenames[2] = std::string(filename) + "_front.ppm";
	filenames[3] = std::string(filename) + "_back.ppm";
	filenames[4] = std::string(filename) + "_left.ppm";
	filenames[5] = std::string(filename) + "_right.ppm";

	GLubyte **mytextures = new GLubyte*[6];

	for(unsigned int i = 0; i < 6; i++)
	{
		FILE *inFile; 
		char buffer[100]; 
		GLubyte *mytexture; 
		unsigned char c; 
		int maxVal;

		if( (inFile = fopen(filenames[i].c_str(), "rb")) == NULL) {
			return 0;
		}

		//Read file type identifier (magic number)
		fgets(buffer, sizeof(buffer), inFile);
		if ((buffer[0] != 'P') || (buffer[1] != '6')) {
			fprintf (stderr, "not a binary ppm file %s\n", filenames[1].c_str());
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

		mytextures[i] = mytexture;
	}

	createTexture(m_Width, m_Height, GL_RGBA, (const GLvoid**)mytextures);

	delete[] mytextures;
}

bool ps::TextureCubeMap::createTexture(int width, int height, GLint internal_format, const GLvoid** textures)
{
	glGenTextures(1, &m_TexName) ; 
	glBindTexture (GL_TEXTURE_CUBE_MAP, m_TexName) ; 

	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR) ; 
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR) ;

	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, internal_format, width, height, 0, internal_format, GL_UNSIGNED_BYTE, textures[2]);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, internal_format, width, height, 0, internal_format, GL_UNSIGNED_BYTE, textures[3]);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, internal_format, width, height, 0, internal_format, GL_UNSIGNED_BYTE, textures[1]);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, internal_format, width, height, 0, internal_format, GL_UNSIGNED_BYTE, textures[0]);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, internal_format, width, height, 0, internal_format, GL_UNSIGNED_BYTE, textures[4]);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, internal_format, width, height, 0, internal_format, GL_UNSIGNED_BYTE, textures[5]);

	return true;
}
