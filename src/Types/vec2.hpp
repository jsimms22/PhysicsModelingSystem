#pragma once

// TODO: define methods/getters/setters

template <typename UNIT>
struct vec2 {
    UNIT data[2] = {UNIT(0), UNIT(0)};

    vec2() = default;
    vec2(UNIT x, UNIT y) 
        : data{x, y} {}
    vec2(UNIT value) 
        : data{value, value} {}

    UNIT& operator[](std::size_t index) { return data[index]; }
    const UNIT& operator[](std::size_t index) const { return data[index]; }
};
// Type aliases
using vec2f = vec2<float>;
using vec2d = vec2<double>;