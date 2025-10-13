#pragma once
#include <cstdint>
#include <ostream>
#include <string>

// TODO: define methods/getters/setters

template <typename UNIT>
struct vec2 {
    UNIT data[2] = {static_cast<UNIT>(0.0), 
                    static_cast<UNIT>(0.0)};

    vec2() = default;
    vec2(UNIT x, UNIT y) 
        : data{x, y} {}
    vec2(UNIT value) 
        : data{value, value} {}
    
    // Constructor to convert between different types of vec2
    template <typename OtherUNIT>
    vec2(const vec2<OtherUNIT>& other) {
        for (std::size_t i = 0; i < 2; ++i) {
            data[i] = static_cast<UNIT>(other[i]);
        }
    }

    UNIT& operator[](std::size_t index) { return data[index]; }
    const UNIT& operator[](std::size_t index) const { return data[index]; }
};

template <typename UNIT>
std::ostream& operator<<(std::ostream& os, const vec2<UNIT>& obj)
{
    os << std::to_string(obj.data[0]) << ", " 
       << std::to_string(obj.data[1]);
    return os;
}

// Type aliases
using vec2f = vec2<float>;
using vec2d = vec2<double>;