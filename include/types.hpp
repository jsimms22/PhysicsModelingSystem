#pragma once

// std library
#include <cmath>
#include <vector>
// type headers
#include "types/vec3.hpp"
#include "types/vec4.hpp"

#include "types/mat3x3.hpp"
#include "types/mat4x4.hpp"

#include "types/vertex2.hpp"
#include "types/vertex3.hpp"
#include "types/vertex4.hpp"

const double M_PI = std::acos(-1);

template <typename UNIT>
struct Mesh
{
    //size_t numVertices;
    std::vector<UNIT> vertices;
    unsigned int numVertices;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    unsigned int positionVBO;
    unsigned int velocityVBO;
    unsigned int sizeIndices;
};
// Type aliases
using Meshf = Mesh<float>;
using Meshd = Mesh<double>;