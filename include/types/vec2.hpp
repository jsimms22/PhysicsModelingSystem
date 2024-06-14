#pragma once

template <typename UNIT>
struct vec2 { UNIT data[2]; };
// Type aliases
using vec2f = vec2<float>;
using vec2d = vec2<double>;