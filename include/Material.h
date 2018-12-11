#ifndef __MATERIAL_H__
#define __MATERIAL_H__
#include "glm/glm.hpp"

struct Material
{
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	float shineness;
	static const unsigned int BindingPoint = 3;
};

#endif // !__MATERIAL_H__
