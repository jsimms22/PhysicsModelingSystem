#pragma once

// project headers
#include "vec2.hpp"
#include "vec3.hpp"

template <typename UNIT>
struct vertex
{
public:
    vec3<UNIT> v;
    vec3<UNIT> vn;
    vec2<UNIT> vt;
    // vec3<UNIT> color;
};
// Type aliases
using vertexf = vertex<float>;
using vertexd = vertex<double>;