#include "glad/glad.h"
#include "CubeModel.h"
#include "GeometryFactory.h"
#include <vector>

bool CubeModel::init()
{
    GeometryFactory::MeshData mesh = GeometryFactory::CreateBox();
    m_vertextCount = mesh.posVec.size();
    std::vector<VERTEX> vertices(m_vertextCount);
    for (size_t i = 0; i < m_vertextCount; ++i)
    {
		vertices[i].pos = mesh.posVec[i];
        vertices[i].normal = mesh.normalVec[i];
    }

    m_indexCount = mesh.indexVec.size();
    std::vector<unsigned int> indices(m_indexCount);
    for (size_t i = 0; i < m_indexCount; ++i)
    {
        indices[i] = mesh.indexVec[i];
    }

    glGenVertexArrays(1, &m_vertBufferObject);
    glGenBuffers(1, &m_vertBufferObject);
    glGenBuffers(1, &m_indexBufferObject);

    glBindVertexArray(m_vertexArrayObject);
	// Transfer vertex data
    glBindBuffer(GL_ARRAY_BUFFER, m_vertBufferObject);
    glBufferData(GL_ARRAY_BUFFER, m_vertextCount * sizeof(VERTEX), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	// Set vertex layout
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 6 * sizeof(float), (void *)(3 * sizeof(float))); // normalized 
	glEnableVertexAttribArray(1);

    glBindVertexArray(0);

	return true;
}

bool CubeModel::render()
{
    // Draw call
    glBindVertexArray(m_vertexArrayObject);
    glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

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
	// scale
	glm::scale(world, m_scale);
	// rotation
	glm::rotate(world, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::rotate(world, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::rotate(world, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	// translate
	glm::translate(world, m_position);

	return world;
}

void CubeModel::cleanup()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
	glDeleteBuffers(1, &m_vertBufferObject);
	glDeleteBuffers(1, &m_indexBufferObject);
}