#pragma once

#include "types.hpp"

template <typename UNIT>
void vec4_copy(vec4<UNIT>& out, const vec4<UNIT>& in);

template <typename UNIT>
void mat4x4_id(mat4x4<UNIT>& out);

template <typename UNIT>
void mat4x4_copy(mat4x4<UNIT>& out, const mat4x4<UNIT>& in);

template <typename UNIT>
void mat4x4_mul(mat4x4<UNIT>& out, const mat4x4<UNIT>& in1, const mat4x4<UNIT>& in2);

template <typename UNIT>
void mat4x4_mul_vec4(vec4<UNIT>& out, const mat4x4<UNIT>& mat_in, const vec4<UNIT>& vec_in);

template <typename UNIT>
void mat4x4_rotate_X(mat4x4<UNIT>& out, const mat4x4<UNIT>& in, const UNIT angle);

template <typename UNIT>
void mat4x4_rotate_Y(mat4x4<UNIT>& out, const mat4x4<UNIT>& in, const UNIT angle);

template <typename UNIT>
void mat4x4_rotate_Z(mat4x4<UNIT>& out, const mat4x4<UNIT>& in, const UNIT angle);

template <typename UNIT>
void mat4x4_ortho(mat4x4<UNIT>& M, UNIT l, UNIT r, UNIT b, UNIT t, UNIT n, UNIT f);