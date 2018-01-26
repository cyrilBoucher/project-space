
#include "Object.h"

#include "trig.h"

#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>

//Constructors and destructors
//Abstract class

//Getters and setters
std::vector<GLfloat>& ps::Object::getVertices(void)
{
	return m_Vertices;
}

std::vector<GLfloat>& ps::Object::getNormals(void)
{
	return m_Normals;
}
std::vector<GLfloat>& ps::Object::getTexCoords(void)
{
	return m_TexCoords;
}

void ps::Object::setLightingFlag(const bool & flag)
{
	m_LightingFlag = flag;
}

const bool & ps::Object::receivesLighting(void)
{
	return m_LightingFlag;
}

glm::mat4 & ps::Object::getModelMatrix(void)
{
	return m_ModelMatrix;
}

void ps::Object::setModelMatrix(const glm::mat4 & model_matrix)
{
	m_ModelMatrix = model_matrix;
}

void ps::Object::setModelMatrix(const glm::mat4 & third_matrix, const glm::mat4 & second_matrix, const glm::mat4 & first_matrix)
{
	m_ModelMatrix = third_matrix * second_matrix * first_matrix;
}

void ps::Object::setModelMatrix(const std::vector<glm::mat4> & transformation_matrices)
{
	for(std::vector<glm::mat4>::const_iterator it_mat = transformation_matrices.begin(); it_mat != transformation_matrices.end(); it_mat++)
	{
		m_ModelMatrix = m_ModelMatrix * (*it_mat);
	}
}

ps::Program & ps::Object::getProgram(void)
{
	return m_Program;
}

void ps::Object::setProgram(const ps::Program & program)
{
	m_Program = program;
}

void ps::Object::clear(void) {
}
 
void ps::Object::readMesh(char *filename)
{
}

void ps::Object::readMaterials(std::string filename, std::map<std::string, Material> & materials)
{
	std::string s, t;
	std::string matname;

	std::ifstream fin("objects/" + filename);
	if (!fin.is_open()) std::cout << "Unable to open file!\n";

	while ( getline(fin, s) )
	{
		std::stringstream myline(s);
		t = "";

		myline >> t;
		if (t == "newmtl")
		{
			Material material;
			myline >> matname;

			materials[matname] = material;

		}
		else if(t == "Kd")
		{
			GLfloat kd_c[3];
			for(int i=0;i<3;i++)
			{
				myline >> kd_c[i];
			}

			materials[matname].setKd(Color(kd_c[0], kd_c[1], kd_c[2], 1.0f));
		}
		else if(t == "Ka")
		{
			GLfloat ka_c[3];
			for(int i=0;i<3;i++)
			{
				myline >> ka_c[i];
			}

			materials[matname].setKa(Color(ka_c[0], ka_c[1], ka_c[2], 1.0f));
		}
		else if(t == "Ks")
		{
			GLfloat ks_c[3];
			for(int i=0;i<3;i++)
			{
				myline >> ks_c[i];
			}

			materials[matname].setKs(Color(ks_c[0], ks_c[1], ks_c[2], 1.0f));
		}
		else if(t == "Ns")
		{
			GLfloat sh;
			myline >> sh;
			materials[matname].setSh(sh);
		}
	}
}

std::vector<GLuint> ps::Object::triangulateIndices(std::vector<GLuint> indices)
{
	std::vector<GLuint> new_indices;

	int nb_triangles = (indices.size() - 3) + 1;
	int offset = 0;

	for(int i = 0; i < nb_triangles; i++)
	{
		new_indices.push_back(indices[0]);
		new_indices.push_back(indices[offset+1]);
		new_indices.push_back(indices[offset+2]);

		offset++;
	}

	return new_indices;
}

void ps::Object::computeNormal(int i1, int i2, int i3, Vec3 & normal)
{
	//Computes the cross product between two vectors of a face to get the normal
	int vert_index;

	vert_index = i1*3;
	Point3 p1 = Point3(m_Vertices[vert_index], m_Vertices[vert_index+1], m_Vertices[vert_index+2]);

	vert_index = i2*3;
	Point3 p2 = Point3(m_Vertices[vert_index], m_Vertices[vert_index+1], m_Vertices[vert_index+2]);

	vert_index = i3*3;
	Point3 p3 = Point3(m_Vertices[vert_index], m_Vertices[vert_index+1], m_Vertices[vert_index+2]);

	Vec3 v1 = p2 - p1;
	Vec3 v2 = p3 - p1;

	// Cross product between v1 and v2
	normal = v1 ^ v2;

	//Normalizes the vector
	normal.normalize();
}

void ps::Object::computeNormal(int i1, int i2, int i3)
{
	if(m_Normals.size() != 0)
	{
		int normal_index;
		Vec3 normal;

		computeNormal(i1, i2, i3, normal);

		normal_index = i1*3;
		m_Normals[normal_index] = normal.getDx();
		m_Normals[normal_index+1] = normal.getDy();
		m_Normals[normal_index+2] = normal.getDz();

		normal_index = i2*3;
		m_Normals[normal_index] = normal.getDx();
		m_Normals[normal_index+1] = normal.getDy();
		m_Normals[normal_index+2] = normal.getDz();

		normal_index = i3*3;
		m_Normals[normal_index] = normal.getDx();
		m_Normals[normal_index+1] = normal.getDy();
		m_Normals[normal_index+2] = normal.getDz();
	}
}

