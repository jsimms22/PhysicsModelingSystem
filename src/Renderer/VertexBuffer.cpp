// vendors
#define GLFW_INCLUDE_NONE
#include "../../vendor/GL/include/GL/glew.h"
#include "../../vendor/GLFW/include/GLFW/glfw3.h"
// project headers
#include "VertexBuffer.hpp"

#include "../Types/vertex.hpp"
// std library

VertexBuffer::VertexBuffer(std::vector<vertex>& vertices)
{
    glGenBuffers(1, &(m_ID));
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
    glBufferData(GL_ARRAY_BUFFER, static_cast<long long int>(vertices.size() * sizeof(vertex)), vertices.data(), GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(std::vector<mat4x4d>& matrices)
{
    glGenBuffers(1, &(m_ID));
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
    glBufferData(GL_ARRAY_BUFFER, static_cast<long long int>(matrices.size() * sizeof(mat4x4d)), matrices.data(), GL_STATIC_DRAW);
}

void VertexBuffer::Bind() { glBindBuffer(GL_ARRAY_BUFFER, m_ID); }

void VertexBuffer::Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

void VertexBuffer::Destroy() { glDeleteBuffers(1, &(m_ID));}

std::uint32_t VertexBuffer::GetID() const { return m_ID; }