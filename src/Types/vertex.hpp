#pragma once

// project headers
#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"

// Vertex layout: span of 11 if fully packed
// { x y z }{ n1 n2 n3 }{ tx1 tx2 }{ r g b }
template <typename UNIT>
struct vertex
{
public:
    vec3<UNIT> v;
    vec3<UNIT> vn;
    vec2<UNIT> vt;
    vec4<UNIT> color;
};
// Type aliases
using vertexf = vertex<float>;
using vertexd = vertex<double>;