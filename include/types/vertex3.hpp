#pragma once

// type headers
#include "vec3.hpp"

template <typename UNIT>
class Vertex3
{
public:
    vec3<UNIT> position;
    vec3<UNIT> normal;
    vec3<UNIT> tex;
    vec3<UNIT> color;
    Vertex3() {}
    Vertex3(vec3<UNIT> _pos, vec3<UNIT> _norm, vec3<UNIT> _tx, vec3<UNIT> _col) 
        : position{_pos}, normal{_norm}, tex{_tx}, color{_col} { }
    Vertex3(const Vertex3& v) 
        : position{v.position}, color{v.color} { }
};
// Type aliases
using Vertex3f = Vertex3<float>;
using Vertex3d = Vertex3<double>;