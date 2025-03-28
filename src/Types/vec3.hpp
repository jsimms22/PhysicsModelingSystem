#pragma once

// TODO: define methods/getters/setters

template <typename UNIT>
struct vec3 { UNIT data[3]; };
// Type aliases
using vec3f = vec3<float>;
using vec3d = vec3<double>;