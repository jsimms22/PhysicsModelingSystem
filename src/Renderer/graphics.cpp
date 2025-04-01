// vendors
// project headers
#include "../Renderer/Graphics.hpp"
// std library
#include <vector>
#include <iostream>

std::vector<vertexf> FloorVertex(uint32_t vertexCount, float length, float width)
{
    float coord_x = -(width / 2);
    float coord_z = -(length / 2);
    float dx = (width / vertexCount);
    float dz = (length / vertexCount);
    std::vector<vertexf> floor;
    for (uint32_t i=0; i<vertexCount; ++i) {
        for (uint32_t j=0; j<vertexCount; ++j) {
            floor.push_back(vertexf
                {   //position
                    vec3f{ (coord_x + j*dx), 0.0f, (coord_z + i*dz) },
                    // normal
                    vec3f{ 1.0f, 1.0f, 1.0f },
                    // texture
                    vec2f{ 0.0f, 0.0f },
                    // color
                    vec4f{ 1.f, 1.f, 1.f, 1.f}
                });
        }
    }
    // std::cout << floor.size() << std::endl;
    return floor;
}

std::vector<uint32_t> FloorIndex(uint32_t vertexCount)
{
    std::vector<uint32_t> index;
    for (uint32_t i=0; i<vertexCount-1; ++i) {
        for (uint32_t j=0; j<vertexCount-1; ++j) {
            uint32_t tl = (i*vertexCount) + j;
            uint32_t tr = tl + 1;
            uint32_t bl = ((i+1)*vertexCount) + j;
            uint32_t br = bl + 1;
            index.push_back(tl); index.push_back(bl); index.push_back(tr);
            index.push_back(tr); index.push_back(bl); index.push_back(br);
        }
    }
#ifdef DEBUG
    std::cout << index.size() << std::endl;
    for (int i=0; i<(index.size()-2); i+=3) {
        std::cout << index[i] << "/" << index[i+1] << "/" << index[i+2] << std::endl;
    }
#endif
    return index;
}

