#pragma once

// vendors
#define GLFW_INCLUDE_NONE
#include "GL/glew.h"
#include "GLFW/glfw3.h"
// project headers
#include "../types.hpp"
// std library

class VertexBuffer
{
public:
    // Constructors
    VertexBuffer() = default;
    // Generates a VBO and links it to a list of vertices
    VertexBuffer(std::vector<vertex>& vertices);
    VertexBuffer(std::vector<mat4x4d>& matrices);

    // Destructors
    ~VertexBuffer() { Destroy(); }

    void Bind() { glBindBuffer(GL_ARRAY_BUFFER, m_ID); }
    void Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

    void Destroy() { glDeleteBuffers(1, &(m_ID));}
    
    std::uint32_t GetID() const { return m_ID; }

private:
    std::uint32_t m_ID;
};
