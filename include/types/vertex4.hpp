#pragma once

template <typename UNIT>
class Vertex4
{
public:
    vec4<UNIT> position;
    vec3<UNIT> color;
    Vertex4() {}
    Vertex4(vec4<UNIT> _pos, vec3<UNIT> _col) 
        : position{_pos}, color{_col} { }
    Vertex4(const Vertex4& v) 
        : position{v.position}, color{v.color} { }
};
// Type aliases
using Vertex4f = Vertex4<float>;
using Vertex4d = Vertex4<double>;