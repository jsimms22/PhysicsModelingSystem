#pragma once

#include <cmath>

const double M_PI = std::acos(-1);

template <typename UNIT>
struct vec2 { UNIT data[2]; };
// Type aliases
using vec2f = vec2<float>;
using vec2d = vec2<double>;

template <typename UNIT>
struct vec3 { UNIT data[3]; };
// Type aliases
using vec3f = vec3<float>;
using vec3d = vec3<double>;

template <typename UNIT>
struct vec4 { UNIT data[4]; };
// Type aliases
using vec4f = vec4<float>;
using vec4d = vec4<double>;

template <typename UNIT>
struct mat4x4 { vec4<UNIT> data[4]; };
// Type aliases
using mat4x4f = mat4x4<float>;
using mat4x4d = mat4x4<double>;

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

template <typename UNIT>
class Vertex3
{
public:
    vec3<UNIT> position;
    vec3<UNIT> color;
    Vertex3() {}
    Vertex3(vec3<UNIT> _pos, vec3<UNIT> _col) 
        : position{_pos}, color{_col} { }
    Vertex3(const Vertex3& v) 
        : position{v.position}, color{v.color} { }
};
// Type aliases
using Vertex3f = Vertex3<float>;
using Vertex3d = Vertex3<double>;

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