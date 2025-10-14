#pragma once
#include <cstdint>
#include <ostream>
#include <string>

// TODO: define methods/getters/setters

template <typename UNIT>
class vec3 
{
public:
    UNIT data[3] = {static_cast<UNIT>(0), 
                    static_cast<UNIT>(0), 
                    static_cast<UNIT>(0)};

    vec3() = default;
    vec3(UNIT x, UNIT y, UNIT z) 
        : data{x, y, z} {}
    vec3(UNIT value) 
        : data{value, value, value} {}
    
    // Constructor to convert between different types of vec3
    template <typename OtherUNIT>
    vec3(const vec3<OtherUNIT>& other) 
    {
        for (std::size_t i = 0; i < 3; ++i)
        {
            data[i] = static_cast<UNIT>(other[i]);
        }
    }

    UNIT& operator[](std::size_t index) { return data[index]; }
    const UNIT& operator[](std::size_t index) const { return data[index]; }
};

// Type aliases
using vec3f = vec3<float>;
using vec3d = vec3<double>;

template <typename UNIT>
std::ostream& operator<<(std::ostream& os, const vec3<UNIT>& obj)
{
    os << std::to_string(obj.data[0]) << ", " 
       << std::to_string(obj.data[1]) << ", "
       << std::to_string(obj.data[2]);

    return os;
}