#pragma once

// TODO: define methods/getters/setters

template <typename UNIT>
struct vec4 { UNIT data[4]; };
// Type aliases
using vec4f = vec4<float>;
using vec4d = vec4<double>;