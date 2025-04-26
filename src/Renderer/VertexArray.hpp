#pragma once

// vendors
#define GLFW_INCLUDE_NONE
#include "GL/glew.h"
#include "GLFW/glfw3.h"
// project headers
#include "../types.hpp"
#include "../Renderer/VertexBuffer.hpp"
// std library

class VertexArray
{
public:
    // Constructors
    VertexArray() { glGenVertexArrays(1, &(m_ID)); }
    
    // Destructors
    ~VertexArray() { Destroy(); }

    // Links a VBO attribute 
    void LinkAttribute(VertexBuffer& VBO, 
                       std::uint32_t order, 
                       int layout, 
                       std::uint32_t type, 
                       int stride, 
                       void* offset);

    void Bind() { glBindVertexArray(m_ID); }
    void Unbind() { glBindVertexArray(0); }

    void Destroy() { glDeleteVertexArrays(1, &(m_ID)); }

    std::uint32_t GetID() const { return m_ID; }

private:
    std::uint32_t m_ID;
};