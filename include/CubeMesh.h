#ifndef __CUBE_MESH_H__
#define __CUBE_MESH_H__

#include "glm/glm.hpp"

class CubeMesh 
{
    struct VERTEX
    {
        glm::vec3 pos;
        glm::vec3 normal;
    };
public:
    bool init();
    bool render();

private:
    unsigned int m_vertexArrayObject;
    unsigned int m_vertBufferObject;
    unsigned int m_indexBufferObject;
    unsigned int m_vertextCount;
    unsigned int m_indexCount;
};
#endif
