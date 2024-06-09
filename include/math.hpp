#pragma once

#include "custom_types.hpp"

void vec4_copy(vec4& out, const vec4& in);

void mat4x4_id(mat4x4& out);

void mat4x4_copy(mat4x4& out, const mat4x4& in);

void mat4x4_mul(mat4x4& out, const mat4x4& in1, const mat4x4& in2);

void mat4x4_mul_vec4(vec4& out, const mat4x4& mat_in, const vec4& vec_in);

void mat4x4_rotate_X(mat4x4& out, const mat4x4& in, const float angle);

void mat4x4_rotate_Y(mat4x4& out, const mat4x4& in, const float angle);

void mat4x4_rotate_Z(mat4x4& out, const mat4x4& in, const float angle);

void mat4x4_ortho(mat4x4& M, float l, float r, float b, float t, float n, float f);