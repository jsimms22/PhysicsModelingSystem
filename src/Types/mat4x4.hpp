#pragma once

// type headers
#include "vec4.hpp"
// std library
#include <cstdlib>

template <typename UNIT>
class mat4x4 
{
public:
    vec4<UNIT> data[4];

    mat4x4() = default;
    mat4x4(const vec4<UNIT>(&d)[4])
        : data{d[0], d[1], d[2], d[3]} {}
    mat4x4(const vec4<UNIT>& row0, 
           const vec4<UNIT>& row1, 
           const vec4<UNIT>& row2,
           const vec4<UNIT>* row3) 
        : data{row0, row1, row2, row3} {}
    mat4x4(const UNIT& value);

    ~mat4x4() = default;

    void set_all(const UNIT& value);

    vec4<UNIT>& operator[](size_t index) { return data[index]; }
    vec4<UNIT>* operator->() { return data; }
    const vec4<UNIT>* operator->() const { return data; }
};
// Type aliases
using mat4x4f = mat4x4<float>;
using mat4x4d = mat4x4<double>;

template <typename UNIT>
mat4x4<UNIT>::mat4x4(const UNIT& value)
{
    mat4x4<UNIT>::set_all(value);
}

template <typename UNIT>
void mat4x4<UNIT>::set_all(const UNIT& value)
{
    for (std::size_t i=0; i<4; ++i)
        for (std::size_t j=0; j<4; ++j)
            this->data[i].data[j] = value;
}

template <typename UNIT>
const mat4x4<UNIT>& set_all(const UNIT& value)
{
    vec4<UNIT> data[4];
    for (std::size_t i=0; i<4; ++i)
        for (std::size_t j=0; j<4; ++j)
            data[i].data[j] = value;
    
    return data;
}