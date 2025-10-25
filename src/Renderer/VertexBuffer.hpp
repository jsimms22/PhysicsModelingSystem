#pragma once

// vendors
// project headers
#include "../Types/mat4x4.hpp"
// std library
#include <cstdint>
#include <vector>

class vertex;

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

    void Bind();
    void Unbind();
    void Destroy();
    std::uint32_t GetID() const;

private:
    std::uint32_t m_ID;
};
