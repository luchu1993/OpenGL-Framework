#ifndef __GEOMETRY_FACTORY_H__
#define __GEOMETRY_FACTORY_H__
#include <vector>
#include "glm/glm.hpp"

class GeometryFactory 
{
public:
    struct MeshData
    {
        std::vector<glm::vec3> position;
        std::vector<glm::vec3> normal;
		std::vector<glm::vec2> texCoord;
        std::vector<unsigned int> index;
    };

    static MeshData CreateBox(float width = 2.0f, float height = 2.0f, float depth = 2.0f);
    static MeshData CreateSphere(float radius = 1.0f, unsigned int levels = 20, unsigned int slices = 20);
    static MeshData CreateCylinder(float radius = 1.0f, float height = 2.0f, unsigned int slices = 20);
    static MeshData CreateCylinderNoCap(float radius = 1.0f, float height = 2.0f, unsigned int slices = 20);
    
private:
    GeometryFactory() = delete;
};
#endif
