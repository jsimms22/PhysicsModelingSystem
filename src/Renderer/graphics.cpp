// vendors
// project headers
#include "Graphics.hpp"

// std library
#include <iostream>

std::vector<vertex> FloorVertex(std::uint32_t vertexCount, double length, double width)
{
    double coord_x = -(width / 2);
    double coord_z = -(length / 2);
    double dx = (width / vertexCount);
    double dz = (length / vertexCount);
    std::vector<vertex> floor;
    for (std::uint32_t i=0; i<vertexCount; ++i)
    {
        for (std::uint32_t j=0; j<vertexCount; ++j)
        {
            floor.push_back(vertex
                {   //position
                    vec3d{ (coord_x + j*dx), 0.0, (coord_z + i*dz) },
                    // normal
                    vec3f{ 1.0f, 1.0f, 1.0f },
                    // texture
                    vec2f{ 0.0f, 0.0f },
                    // color
                    vec4f{ 1.f, 1.f, 1.f, 1.f}
                });
        }
    }
    return floor;
}

std::vector<std::uint32_t> FloorIndex(std::uint32_t vertexCount)
{
    std::vector<std::uint32_t> index;
    for (std::uint32_t i=0; i<vertexCount-1; ++i)
    {
        for (std::uint32_t j=0; j<vertexCount-1; ++j)
        {
            std::uint32_t tl = (i*vertexCount) + j;
            std::uint32_t tr = tl + 1;
            std::uint32_t bl = ((i+1)*vertexCount) + j;
            std::uint32_t br = bl + 1;
            index.push_back(tl); index.push_back(bl); index.push_back(tr);
            index.push_back(tr); index.push_back(bl); index.push_back(br);
        }
    }

    return index;
}

