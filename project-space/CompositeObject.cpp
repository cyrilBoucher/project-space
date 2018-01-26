
#include "CompositeObject.h"

#include <iostream>
#include <fstream>
#include <sstream>


ps::CompositeObject::CompositeObject(void)
{
	m_LightingFlag = false;
}


ps::CompositeObject::~CompositeObject(void)
{
}

void ps::CompositeObject::readMesh(char *filename)
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
		else if ( t == "g" )	
		{
			//SubObject * mysub = new SubObject();
			//m_Parts.push_back(mysub);
		}
		else if(t == "usemtl")
		{
			SingleObject * mysub = new SingleObject();
			m_Parts.push_back(mysub);

			std::string matname;

			myline >> matname;

			if(matname == "(null)")
			{
				m_Parts[m_Parts.size()-1]->setMaterial(previous_material);
			}
			else
			{
				Material mat = materials[matname];
				m_Parts[m_Parts.size()-1]->setMaterial(mat);
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

			for(unsigned int i = 0; i < face_indices.size(); i++)
			{
				m_Parts[m_Parts.size()-1]->getIndices().push_back(face_indices[i]-1);
			}	
		}
	}
}

void ps::CompositeObject::computeNormals(void)
{
	if(m_Vertices.size() != 0)
	{
		m_Normals.resize(m_Vertices.size());

		int parts_size = 0;

		for(std::vector<SingleObject *>::iterator it_sub = m_Parts.begin(); it_sub != m_Parts.end(); it_sub++)
		{
			parts_size += (*it_sub)->getIndices().size();
		}

		std::vector<int> nb_normals(parts_size);

		for(std::vector<SingleObject *>::iterator it_sub = m_Parts.begin(); it_sub != m_Parts.end(); it_sub++)
		{
			const std::vector<GLuint> & indices = (*it_sub)->getIndices();

			nb_normals.resize(nb_normals.size()+indices.size());

			for(unsigned int i = 0; i < indices.size(); i+=3)
			{
				computeNormal(indices[i], indices[i+1], indices[i+2]);

				nb_normals[indices[i]]++;
				nb_normals[indices[i+1]]++;
				nb_normals[indices[i+2]]++;
			}
		}

		for(std::vector<SingleObject *>::iterator it_sub = m_Parts.begin(); it_sub != m_Parts.end(); it_sub++)
		{
			const std::vector<GLuint> & indices = (*it_sub)->getIndices();

			for(unsigned int i = 0; i < indices.size(); i++)
			{
				int normal_idx = indices[i]*3;
				m_Normals[normal_idx] /= (float)nb_normals[indices[i]];
				m_Normals[normal_idx+1] /= (float)nb_normals[indices[i]];
				m_Normals[normal_idx+2] /= (float)nb_normals[indices[i]];

				Vec3 tmp_normal = Vec3(m_Normals[normal_idx], m_Normals[normal_idx+1], m_Normals[normal_idx+2]);
				tmp_normal.normalize();
    
				m_Normals[normal_idx] = tmp_normal.getDx();
				m_Normals[normal_idx+1] = tmp_normal.getDy();
				m_Normals[normal_idx+2] = tmp_normal.getDz();
			}
		}
	}
}

void ps::CompositeObject::createObjectBuffers(void)
{
	glGenBuffers(3, m_Buffers);

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
	for(std::vector<SingleObject *>::iterator it_sub = m_Parts.begin(); it_sub != m_Parts.end(); it_sub++)
	{
		GLuint indices_buffer;
		const std::vector<GLuint> & indices = (*it_sub)->getIndices();

		glGenBuffers(1, &indices_buffer);

		if(!indices.empty())
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_buffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*4, &indices.front(), GL_STATIC_DRAW);
			(*it_sub)->setIndicesBuffer(indices_buffer);
		}
	}
}

void ps::CompositeObject::renderObject(void)
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

	for(std::vector<SingleObject *>::iterator it_sub = m_Parts.begin(); it_sub != m_Parts.end(); it_sub++)
	{
		Material material = (*it_sub)->getMaterial();
		m_Program.setUniform("mat", material);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, (*it_sub)->getTexture().getTexName());

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,(*it_sub)->getIndicesBuffer());

		glDrawElements(GL_TRIANGLES, (*it_sub)->getIndices().size(), GL_UNSIGNED_INT, 0);

	}
}

void ps::CompositeObject::setTextures(std::map<GLuint, Texture2D> textures)
{
	for(std::map<GLuint, Texture2D>::iterator it_tex = textures.begin(); it_tex != textures.end(); it_tex++)
	{
		m_Parts[(*it_tex).first]->setTexture((*it_tex).second);
	}
}
