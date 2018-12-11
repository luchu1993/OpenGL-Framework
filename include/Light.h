#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "glm/glm.hpp"

class DirectionalLight
{
	struct ub_DirectionalLight
	{
		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;
		glm::vec3 direction;
		float pad;

		static const unsigned int BindingPoint = 1;
	};
public:
	bool init();
	bool render();
	void cleanup();

	void setAmbient(float r, float g, float b);
	void setDiffuse(float r, float g, float b);
	void setSpecular(float r, float g, float b);
	void setDirection(float x, float y, float z);

	glm::vec3 getDirection() const { return m_dirLight.direction; }

private:
	ub_DirectionalLight m_dirLight;
	unsigned int m_dirLightUBO;
};


class PointLight
{
	struct ub_PointLight
	{
		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;
		glm::vec3 position;
		float pad0;
		glm::vec3 attenuation;
		float range;

		static const unsigned int BindingPoint = 2;
	};

public:
	bool init();
	bool render();
	void cleanup();

	void setAmbient(float r, float g, float b);
	void setDiffuse(float r, float g, float b);
	void setSpecular(float r, float g, float b);
	void setPosition(float x, float y, float z);
	void setAttenuation(float a0, float a1, float a2);
	void setRange(float range);

private:
	unsigned int m_pointLightUBO;
	ub_PointLight m_pointLight;
};
#endif
