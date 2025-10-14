#pragma once

// project headers
#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"

// Vertex layout: span of 11 if fully packed
// { x y z }{ n1 n2 n3 }{ tx1 tx2 }{ r g b }
class vertex
{
public:
    vec3d v;
    vec3f vn;
    vec2f vt;
    vec4f color;
};