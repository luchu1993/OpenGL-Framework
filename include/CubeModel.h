#ifndef __CUBE_MODEL_H__
#define __CUBE_MODEL_H__

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class CubeModel
{
    struct VERTEX
    {
        glm::vec3 pos;
        glm::vec3 normal;
    };
public:
    bool init();
    bool render();
	void cleanup();

	void setPosition(float x, float y, float z);
	void setRotation(float x, float y, float z);
	void setScale(float x, float y, float z);

	glm::mat4 getWorldMatrix() const;

private:
	glm::vec3 m_position = glm::vec3(0.0f);
	glm::vec3 m_rotation = glm::vec3(0.0f);
	glm::vec3 m_scale = glm::vec3(1.0f);
	unsigned int m_vertextCount;
	unsigned int m_indexCount;

    unsigned int m_vertexArrayObject;
    unsigned int m_vertBufferObject;
    unsigned int m_indexBufferObject;
};
#endif
