#ifndef __GEOMETRY_FACTORY_H__
#define __GEOMETRY_FACTORY_H__
#include <vector>
#include "glm/glm.hpp"

class GeometryFactory 
{
public:
    struct MeshData
    {
        std::vector<glm::vec3> posVec;
        std::vector<glm::vec3> normalVec;
        std::vector<unsigned int> indexVec;
    };

    static MeshData CreateBox(float width = 2.0f, float height = 2.0f, float depth = 2.0f);
    static MeshData CreateSphere(float radius = 1.0f, unsigned int levels = 50, unsigned int slices = 50);
    static MeshData CreateCylinder(float radius = 1.0f, float height = 2.0f, unsigned int slices = 50);
    static MeshData CreateCylinderNoCap(float radius = 1.0f, float height = 2.0f, unsigned int slices = 50);
    
private:
    GeometryFactory() = delete;
};
#endif
