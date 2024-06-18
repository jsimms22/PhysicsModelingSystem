#pragma once

#include "math/math.hpp"

const double M_PI = std::acos(-1);

template <typename UNIT>
void vec3_scale(vec3<UNIT>& out, UNIT scalar, vec3<UNIT> in);

template <typename UNIT>
void vec3_add(vec3<UNIT>& out, vec3<UNIT> in1, vec3<UNIT> in2);

template <typename UNIT>
void vec3_sub(vec3<UNIT>& out, vec3<UNIT> in1, vec3<UNIT> in2);

template <typename UNIT>
void vec3_normal(vec3<UNIT>& out, vec3<UNIT> in);

template <typename UNIT>
void vec3_cross(vec3<UNIT>& out, vec3<UNIT> in1, vec3<UNIT> in2);

template <typename UNIT>
UNIT vec3_dot(vec3<UNIT> in1, vec3<UNIT> in2);

template <typename UNIT>
void vec4_copy(vec4<UNIT>& out, const vec4<UNIT> in);

template <typename UNIT>
UNIT vec3_angle(vec3<UNIT> in1, vec3<UNIT> in2);

template <typename UNIT>
void mat4x4_id(mat4x4<UNIT>& out);

template <typename UNIT>
void mat4x4_copy(mat4x4<UNIT>& out, const mat4x4<UNIT> in);

template <typename UNIT>
void mat4x4_add(mat4x4<UNIT>& out, const mat4x4<UNIT> in1, const mat4x4<UNIT> in2);

template <typename UNIT>
void mat4x4_mul(mat4x4<UNIT>& out, const mat4x4<UNIT> in1, const mat4x4<UNIT> in2);

template <typename UNIT>
void mat4x4_mul_vec3(vec4<UNIT>& out, const vec4<UNIT> vec_in, const mat4x4<UNIT> mat_in);

template <typename UNIT>
void mat3x3_rotate_X(vec3<UNIT>& out, const vec3<UNIT> in, const UNIT angle);

template <typename UNIT>
void mat3x3_rotate_Y(vec3<UNIT>& out, const vec3<UNIT> in, const UNIT angle);

template <typename UNIT>
void mat3x3_rotate_Z(vec3<UNIT>& out, const vec3<UNIT> in, const UNIT angle);

template <typename UNIT>
void mat4x4_ortho(mat4x4<UNIT>& M, UNIT l, UNIT r, UNIT b, UNIT t, UNIT n, UNIT f);

template <typename UNIT>
void mat4x4_translation(mat4x4<UNIT>& out, const mat4x4<UNIT> mat_in, const vec3<UNIT> vec_in);

template <typename UNIT>
void mat4x4_translation(mat4x4<UNIT>& out, const mat4x4<UNIT> mat_in, const vec4<UNIT> vec_in);

template <typename UNIT>
void mat4x4_buildScaler(mat4x4<UNIT>& out, const mat4x4<UNIT> mat_in, const vec3<UNIT> vec_in);

template <typename UNIT>
void mat4x4_buildScaler(mat4x4<UNIT>& out, const mat4x4<UNIT> mat_in, const vec4<UNIT> vec_in);

template <typename UNIT>
void mat4x4_projection(mat4x4<UNIT>& out, UNIT FOV, UNIT aspect, UNIT near, UNIT far);

template <typename UNIT>
void mat4x4_lookAt(mat4x4<UNIT>& out, vec3<UNIT> position, vec3<UNIT> center, vec3<UNIT> up);

template <typename UNIT>
void mat4_eulerAngles(mat4x4<UNIT>& out, vec3<UNIT> r);