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

    // Constructor to convert between different types of vec4
    template <typename OtherUNIT>
    vec4(const vec4<OtherUNIT>& other) {
        for (std::size_t i = 0; i < 4; ++i) {
            data[i] = static_cast<UNIT>(other[i]);
        }
    }

    UNIT& operator[](std::size_t index) { return data[index]; }
    const UNIT& operator[](std::size_t index) const { return data[index]; }
};
// Type aliases
using vec4f = vec4<float>;
using vec4d = vec4<double>;