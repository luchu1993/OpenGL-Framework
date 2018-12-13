#include "GeometryFactory.h"
#include "glm/gtc/constants.hpp"

GeometryFactory::MeshData GeometryFactory::CreateBox(float width, float height, float depth)
{
    MeshData meshData;
	float w2 = width / 2, h2 = height / 2, d2 = depth / 2;

	meshData.position.resize(24);

	meshData.position[0] = glm::vec3(-w2, h2, -d2);
	meshData.position[1] = glm::vec3(-w2, h2, d2);
	meshData.position[2] = glm::vec3(w2, h2, d2);
	meshData.position[3] = glm::vec3(w2, h2, -d2);

	meshData.position[4] = glm::vec3(w2, -h2, -d2);
	meshData.position[5] = glm::vec3(w2, -h2, d2);
	meshData.position[6] = glm::vec3(-w2, -h2, d2);
	meshData.position[7] = glm::vec3(-w2, -h2, -d2);

	meshData.position[8] = glm::vec3(-w2, -h2, d2);
	meshData.position[9] = glm::vec3(-w2, h2, d2);
	meshData.position[10] = glm::vec3(-w2, h2, -d2);
	meshData.position[11] = glm::vec3(-w2, -h2, -d2);

	meshData.position[12] = glm::vec3(w2, -h2, -d2);
	meshData.position[13] = glm::vec3(w2, h2, -d2);
	meshData.position[14] = glm::vec3(w2, h2, d2);
	meshData.position[15] = glm::vec3(w2, -h2, d2);

	meshData.position[16] = glm::vec3(w2, -h2, d2);
	meshData.position[17] = glm::vec3(w2, h2, d2);
	meshData.position[18] = glm::vec3(-w2, h2, d2);
	meshData.position[19] = glm::vec3(-w2, -h2, d2);

	meshData.position[20] = glm::vec3(-w2, -h2, -d2);
	meshData.position[21] = glm::vec3(-w2, h2, -d2);
	meshData.position[22] = glm::vec3(w2, h2, -d2);
	meshData.position[23] = glm::vec3(w2, -h2, -d2);

	meshData.normal.resize(24);
	for (int i = 0; i < 4; ++i)
	{
		meshData.normal[i] = glm::vec3(0.0f, 1.0f, 0.0f);         
		meshData.normal[i + 4] = glm::vec3(0.0f, -1.0f, 0.0f);    
		meshData.normal[i + 8] = glm::vec3(-1.0f, 0.0f, 0.0f);    
		meshData.normal[i + 12] = glm::vec3(1.0f, 0.0f, 0.0f);    
		meshData.normal[i + 16] = glm::vec3(0.0f, 0.0f, 1.0f);    
		meshData.normal[i + 20] = glm::vec3(0.0f, 0.0f, -1.0f);   
	}

	meshData.texCoord.resize(24);
	for (int i = 0; i < 6; i++)
	{
		meshData.texCoord[i * 4] = glm::vec2(0.0f, 1.0f);
		meshData.texCoord[i * 4 + 1] = glm::vec2(0.0f, 0.0f);
		meshData.texCoord[i * 4 + 2] = glm::vec2(1.0f, 0.0f);
		meshData.texCoord[i * 4 + 3] = glm::vec2(1.0f, 1.0f);
	}

	meshData.index = {
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
	meshData.position.push_back(glm::vec3(0.0f, radius, 0.0f));
	meshData.normal.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	meshData.texCoord.push_back(glm::vec2(0.0f, 0.0f));

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
			meshData.position.push_back(pos);
			meshData.normal.push_back(normal);
			meshData.texCoord.push_back(glm::vec2(theta / glm::two_pi<float>(), phi / glm::pi<float>()));
		}
	}
	// 放入底端点
	meshData.position.push_back(glm::vec3(0.0f, -radius, 0.0f));
	meshData.normal.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	meshData.texCoord.push_back(glm::vec2(0.0f, 1.0f));

	// 逐渐放入索引
	if (levels > 1)
	{
		for (unsigned int j = 1; j <= slices + 1; ++j)
		{
			meshData.index.push_back(0);
			meshData.index.push_back(j % (slices + 1) + 1);
			meshData.index.push_back(j);

		}
	}


	for (unsigned int i = 1; i < levels - 1; ++i)
	{
		for (unsigned int j = 1; j <= slices + 1; ++j)
		{

			meshData.index.push_back((i - 1) * (slices + 1) + j);
			meshData.index.push_back((i - 1) * (slices + 1) + j % (slices + 1) + 1);
			meshData.index.push_back(i * (slices + 1) + j % (slices + 1) + 1);

			meshData.index.push_back(i * (slices + 1) + j % (slices + 1) + 1);
			meshData.index.push_back(i * (slices + 1) + j);
			meshData.index.push_back((i - 1) * (slices + 1) + j);

		}

	}

	// 逐渐放入索引
	if (levels > 1)
	{
		for (unsigned int j = 1; j <= slices; ++j)
		{
			meshData.index.push_back((levels - 2) * (slices + 1) + j);
			meshData.index.push_back((levels - 2) * (slices + 1) + j % (slices + 1) + 1);
			meshData.index.push_back(meshData.position.size() - 1);
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
	meshData.position.push_back(glm::vec3(0.0f, h2, 0.0f));
	meshData.normal.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	meshData.texCoord.push_back(glm::vec2(0.5f, 0.5f));

	// 放入顶端圆上各点
	for (unsigned int i = 0; i <= slices; ++i)
	{
		theta = i * per_theta;
		meshData.position.push_back(glm::vec3(radius * cosf(theta), h2, radius * sinf(theta)));
		meshData.normal.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
		meshData.texCoord.push_back(glm::vec2(cosf(theta) / 2 + 0.5f, sinf(theta) / 2 + 0.5f));
	}

	// 逐渐放入索引
	for (unsigned int i = 1; i <= slices; ++i)
	{
		meshData.index.push_back(offset);
		meshData.index.push_back(offset + i + 1);
		meshData.index.push_back(offset + i);
	}

	// 放入底端圆心
	meshData.position.push_back(glm::vec3(0.0f, -h2, 0.0f));
	meshData.normal.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	meshData.texCoord.push_back(glm::vec2(0.5f, 0.5f));

	// 放入底部圆上各点
	for (unsigned int i = 0; i <= slices; ++i)
	{
		theta = i * per_theta;
		meshData.position.push_back(glm::vec3(radius * cosf(theta), -h2, radius * sinf(theta)));
		meshData.normal.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
		meshData.texCoord.push_back(glm::vec2(cosf(theta) / 2 + 0.5f, sinf(theta) / 2 + 0.5f));
	}
	
	// 逐渐放入索引
	offset += (slices + 1) + 1;
	for (unsigned int i = 1; i <= slices; ++i)
	{
		meshData.index.push_back(offset);
		meshData.index.push_back(offset + i);
		meshData.index.push_back(offset + i + 1);
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
		meshData.position.push_back(glm::vec3(radius * cosf(theta), h2, radius * sinf(theta)));
		meshData.normal.push_back(glm::vec3(cosf(theta), 0.0f, sinf(theta)));
		meshData.texCoord.push_back(glm::vec2(theta / glm::two_pi<float>(), 0.0f));
	}
	// 放入侧面底端点
	for (unsigned int i = 0; i <= slices; ++i)
	{
		theta = i * per_theta;
		meshData.position.push_back(glm::vec3(radius * cosf(theta), -h2, radius * sinf(theta)));
		meshData.normal.push_back(glm::vec3(cosf(theta), 0.0f, sinf(theta)));
		meshData.texCoord.push_back(glm::vec2(theta / glm::two_pi<float>(), 1.0f));
	}

	// 放入索引
	for (unsigned int i = 0; i < slices; ++i)
	{
		meshData.index.push_back(i);
		meshData.index.push_back(i + 1);
		meshData.index.push_back((slices + 1) + i + 1);

		meshData.index.push_back((slices + 1) + i + 1);
		meshData.index.push_back((slices + 1) + i);
		meshData.index.push_back(i);
	}

	return meshData;
}