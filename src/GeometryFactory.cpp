#include "GeometryFactory.h"
#include "glm/gtc/constants.hpp"

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

GeometryFactory::MeshData GeometryFactory::CreateSphere(float radius, unsigned int levels, unsigned int slices)
{
	MeshData meshData;
	float phi = 0.0f, theta = 0.0f;
	float per_phi = glm::pi<float>()/ levels;
	float per_theta = glm::two_pi<float>() / slices;
	float x, y, z;

	// 放入顶端点
	meshData.posVec.push_back(glm::vec3(0.0f, radius, 0.0f));
	meshData.normalVec.push_back(glm::vec3(0.0f, 1.0f, 0.0f));

	for (unsigned int i = 1; i < levels; ++i)
	{
		phi = per_phi * i;
		// 需要slices + 1个顶点是因为 起点和终点需为同一点，但纹理坐标值不一致
		for (unsigned int j = 0; j <= slices; ++j)
		{
			theta = per_theta * j;
			x = radius * sinf(phi) * cosf(theta);
			y = radius * cosf(phi);
			z = radius * sinf(phi) * sinf(theta);
			// 计算出局部坐标、法向量和纹理坐标
			glm::vec3 pos = glm::vec3(x, y, z);
			glm::vec3 normal = glm::normalize(pos);
			meshData.posVec.push_back(pos);
			meshData.normalVec.push_back(normal);
		}
	}
	// 放入底端点
	meshData.posVec.push_back(glm::vec3(0.0f, -radius, 0.0f));
	meshData.normalVec.push_back(glm::vec3(0.0f, -1.0f, 0.0f));

	// 逐渐放入索引
	if (levels > 1)
	{
		for (unsigned int j = 1; j <= slices + 1; ++j)
		{
			meshData.indexVec.push_back(0);
			meshData.indexVec.push_back(j % (slices + 1) + 1);
			meshData.indexVec.push_back(j);

		}
	}


	for (unsigned int i = 1; i < levels - 1; ++i)
	{
		for (unsigned int j = 1; j <= slices + 1; ++j)
		{

			meshData.indexVec.push_back((i - 1) * (slices + 1) + j);
			meshData.indexVec.push_back((i - 1) * (slices + 1) + j % (slices + 1) + 1);
			meshData.indexVec.push_back(i * (slices + 1) + j % (slices + 1) + 1);

			meshData.indexVec.push_back(i * (slices + 1) + j % (slices + 1) + 1);
			meshData.indexVec.push_back(i * (slices + 1) + j);
			meshData.indexVec.push_back((i - 1) * (slices + 1) + j);

		}

	}

	// 逐渐放入索引
	if (levels > 1)
	{
		for (unsigned int j = 1; j <= slices; ++j)
		{
			meshData.indexVec.push_back((levels - 2) * (slices + 1) + j);
			meshData.indexVec.push_back((levels - 2) * (slices + 1) + j % (slices + 1) + 1);
			meshData.indexVec.push_back(meshData.posVec.size() - 1);
		}
	}

	return meshData;
}

GeometryFactory::MeshData GeometryFactory::CreateCylinder(float radius, float height, unsigned int slices)
{
	MeshData meshData = CreateCylinderNoCap(radius, height, slices);
	float h2 = height / 2;
	float theta = 0.0f;
	float per_theta = glm::two_pi<float>() / slices;

	unsigned int offset = 2 * (slices + 1);
	// 放入顶端圆心
	meshData.posVec.push_back(glm::vec3(0.0f, h2, 0.0f));
	meshData.normalVec.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	// 放入顶端圆上各点
	for (unsigned int i = 0; i <= slices; ++i)
	{
		theta = i * per_theta;
		meshData.posVec.push_back(glm::vec3(radius * cosf(theta), h2, radius * sinf(theta)));
		meshData.normalVec.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	}
	// 逐渐放入索引
	for (unsigned int i = 1; i <= slices; ++i)
	{
		meshData.indexVec.push_back(offset);
		meshData.indexVec.push_back(offset + i % (slices + 1) + 1);
		meshData.indexVec.push_back(offset + i);
	}


	// 放入底部圆上各点
	for (unsigned int i = 0; i <= slices; ++i)
	{
		theta = i * per_theta;
		meshData.posVec.push_back(glm::vec3(radius * cosf(theta), -h2, radius * sinf(theta)));
		meshData.normalVec.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	}
	// 放入底端圆心
	meshData.posVec.push_back(glm::vec3(0.0f, -h2, 0.0f));
	meshData.normalVec.push_back(glm::vec3(0.0f, -1.0f, 0.0f));

	// 逐渐放入索引
	offset += (slices + 1) + 1;
	for (unsigned int i = 1; i <= slices; ++i)
	{
		meshData.indexVec.push_back(offset);
		meshData.indexVec.push_back(offset + i);
		meshData.indexVec.push_back(offset + i % (slices + 1) + 1);
	}

	return meshData;
}

GeometryFactory::MeshData GeometryFactory::CreateCylinderNoCap(float radius, float height, unsigned int slices)
{
	MeshData meshData;
	float h2 = height / 2;
	float theta = 0.0f;
	float per_theta = glm::two_pi<float>() / slices;

	// 放入侧面顶端点
	for (unsigned int i = 0; i <= slices; ++i)
	{
		theta = i * per_theta;
		meshData.posVec.push_back(glm::vec3(radius * cosf(theta), h2, radius * sinf(theta)));
		meshData.normalVec.push_back(glm::vec3(cosf(theta), 0.0f, sinf(theta)));
	}
	// 放入侧面底端点
	for (unsigned int i = 0; i <= slices; ++i)
	{
		theta = i * per_theta;
		meshData.posVec.push_back(glm::vec3(radius * cosf(theta), -h2, radius * sinf(theta)));
		meshData.normalVec.push_back(glm::vec3(cosf(theta), 0.0f, sinf(theta)));
	}

	// 放入索引
	for (unsigned int i = 0; i < slices; ++i)
	{
		meshData.indexVec.push_back(i);
		meshData.indexVec.push_back(i + 1);
		meshData.indexVec.push_back((slices + 1) + i + 1);

		meshData.indexVec.push_back((slices + 1) + i + 1);
		meshData.indexVec.push_back((slices + 1) + i);
		meshData.indexVec.push_back(i);
	}

	return meshData;
}