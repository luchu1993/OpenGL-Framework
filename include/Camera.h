#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Camera 
{
	struct CameraInfo
	{
		glm::vec3 cameraPos;
	};
public:
	Camera(unsigned int shaderProgram, float fov, float aspect, float scn_near, float scn_far);
	
	bool init();
	bool render();
	void cleanup();
	void resize(int width, int height);

	void setPosition(float x, float y, float z);
	void setRotation(float x, float y, float z);

	glm::mat4 getProjectionMatrix() const { return m_projMatrix; }
	glm::mat4 getViewMatrix() const { return m_viewMatrix; }

private:
	unsigned int m_shaderProgram;
	float m_fieldOfView;
	float m_aspectRatio;
	float m_screenNear;
	float m_screenFar;

	glm::vec3 m_position;
	glm::vec3 m_rotation;

	unsigned int m_cameraInfoUBO;
	unsigned int m_cameraInfoUBOIndex;
	int m_cameraInfoUBOSize;

	glm::mat4 m_projMatrix;
	glm::mat4 m_viewMatrix;
};

#endif