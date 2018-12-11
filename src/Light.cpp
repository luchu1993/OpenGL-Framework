#include "GL/glew.h"
#include "Light.h"

bool DirectionalLight::init()
{
	glGenBuffers(1, &m_dirLightUBO);
	glBindBufferBase(GL_UNIFORM_BUFFER, ub_DirectionalLight::BindingPoint, m_dirLightUBO);
	
	return true;
}

bool DirectionalLight::render()
{
	// send dirLight settings to GPU
	glBindBuffer(GL_UNIFORM_BUFFER, m_dirLightUBO);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(m_dirLight), &m_dirLight, GL_STATIC_DRAW);

	return true;
}

void DirectionalLight::cleanup()
{
	glDeleteBuffers(1, &m_dirLightUBO);
}

void DirectionalLight::setAmbient(float r, float g, float b)
{
	m_dirLight.ambient = glm::vec4(r, g, b, 1.0f);
}

void DirectionalLight::setDiffuse(float r, float g, float b)
{
	m_dirLight.diffuse = glm::vec4(r, g, b, 1.0f);
}

void DirectionalLight::setSpecular(float r, float g, float b)
{
	m_dirLight.specular = glm::vec4(r, g, b, 1.0f);
}

void DirectionalLight::setDirection(float x, float y, float z)
{
	m_dirLight.direction = glm::vec3(x, y, z);
}

bool PointLight::init()
{
	glGenBuffers(1, &m_pointLightUBO);
	glBindBufferBase(GL_UNIFORM_BUFFER, ub_PointLight::BindingPoint, m_pointLightUBO);

	return true;
}

bool PointLight::render()
{
	// send point light settings to GPU
	glBindBuffer(GL_UNIFORM_BUFFER, m_pointLightUBO);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ub_PointLight), &m_pointLight, GL_STATIC_DRAW);

	return true;
}

void PointLight::cleanup()
{
	glDeleteBuffers(1, &m_pointLightUBO);
}

void PointLight::setAmbient(float r, float g, float b)
{
	m_pointLight.ambient = glm::vec4(r, g, b, 1.0f);
}

void PointLight::setDiffuse(float r, float g, float b)
{
	m_pointLight.diffuse = glm::vec4(r, g, b, 1.0f);
}

void PointLight::setSpecular(float r, float g, float b)
{
	m_pointLight.specular = glm::vec4(r, g, b, 1.0f);
}

void PointLight::setPosition(float x, float y, float z)
{
	m_pointLight.position = glm::vec3(x, y, z);
}

void PointLight::setAttenuation(float a0, float a1, float a2)
{
	m_pointLight.attenuation = glm::vec3(a0, a1, a2);
}

void PointLight::setRange(float range)
{
	m_pointLight.range = range;
}