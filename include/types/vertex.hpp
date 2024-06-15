#pragma once

// project headers
#include "vec2.hpp"
#include "vec3.hpp"

template <typename UNIT>
struct Vertex
{
public:
    vec3<UNIT> v;
    vec3<UNIT> vn;
    vec2<UNIT> vt;
    // vec3<UNIT> color;
};
// Type aliases
using Vertexf = Vertex<float>;
using Vertexd = Vertex<double>;