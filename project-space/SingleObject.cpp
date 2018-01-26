
#include "SingleObject.h"

#include <iostream>
#include <fstream>
#include <sstream>


ps::SingleObject::SingleObject(void)
{
	m_LightingFlag = false;
}


ps::SingleObject::~SingleObject(void)
{
}

std::vector<GLuint> & ps::SingleObject::getIndices(void)
{
	return m_Indices;
}

const GLuint & ps::SingleObject::getIndicesBuffer(void) const
{
	return m_IndicesBuffer;
}

void ps::SingleObject::setIndicesBuffer(const GLuint & indices_buffer)
{
	m_IndicesBuffer = indices_buffer;
}

const ps::Material & ps::SingleObject::getMaterial(void) const
{
	return m_Material; 
}

void ps::SingleObject::setMaterial(const Material & material)
{
	m_Material = material;
}

ps::Texture2D & ps::SingleObject::getTexture(void)
{
	return m_Texture;
}

void ps::SingleObject::setTexture(const Texture2D & texture)
{
	m_Texture = texture;
}

void ps::SingleObject::readMesh(char *filename)
{
	std::string s, t;
	std::string matfilename;
	GLfloat x;
	GLuint index;

	std::map<std::string, Material> materials;
	Material previous_material;
	
	std::ifstream fin(filename);
	if (!fin.is_open()) std::cout << "Unable to open file!\n";

	while ( getline(fin, s) )
	{
		std::stringstream myline(s);
		t = "";

		myline >> t;
		if (t == "mtllib")
		{
			myline >> matfilename;
			readMaterials(matfilename, materials);
		}
		else if(t == "usemtl")
		{
			std::string matname;

			myline >> matname;

			if(matname == "(null)")
			{
				m_Material = previous_material;
			}
			else
			{
				Material mat = materials[matname];
				m_Material = mat;
				previous_material = mat;
			}
		}
		else if (t == "v")
		{
			for(int i=0;i<3;i++)
			{
				myline >> x;
				m_Vertices.push_back(x);
			}
			while(myline >> t){ }
		}
		else if (t == "f")
		{
			std::vector<GLuint> face_indices;

			std::string vert_coords;

			while(myline >> vert_coords)
			{
				if(vert_coords.find('/') != std::string::npos)
				{
					std::string vert_index = vert_coords.substr(0, vert_coords.find('/'));

					std::stringstream myindex(vert_index);

					myindex >> index;
				}
				else
				{
					std::stringstream myindex(vert_coords);

					myindex >> index;
				}

				face_indices.push_back(index);
			}

			if(face_indices.size() > 3)
			{
				face_indices = triangulateIndices(face_indices);
			}

			for(unsigned int i=0; i < face_indices.size(); i++)
			{
				m_Indices.push_back(face_indices[i]-1);
			}	
		}
	}
}

void ps::SingleObject::computeNormals(void)
{
	if(m_Vertices.size() != 0 && m_Indices.size() != 0)
	{
		m_Normals.resize(m_Vertices.size());

		std::vector<int> nb_normals(m_Indices.size());

		for(unsigned int i = 0; i < m_Indices.size(); i += 3)
		{
			computeNormal(m_Indices[i], m_Indices[i+1], m_Indices[i+2]);

			nb_normals[m_Indices[i]]++;
			nb_normals[m_Indices[i+1]]++;
			nb_normals[m_Indices[i+2]]++;
		}

		for(unsigned int i = 0; i < m_Indices.size(); i++)
		{
			int normal_idx = m_Indices[i]*3;
			m_Normals[normal_idx] /= (float)nb_normals[m_Indices[i]];
			m_Normals[normal_idx+1] /= (float)nb_normals[m_Indices[i]];
			m_Normals[normal_idx+2] /= (float)nb_normals[m_Indices[i]];

			Vec3 tmp_normal = Vec3(m_Normals[normal_idx], m_Normals[normal_idx+1], m_Normals[normal_idx+2]);
			tmp_normal.normalize();
    
			m_Normals[normal_idx] = tmp_normal.getDx();
			m_Normals[normal_idx+1] = tmp_normal.getDy();
			m_Normals[normal_idx+2] = tmp_normal.getDz();
		}
	}
	else
	{
		printf("Couldn't compute normals : there are no vertices\n");
	}
}

void ps::SingleObject::createObjectBuffers(void)
{
	glGenBuffers(3, m_Buffers);
	glGenBuffers(1, &m_IndicesBuffer);

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
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndicesBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size()*4, &m_Indices.front(), GL_STATIC_DRAW);
	}
}

void ps::SingleObject::renderObject()
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[2]);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//m_Program.setUniform("mat", m_Material);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture.getTexName());

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_IndicesBuffer);

	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
}

bool ps::SingleObject::setTexture(char* filename)
{
	return m_Texture.readTexture(filename);
}
