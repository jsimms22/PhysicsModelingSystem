#pragma once

// vendors
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// project headers
// std library
#include <cstdint>
#include <vector>

class ElementBuffer
{
public:
    // Constructors
    ElementBuffer() = default;
    ElementBuffer(std::vector<std::uint32_t> indices);

    // Destructors
    ~ElementBuffer() { Destroy(); }

    void Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID); }
    void Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

    void Destroy() { glDeleteBuffers(1, &(m_ID)); }

    std::uint32_t GetID() const { return m_ID; }

private:
    std::uint32_t m_ID;
};