void ps::Object::computeNormals(void)
{
	
}

/*bool ps::Object::setTexture(char* filename)
{
	return m_Texture.readTexture(filename);
	bool result = false;

	for(std::vector<SubObject *>::iterator it_sub = m_Parts.begin(); it_sub != m_Parts.end(); it_sub++)
	{
		if((*it_sub)->getIndices().size() != 0)
		{
			result = (*it_sub)->getTexture().readTexture(filename);

			if(result == false)
			{
				return result;
			}
		}
	}

	return result;
}*/

void ps::Object::computeCylinderTextureCoordinates()
{
	unsigned int nb_vertices = m_Vertices.size()/3;

	m_TexCoords.resize(2*nb_vertices);
	GLfloat x, y, z;
	for (int i = 0; i < nb_vertices; i++)
	{
		x = m_Vertices[3*i]; y = m_Vertices[3*i+1]; z = m_Vertices[3*i+2];
	
		m_TexCoords[2*i] = z;

		if ( y>=0.0f )
		{
			m_TexCoords[2*i+1] = atan2(  y,  x ) / (PI) ;
		}
		else if ( y<0.0f )  
		{
			m_TexCoords[2*i+1] = (- atan2(  y,  x )) / (PI) ;
		}

		//this has problems at the seam, when 1->0 and so interpoltion results in the whole image squeezed between the two border vertices.
		//if ( y>=0.0f )     textures[2*i+1] = atan2(  y,  x ) / (2*PI) ;
		//else if ( y<0.0f )  textures[2*i+1] = (2*PI + atan2(  y,  x )) / (2*PI) ;
	}
}

void ps::Object::computeSphericalTextureCoordinates(float sphere_radius)
{
	unsigned int nb_vertices = m_Vertices.size()/3;

	m_TexCoords.resize(2*nb_vertices);
	GLfloat x, y, z;
	for (int i = 0; i < nb_vertices; i++)
	{
		x = m_Vertices[3*i]; y = m_Vertices[3*i+1]; z = m_Vertices[3*i+2];
	
		m_TexCoords[2*i] = (1.0f- atan2(  z,  x ) / (2*PI)) ; // Longitude
		m_TexCoords[2*i+1] = acos( y / sphere_radius) / (PI); // Latitude

		//this has problems at the seam, when 1->0 and so interpoltion results in the whole image squeezed between the two border vertices.
		//if ( y>=0.0f )     textures[2*i+1] = atan2(  y,  x ) / (2*PI) ;
		//else if ( y<0.0f )  textures[2*i+1] = (2*PI + atan2(  y,  x )) / (2*PI) ;
	}
}

void ps::Object::computePlaneTextureCoordinates()
{
	//unsigned int nb_vertices = vertices.size()/3;

	//texture_coords.resize(2*nb_vertices);
	//GLfloat x, y, z;
	//for (int i = 0; i < nb_vertices; i++)
	//{
	//	x = vertices[3*i]; y = vertices[3*i+1]; z = vertices[3*i+2];
	
	//	texture_coords[2*i] = (1.0f- atan2(  z,  x ) / (2*PI)) ;
	//	texture_coords[2*i+1] = acos( y / sphere_radius) / (PI);

	//	//this has problems at the seam, when 1->0 and so interpoltion results in the whole image squeezed between the two border vertices.
	//	//if ( y>=0.0f )     textures[2*i+1] = atan2(  y,  x ) / (2*PI) ;
	//	//else if ( y<0.0f )  textures[2*i+1] = (2*PI + atan2(  y,  x )) / (2*PI) ;
	//}
}

void ps::Object::createObjectBuffers()
{
	/*glGenBuffers(4, m_Buffers);

	// Vertices
	if(!m_Vertices.empty())
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[0]);
		glBufferData(GL_ARRAY_BUFFER, m_Vertices.size()*4, &m_Vertices.front(), GL_STATIC_DRAW);
	}

	// Normals
	if(!m_Normals.empty())
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[1]);
		glBufferData(GL_ARRAY_BUFFER, m_Normals.size()*4, &m_Normals.front(), GL_STATIC_DRAW);
	}

	// Texture coordinates
	if(!m_TexCoords.empty())
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[2]);
		glBufferData(GL_ARRAY_BUFFER, m_TexCoords.size()*4, &m_TexCoords.front(), GL_STATIC_DRAW);
	}

	// Indices
	if(!m_Indices.empty())
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffers[3]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size()*4, &m_Indices.front(), GL_STATIC_DRAW);
	}*/
}

void ps::Object::renderObject()
{
	/*glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[2]);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	m_Program.setUniform("mat", m_Material);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture.getTexName());

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_Buffers[3]);

	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);*/ 
}
