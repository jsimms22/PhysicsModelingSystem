#pragma once

// vendor
// project headers
// std library
#include <cmath>

template <typename UNIT>
struct vec3 
{ 
    UNIT data[3];

    UNIT GetX() const { return data[0]; }
    UNIT GetY() const { return data[1]; }
    UNIT GetZ() const { return data[2]; }

    UNIT Magnitude() const { return sqrt((data[0]*data[0]) + (data[1]*data[1]) + (data[2]*data[2])); }

    vec3& operator=(const vec3& rhs) 
    {
        if (this == &rhs) { return *this; } 
        this->data[0] = rhs.GetX();
        this->data[1] = rhs.GetY();
        this->data[2] = rhs.GetZ();
        return *this; 
    }
    vec3& operator=(const UNIT& rhs) 
    {
        this->data = {rhs, rhs, rhs}; 
        return *this; 
    }

    void operator==(const vec3& rhs)
    {
        return (this->GetX() == rhs.GetX() &&
                this->GetY() == rhs.GetY() &&
                this->GetZ() == rhs.GetZ());
    }
};
// Type aliases
using vec3f = vec3<float>;
using vec3d = vec3<double>;