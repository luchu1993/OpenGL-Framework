#include "GL/glew.h"
#include "CubeModel.h"
#include "GeometryFactory.h"
#include <vector>
#include <iostream>

void CubeModel::resetGeometry()
{
	m_position = glm::vec3(0.0f);
	m_rotation = glm::vec3(0.0f);
	m_scale = glm::vec3(1.0f);
}

bool CubeModel::init()
{
	resetGeometry();

    GeometryFactory::MeshData mesh = GeometryFactory::CreateCylinder();
    m_vertextCount = mesh.position.size();
    std::vector<VERTEX> vertices(m_vertextCount);
    for (size_t i = 0; i < m_vertextCount; ++i)
    {
		vertices[i].position = mesh.position[i];
        vertices[i].normal = mesh.normal[i];
		vertices[i].texCoord = mesh.texCoord[i];
    }

    m_indexCount = mesh.index.size();
    std::vector<unsigned int> indices(m_indexCount);
    for (size_t i = 0; i < m_indexCount; ++i)
    {
        indices[i] = mesh.index[i];
    }

    glGenVertexArrays(1, &m_cubeVAO);
    glGenBuffers(1, &m_cubeVBO);
    glGenBuffers(1, &m_cubeIBO);

    glBindVertexArray(m_cubeVAO);
	// Transfer vertex data
    glBindBuffer(GL_ARRAY_BUFFER, m_cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertextCount * sizeof(VERTEX), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_cubeIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	// Set vertex layout
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float))); 
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

    glBindVertexArray(0);

	return true;
}

bool CubeModel::render()
{
    // Draw call
    glBindVertexArray(m_cubeVAO);
    glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr);

	return true;
}

void CubeModel::setPosition(float x, float y, float z)
{
	m_position = glm::vec3(x, y, z);
}

void CubeModel::setRotation(float x, float y, float z)
{
	m_rotation = glm::vec3(x, y, z);
}

void CubeModel::setScale(float x, float y, float z)
{
	m_scale = glm::vec3(x, y, z);
}

glm::mat4 CubeModel::getWorldMatrix() const
{
	glm::mat4 world = glm::mat4(1.0f);

	glm::mat4 scaleMat(1.0f);
	scaleMat = glm::scale(scaleMat, m_scale);

	glm::mat4 rotateMat(1.0f);
	rotateMat = glm::rotate(rotateMat, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	rotateMat = glm::rotate(rotateMat, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	rotateMat = glm::rotate(rotateMat, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	glm::mat4 translateMat(1.0f);
	translateMat = glm::translate(translateMat, m_position);

	return translateMat * rotateMat * scaleMat;
}

void CubeModel::cleanup()
{
	glDeleteVertexArrays(1, &m_cubeVAO);
	glDeleteBuffers(1, &m_cubeVBO);
	glDeleteBuffers(1, &m_cubeIBO);
	glDeleteBuffers(1, &m_materialUBO);
}