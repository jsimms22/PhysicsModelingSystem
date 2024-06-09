#pragma once

#include "custom_types.hpp"

void vec4_dup(vec4 r, vec4 const src);

void mat4x4_identity(mat4x4 M);

void mat4x4_dup(mat4x4 M, mat4x4 const N);

void mat4x4_mul(mat4x4 M, mat4x4 const a, mat4x4 const b);

void mat4x4_mul_vec4(vec4 r, mat4x4 const M, vec4 const v);

void mat4x4_rotate_X(mat4x4 Q, mat4x4 const M, float angle);

void mat4x4_rotate_Y(mat4x4 Q, mat4x4 const M, float angle);

void mat4x4_rotate_Z(mat4x4 Q, mat4x4 const M, float angle);

void mat4x4_ortho(mat4x4 M, float l, float r, float b, float t, float n, float f);