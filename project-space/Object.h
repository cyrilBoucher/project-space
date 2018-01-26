#pragma once

#include "project-space/project-space-export.h"
#include "Material.h"
#include "Texture2D.h"
#include "Program.h"

#include <map>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <vector>

namespace ps
{
	class PROJECT_SPACE_EXPORT Object
	{
	public:
		std::vector<GLfloat>& getVertices(void);
		std::vector<GLfloat>& getNormals(void);
		std::vector<GLfloat>& getTexCoords(void);

		void setLightingFlag(const bool & flag);
		const bool & receivesLighting(void);

		glm::mat4 & getModelMatrix(void);
		void setModelMatrix(const glm::mat4 & model_matrix);
		void setModelMatrix(const glm::mat4 & third_matrix, const glm::mat4 & second_matrix, const glm::mat4 & first_matrix);
		void setModelMatrix(const std::vector<glm::mat4> & transformation_matrices);

		Program & getProgram(void);
		void setProgram(const Program & program);

		void clear(void);
 
		virtual void readMesh(char *filename);

		void readMaterials(std::string filename, std::map<std::string, Material> & materials);

		std::vector<GLuint> triangulateIndices(std::vector<GLuint> indices);

		void computeNormal(int i1, int i2, int i3, Vec3 & normal);

		virtual void computeNormals(void);

		void computeCylinderTextureCoordinates();

		void computeSphericalTextureCoordinates(float sphere_radius);

		void computePlaneTextureCoordinates();

		virtual void createObjectBuffers();

		virtual void renderObject();

	protected:
		GLuint m_Buffers[3];

		std::vector<GLfloat> m_Vertices;
		std::vector<GLfloat> m_Normals;
		std::vector<GLfloat> m_TexCoords;

		bool m_LightingFlag;

		glm::mat4 m_ModelMatrix;

		Program m_Program;

		void computeNormal(int i1, int i2, int i3);

	private:
	};
}

