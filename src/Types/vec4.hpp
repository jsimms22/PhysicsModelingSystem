#pragma once
#include <cstdint>
// TODO: define methods/getters/setters

template <typename UNIT>
struct vec4 {
    UNIT data[4] = {UNIT(0), UNIT(0), UNIT(0), UNIT(0)};

    vec4() = default;
    vec4(UNIT x, UNIT y, UNIT z, UNIT w) 
        : data{x, y, z, w} {}
    vec4(UNIT value) 
        : data{value, value, value, value} {}

    UNIT& operator[](std::size_t index) { return data[index]; }
    const UNIT& operator[](std::size_t index) const { return data[index]; }
};
// Type aliases
using vec4f = vec4<float>;
using vec4d = vec4<double>;