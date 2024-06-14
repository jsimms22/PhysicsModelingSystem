#pragma once

// type headers
#include "vec4.hpp"

template <typename UNIT>
class mat4x4 
{
public:
    vec4<UNIT> data[4]; 
    void set_all(UNIT value);
};
// Type aliases
using mat4x4f = mat4x4<float>;
using mat4x4d = mat4x4<double>;

template <typename UNIT>
void mat4x4<UNIT>::set_all(UNIT value)
{
    for (size_t i=0; i<4; ++i)
        for (size_t j=0; j<4; ++j)
            this->data[i].data[j] = value;
}