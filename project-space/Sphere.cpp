
#include "Sphere.h"


ps::Sphere::Sphere(void)
{
}

ps::Sphere::Sphere(const Point3 & position, const float & radius)
	: SingleObject()
{
	readMesh("objects/sphere.obj");

	//Setting model matrix
	glm::mat4 scale_matrix, rotation_matrix, translation_matrix;

	scale_matrix = glm::scale(scale_matrix, glm::vec3(radius, radius, radius));

	translation_matrix = glm::translate(translation_matrix, glm::vec3(position.getX(), position.getY(), position.getZ()));

	setModelMatrix(translation_matrix, rotation_matrix, scale_matrix);
}


ps::Sphere::~Sphere(void)
{
}
