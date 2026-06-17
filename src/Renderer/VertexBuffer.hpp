#pragma once

// vendors
#include <glm/mat4x4.hpp>
// project headers
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
    VertexBuffer(std::vector<glm::dmat4>& matrices);

    // Destructors
    ~VertexBuffer() { Destroy(); }

    void Bind();
    void Unbind();
    void Destroy();
    std::uint32_t GetID() const;

private:
    std::uint32_t m_ID;
};
