#include "GL/glew.h"
#include "Camera.h"

Camera::Camera(unsigned int shaderProgram, float fov, float aspect, float scn_near, float scn_far)
	: m_shaderProgram(shaderProgram)
	, m_fieldOfView(fov)
	, m_aspectRatio(aspect)
	, m_screenNear(scn_near)
	, m_screenFar(scn_far)
{

}

bool Camera::init()
{
	m_position = glm::vec3(0.0f);
	m_rotation = glm::vec3(0.0f);

	return true;
}

void Camera::setPosition(float x, float y, float z)
{
	m_position = glm::vec3(x, y, z);
}

void Camera::setRotation(float x, float y, float z)
{
	m_rotation = glm::vec3(x, y, z);
}

bool Camera::render()
{
	// projection matrix
	m_projMatrix = glm::perspective(glm::radians(m_fieldOfView), m_aspectRatio, m_screenNear, m_screenFar);

	// view matrix
	glm::vec4 _up(0.0f, 1.0f, 0.0f, 0.0f);
	glm::vec4 _lookAt(0.0f, 0.0f, -1.0f, 0.0f);

	glm::mat4 rotate = glm::mat4(1.0f);
	rotate = glm::rotate(rotate, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	rotate = glm::rotate(rotate, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	rotate = glm::rotate(rotate, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	glm::vec3 up = rotate * _up;
	glm::vec3 lookAt = rotate * _lookAt;

	lookAt += m_position;
	m_viewMatrix = glm::lookAt(m_position, lookAt, up);

	glUseProgram(m_shaderProgram);
	int eyePosWLoc = glGetUniformLocation(m_shaderProgram, "eyePosW");
	glUniform3fv(eyePosWLoc, 1, glm::value_ptr(m_position));

	return true;
}

void Camera::cleanup()
{

}

void Camera::resize(int width, int height)
{
	m_aspectRatio = static_cast<float>(width) / static_cast<float>(height);
}