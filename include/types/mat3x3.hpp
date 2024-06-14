#pragma once

// type headers
#include "vec3.hpp"

template <typename UNIT>
class mat3x3 
{ 
public:
    vec3<UNIT> data[3];
    void set_all(UNIT value);
};
// Type aliases
using mat3x3f = mat3x3<float>;
using mat3x3d = mat3x3<double>;

template <typename UNIT>
void mat3x3<UNIT>::set_all(UNIT value)
{
    for (size_t i=0; i<3; ++i)
        for (size_t j=0; j<3; ++j)
            this->data[i].data[j] = value;
}