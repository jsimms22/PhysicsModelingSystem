// vendors
// project headers
#include "ElementBuffer.hpp"
// std library

ElementBuffer::ElementBuffer(std::vector<std::uint32_t> indices) 
{ 
    glGenBuffers(1, &(m_ID));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<long long int>(indices.size() * sizeof(std::uint32_t)), indices.data(), GL_STATIC_DRAW);
}