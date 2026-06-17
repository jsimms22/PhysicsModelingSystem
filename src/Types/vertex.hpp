#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
// project headers

// Vertex layout: span of 11 if fully packed
// { x y z }{ n1 n2 n3 }{ tx1 tx2 }{ r g b }
class vertex
{
public:
    glm::vec<3, double> v;
    glm::vec<3, float> vn;
    glm::vec<2, float> vt;
    glm::vec<4, float> color;
};