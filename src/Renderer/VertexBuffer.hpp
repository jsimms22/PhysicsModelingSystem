#pragma once

// vendors
#define GLFW_INCLUDE_NONE
#include "../../vendor/GL/include/glew.h"
#include "../../vendor/GLFW/include/glfw3.h"
// project headers
#include "../types.hpp"
// std library

class VertexBuffer
{
public:
    // Constructors
    VertexBuffer() = default;
    // Generates a VBO and links it to a list of vertices
    VertexBuffer(std::vector<vertexf>& vertices);
    VertexBuffer(std::vector<mat4x4f>& matrices);

    // Destructors
    ~VertexBuffer() { Destroy(); }

    void Bind() { glBindBuffer(GL_ARRAY_BUFFER, m_ID); }
    void Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

    void Destroy() { glDeleteBuffers(1, &(m_ID));}
    
    uint32_t GetID() const { return m_ID; }

private:
    uint32_t m_ID;
};
