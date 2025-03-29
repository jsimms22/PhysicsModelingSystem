#pragma once

// TODO: define methods/getters/setters

template <typename UNIT>
struct vec4 
{ 
    UNIT data[4];

    UNIT GetR() const { return data[0]; }
    UNIT GetG() const { return data[1]; }
    UNIT GetB() const { return data[2]; }
    UNIT GetOpacity() const { return data[3]; }

    vec4& operator=(const vec4& rhs) 
    {
        if (this == &rhs) { return *this; } 
        this->data[0] = rhs.GetR();
        this->data[1] = rhs.GetG();
        this->data[2] = rhs.GetB();
        this->data[3] = rhs.GetOpacity();
        return *this; 
    }
    vec4& operator=(const UNIT& rhs) 
    {
        this->data = {rhs, rhs, rhs}; 
        return *this; 
    }

    void operator==(const vec4& rhs)
    {
        return (this->GetR() == rhs.GetR() &&
                this->GetG() == rhs.GetG() &&
                this->GetB() == rhs.GetB() &&
                this->GetOpacity() == rhs.GetOpacity()
                );
    } 
};
// Type aliases
using vec4f = vec4<float>;
using vec4d = vec4<double>;