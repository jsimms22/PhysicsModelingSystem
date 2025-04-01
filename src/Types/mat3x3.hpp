#pragma once

// type headers
#include "vec3.hpp"
// std library
#include <cstdlib>

template <typename UNIT>
class mat3x3 
{ 
public:
    vec3<UNIT> data[3];

    mat3x3()
        : data{UNIT(0), UNIT(0), UNIT(0)} {}
    mat3x3(const vec3<UNIT>(&d)[3])
        : data{d[0], d[1], d[2]} {}
    mat3x3(const vec3<UNIT>& row0, 
           const vec3<UNIT>& row1, 
           const vec3<UNIT>& row2) 
        : data{row0, row1, row2} {}
    mat3x3(const UNIT& value);

    ~mat3x3() = default;
    
    void set_all(const UNIT& value);

    vec4<UNIT>& operator[](size_t index) { return data[index]; }
    vec4<UNIT>* operator->() { return data; }
    const vec4<UNIT>* operator->() const { return data; }
};
// Type aliases
using mat3x3f = mat3x3<float>;
using mat3x3d = mat3x3<double>;

template <typename UNIT>
mat3x3<UNIT>::mat3x3(const UNIT& value)
{
    mat3x3<UNIT>::set_all(value);
}

template <typename UNIT>
void mat3x3<UNIT>::set_all(const UNIT& value)
{
    for (std::size_t i=0; i<3; ++i)
        for (std::size_t j=0; j<3; ++j)
            this->data[i].data[j] = value;
}

template <typename UNIT>
const mat3x3<UNIT>& set_all(const UNIT& value)
{
    vec3<UNIT> data[3];
    for (std::size_t i=0; i<3; ++i)
        for (std::size_t j=0; j<3; ++j)
            data[i].data[j] = value;
    
    return data;
}