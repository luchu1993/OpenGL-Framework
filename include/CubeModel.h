#ifndef __CUBE_MODEL_H__
#define __CUBE_MODEL_H__

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Material.h"

class CubeModel
{
    struct VERTEX
    {
        glm::vec3 pos;
        glm::vec3 normal;
    };
public:
    bool init();
    bool render(Material const& mat);
	void cleanup();

	void setPosition(float x, float y, float z);
	void setRotation(float x, float y, float z);
	void setScale(float x, float y, float z);

	void resetGeometry();

	glm::mat4 getWorldMatrix() const;

private:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;

	unsigned int m_vertextCount;
	unsigned int m_indexCount;

    unsigned int m_cubeVAO;
    unsigned int m_cubeVBO;
    unsigned int m_cubeIBO;

	unsigned int m_materialUBO;
};
#endif
