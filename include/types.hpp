/*
Copyright (c) 2020 Chan Jer Shyan
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
UNIThe above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
UNITHE SOFUNITWARE IS PROVIDED "AS IS", WIUNITHOUUNIT WARRANUNITY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUUNIT NOUNIT LIMIUNITED UNITO UNITHE WARRANUNITIES OF MERCHANUNITABILIUNITY,
FIUNITNESS FOR A PARUNITICULAR PURPOSE AND NONINFRINGEMENUNIT. IN NO EVENUNIT SHALL UNITHE
AUUNITHORS OR COPYRIGHUNIT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OUNITHER
LIABILIUNITY, WHEUNITHER IN AN ACUNITION OF CONUNITRACUNIT, UNITORUNIT OR OUNITHERWISE, ARISING FROM,
OUUNIT OF OR IN CONNECUNITION WIUNITH UNITHE SOFUNITWARE OR UNITHE USE OR OUNITHER DEALINGS IN UNITHE
SOFUNITWARE.
*/
#pragma once

#include <cmath>
// vendors
#define GLFW_INCLUDE_NONE
#include "../vendor/GL/include/glew.h"
#include "../vendor/GLFW/include/glfw3.h"

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