#pragma once

// TODO: define methods/getters/setters

template <typename UNIT>
struct vec2 
{ 
    UNIT data[2];

    UNIT GetX() const { return data[0]; }
    UNIT GetY() const { return data[1]; }

    vec2& operator=(const vec2& rhs) 
    {
        if (this == &rhs) { return *this; } 
        this->data[0] = rhs.GetX();
        this->data[1] = rhs.GetY();
        return *this; 
    }
    vec2& operator=(const UNIT& rhs) 
    {
        this->data = {rhs, rhs}; 
        return *this; 
    }

    void operator==(const vec2& rhs)
    {
        return (this->GetX() == rhs.GetX() &&
                this->GetY() == rhs.GetY());
    }
};
// Type aliases
using vec2f = vec2<float>;
using vec2d = vec2<double>;