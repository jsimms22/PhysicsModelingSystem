// vendors
// project headers
#include "../Renderer/VertexBuffer.hpp"
// std library

VertexBuffer::VertexBuffer(std::vector<vertexf>& vertices)
{
    glGenBuffers(1, &(m_ID));
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
    glBufferData(GL_ARRAY_BUFFER, static_cast<long long int>(vertices.size() * sizeof(vertexf)), vertices.data(), GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(std::vector<mat4x4f>& matrices)
{
    glGenBuffers(1, &(m_ID));
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
    glBufferData(GL_ARRAY_BUFFER, static_cast<long long int>(matrices.size() * sizeof(mat4x4f)), matrices.data(), GL_STATIC_DRAW);
}