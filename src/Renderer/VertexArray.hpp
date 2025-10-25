#pragma once

// vendors
// project headers
// std library
#include <cstdint>

class VertexBuffer;

class VertexArray
{
public:
    // Constructors
    VertexArray();
    
    // Destructors
    ~VertexArray() { Destroy(); }

    // Links a VBO attribute 
    void LinkAttribute(VertexBuffer& VBO, 
                       std::uint32_t order, 
                       int layout, 
                       std::uint32_t type, 
                       int stride, 
                       void* offset);

    void Bind();
    void Unbind();
    void Destroy();
    std::uint32_t GetID() const;

private:
    std::uint32_t m_ID;
};