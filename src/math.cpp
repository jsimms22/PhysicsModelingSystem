// SIMD headers
#include <mmintrin.h>
// Project headers
#include "../include/math.hpp"

void vec4_copy(vec4& out, const vec4& in) 
{ 
    out[0] = in[0];
    out[1] = in[1];
    out[2] = in[2];
    out[3] = in[3];

}

// Unit/Identity Matrix
// | 1 0 0 0 |
// | 0 1 0 0 |
// | 0 0 1 0 |
// | 0 0 0 1 | 
void mat4x4_id(mat4x4& out)
{ // calculate unit matrix
	for(size_t i=0; i<4; ++i) {
		for(size_t j=0; j<4; ++j) {
			out[i][j] = i==j ? 1.0f : 0.0f;
        }
    }
}

void mat4x4_copy(mat4x4& out, const mat4x4& in)
{
	vec4_copy(out[0], in[0]);
    vec4_copy(out[1], in[1]);
    vec4_copy(out[2], in[2]);
    vec4_copy(out[3], in[3]);
}

void mat4x4_mul(mat4x4& out, const mat4x4& in1, const mat4x4& in2)
{
	mat4x4 temp;
	for(size_t c=0; c<4; ++c) {
        for(size_t r=0; r<4; ++r) {
		    temp[c][r] = 0.f;
		    for(size_t k=0; k<4; ++k) {
			    temp[c][r] += in1[k][r] * in2[c][k];
            }
        }
	}
	mat4x4_copy(out, temp);
}

void mat4x4_mul_vec4(vec4& out, const mat4x4& mat_in, const vec4& vec_in)
{
	for(size_t j=0; j<4; ++j) {
		out[j] = 0.f;
		for(size_t i=0; i<4; ++i) {
			out[j] += mat_in[i][j] * vec_in[i];
        }
	}
}

void mat4x4_rotate_X(mat4x4& out, const mat4x4& in, const float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);
	mat4x4 r = { // Rotation matrix
		{1.f, 0.f, 0.f, 0.f},
		{0.f,   c,   s, 0.f},
		{0.f,  -s,   c, 0.f},
		{0.f, 0.f, 0.f, 1.f}
	};
	mat4x4_mul(out, in, r);
}
void mat4x4_rotate_Y(mat4x4& out, const mat4x4& in, const float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);
	mat4x4 r = { // Rotation matrix
		{   c, 0.f,  -s, 0.f},
		{ 0.f, 1.f, 0.f, 0.f},
		{   s, 0.f,   c, 0.f},
		{ 0.f, 0.f, 0.f, 1.f}
	};
	mat4x4_mul(out, in, r);
}
void mat4x4_rotate_Z(mat4x4& out, const mat4x4& in, const float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);
	mat4x4 r = { // Rotation matrix
		{   c,   s, 0.f, 0.f},
		{  -s,   c, 0.f, 0.f},
		{ 0.f, 0.f, 1.f, 0.f},
		{ 0.f, 0.f, 0.f, 1.f}
	};
	mat4x4_mul(out, in, r);
}

void mat4x4_ortho(mat4x4& M, float l, float r, float b, float t, float n, float f)
{
	M[0][0] = 2.f/(r-l);
	M[0][1] = M[0][2] = M[0][3] = 0.f;

	M[1][1] = 2.f/(t-b);
	M[1][0] = M[1][2] = M[1][3] = 0.f;

	M[2][2] = -2.f/(f-n);
	M[2][0] = M[2][1] = M[2][3] = 0.f;
	
	M[3][0] = -(r+l)/(r-l);
	M[3][1] = -(t+b)/(t-b);
	M[3][2] = -(f+n)/(f-n);
	M[3][3] = 1.f;
}