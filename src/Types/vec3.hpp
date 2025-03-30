#pragma once
#include <cstdint>

// TODO: define methods/getters/setters

template <typename UNIT>
struct vec3 {
    UNIT data[3] = {UNIT(0), UNIT(0), UNIT(0)};

    vec3() = default;
    vec3(UNIT x, UNIT y, UNIT z) 
        : data{x, y, z} {}
    vec3(UNIT value) 
        : data{value, value, value} {}

    UNIT& operator[](std::size_t index) { return data[index]; }
    const UNIT& operator[](std::size_t index) const { return data[index]; }
};
// Type aliases
using vec3f = vec3<float>;
using vec3d = vec3<double>;