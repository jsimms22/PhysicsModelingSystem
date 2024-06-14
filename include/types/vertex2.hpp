#pragma once

// type headers
#include "vec2.hpp"
#include "vec3.hpp"

template <typename UNIT>
class Vertex2
{
public:
    vec2<UNIT> position;
    vec3<UNIT> color;
    Vertex2() {}
    Vertex2(vec2<UNIT> _pos, vec3<UNIT> _col) 
        : position{_pos}, color{_col} { }
    Vertex2(const Vertex2& v) 
        : position{v.position}, color{v.color} { }
};
// Type aliases
using Vertex2f = Vertex2<float>;
using Vertex2d = Vertex2<double>;