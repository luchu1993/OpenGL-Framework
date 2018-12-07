#include "GeometryFactory.h"

GeometryFactory::MeshData GeometryFactory::CreateBox(float width, float height, float depth)
{
    MeshData meshData;
	float w2 = width / 2, h2 = height / 2, d2 = depth / 2;

	meshData.posVec.resize(24);

	meshData.posVec[0] = glm::vec3(-w2, h2, -d2);
	meshData.posVec[1] = glm::vec3(-w2, h2, d2);
	meshData.posVec[2] = glm::vec3(w2, h2, d2);
	meshData.posVec[3] = glm::vec3(w2, h2, -d2);

	meshData.posVec[4] = glm::vec3(w2, -h2, -d2);
	meshData.posVec[5] = glm::vec3(w2, -h2, d2);
	meshData.posVec[6] = glm::vec3(-w2, -h2, d2);
	meshData.posVec[7] = glm::vec3(-w2, -h2, -d2);

	meshData.posVec[8] = glm::vec3(-w2, -h2, d2);
	meshData.posVec[9] = glm::vec3(-w2, h2, d2);
	meshData.posVec[10] = glm::vec3(-w2, h2, -d2);
	meshData.posVec[11] = glm::vec3(-w2, -h2, -d2);

	meshData.posVec[12] = glm::vec3(w2, -h2, -d2);
	meshData.posVec[13] = glm::vec3(w2, h2, -d2);
	meshData.posVec[14] = glm::vec3(w2, h2, d2);
	meshData.posVec[15] = glm::vec3(w2, -h2, d2);

	meshData.posVec[16] = glm::vec3(w2, -h2, d2);
	meshData.posVec[17] = glm::vec3(w2, h2, d2);
	meshData.posVec[18] = glm::vec3(-w2, h2, d2);
	meshData.posVec[19] = glm::vec3(-w2, -h2, d2);

	meshData.posVec[20] = glm::vec3(-w2, -h2, -d2);
	meshData.posVec[21] = glm::vec3(-w2, h2, -d2);
	meshData.posVec[22] = glm::vec3(w2, h2, -d2);
	meshData.posVec[23] = glm::vec3(w2, -h2, -d2);

	meshData.normalVec.resize(24);
	for (int i = 0; i < 4; ++i)
	{
		meshData.normalVec[i] = glm::vec3(0.0f, 1.0f, 0.0f);         
		meshData.normalVec[i + 4] = glm::vec3(0.0f, -1.0f, 0.0f);    
		meshData.normalVec[i + 8] = glm::vec3(-1.0f, 0.0f, 0.0f);    
		meshData.normalVec[i + 12] = glm::vec3(1.0f, 0.0f, 0.0f);    
		meshData.normalVec[i + 16] = glm::vec3(0.0f, 0.0f, 1.0f);    
		meshData.normalVec[i + 20] = glm::vec3(0.0f, 0.0f, -1.0f);   
	}

	meshData.indexVec = {
		0, 1, 2, 2, 3, 0,       
		4, 5, 6, 6, 7, 4,       
		8, 9, 10, 10, 11, 8,    
		12, 13, 14, 14, 15, 12, 
		16, 17, 18, 18, 19, 16, 
		20, 21, 22, 22, 23, 20  
	};

	return meshData;
}

GeometryFactory::MeshData GeometryFactory::CreateSphere(float radius, int levels, int slices)
{
    MeshData meshData;

    return meshData;
}

GeometryFactory::MeshData GeometryFactory::CreateCylinder(float radius, float height, int slices)
{
    MeshData meshData;

    return meshData;
}

GeometryFactory::MeshData GeometryFactory::CreateCylinderNoCap(float radius, float height, int slices)
{
    MeshData meshData;

    return meshData;
}