#pragma once
#include "object.h"

namespace ps
{
	class SingleObject :
		public Object
	{
	public:
		SingleObject(void);
		~SingleObject(void);

		std::vector<GLuint> & getIndices(void);

		const GLuint & getIndicesBuffer(void) const;
		void setIndicesBuffer(const GLuint & indices_buffer);

		const Material & getMaterial(void) const;
		void setMaterial(const Material & material);

		Texture2D & getTexture(void);
		void setTexture(const Texture2D & texture);

		virtual void readMesh(char *filename);

		virtual void computeNormals(void);

		virtual void createObjectBuffers(void);

		virtual void renderObject(void);

		bool setTexture(char* filename);

	protected:
		GLuint m_IndicesBuffer;

		std::vector<GLuint> m_Indices;

		Material m_Material;

		Texture2D m_Texture;
	};
}

