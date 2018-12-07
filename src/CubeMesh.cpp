#include "glad/glad.h"
#include "CubeMesh.h"
#include "GeometryFactory.h"
#include <vector>

bool CubeMesh::init()
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
    glBindBuffer(GL_ARRAY_BUFFER, m_vertBufferObject);
    glBufferData(GL_ARRAY_BUFFER, m_vertextCount * sizeof(VERTEX), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    glBindVertexArray(0);
}

bool CubeMesh::render()
{
    // Draw call
    glBindVertexArray(m_vertexArrayObject);
    glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}