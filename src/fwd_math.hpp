#pragma once

// vendors
// project headers
#include "Math/Math.hpp"
// std library

const double PI = std::acos(-1);

template <typename UNIT>
vec3<UNIT> vec3_scale(const UNIT scalar, const vec3<UNIT>& in);

template <typename UNIT>
vec3<UNIT> vec3_add(const vec3<UNIT>& in1, const vec3<UNIT>& in2);

template <typename UNIT>
vec3<UNIT> vec3_sub(const vec3<UNIT>& in1, const vec3<UNIT>& in2);

template <typename UNIT>
vec3<UNIT> vec3_normal(const vec3<UNIT>& in);

template <typename UNIT>
vec3<UNIT> vec3_cross(const vec3<UNIT>& in1, const vec3<UNIT>& in2);

template <typename UNIT>
UNIT vec3_dot(const vec3<UNIT>& in1, const vec3<UNIT>& in2);

template <typename UNIT>
UNIT vec3_angle(const vec3<UNIT>& in1, const vec3<UNIT>& in2);

template <typename UNIT>
vec4<UNIT> vec4_add(const vec4<UNIT>& in1, const vec4<UNIT>& in2);

template <typename UNIT>
mat4x4<UNIT> mat4x4_id();

template <typename UNIT>
mat4x4<UNIT> mat4x4_add(const mat4x4<UNIT>& in1, const mat4x4<UNIT>& in2);

template <typename UNIT>
mat4x4<UNIT> mat4x4_mul(const mat4x4<UNIT>& in1, const mat4x4<UNIT>& in2);

template <typename UNIT>
vec3<UNIT> mat3x3_rotate_X(const vec3<UNIT>& in, const UNIT angle);

template <typename UNIT>
vec3<UNIT> mat3x3_rotate_Y(const vec3<UNIT>& in, const UNIT angle);

template <typename UNIT>
vec3<UNIT> mat3x3_rotate_Z(const vec3<UNIT>& in, const UNIT angle);

template <typename UNIT>
vec4<UNIT> mat4x4_mul_vec3(const vec4<UNIT>& vec_in, const mat4x4<UNIT>& mat_in);

template <typename UNIT>
mat4x4<UNIT> mat4x4_ortho(const UNIT l, const UNIT r, const UNIT b, const UNIT t, const UNIT n, const UNIT f);

template <typename UNIT>
mat4x4<UNIT> mat4x4_translation(const mat4x4<UNIT>& mat_in, const vec3<UNIT>& vec_in);

template <typename UNIT>
mat4x4<UNIT> mat4x4_translation(const mat4x4<UNIT>& mat_in, const vec4<UNIT>& vec_in);

template <typename UNIT>
mat4x4<UNIT> mat4x4_buildScaler(const mat4x4<UNIT>& mat_in, const vec3<UNIT>& vec_in);

template <typename UNIT>
mat4x4<UNIT> mat4x4_buildScaler(const mat4x4<UNIT>& mat_in, const vec4<UNIT>& vec_in);

template <typename UNIT>
mat4x4<UNIT> mat4x4_projection(const UNIT FOV, const UNIT aspect, const UNIT near, const UNIT far);

template <typename UNIT>
mat4x4<UNIT> mat4x4_lookAt(const vec3<UNIT>& position, const vec3<UNIT>& center, const vec3<UNIT>& up);

template <typename UNIT>
mat4x4<UNIT> mat4_eulerAngles(const vec3<UNIT>& r);