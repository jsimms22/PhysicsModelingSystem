// SIMD headers
#include <mmintrin.h>
// Project headers
#include "../include/fwd_math.hpp"

template <typename UNIT>
void vec4_copy(vec4<UNIT>& out, const vec4<UNIT>& in) 
{ 
    out.data[0] = in.data[0];
    out.data[1] = in.data[1];
    out.data[2] = in.data[2];
    out.data[3] = in.data[3];

}

// Unit/Identity Matrix
// | 1 0 0 0 |
// | 0 1 0 0 |
// | 0 0 1 0 |
// | 0 0 0 1 |
template <typename UNIT>
void mat4x4_id(mat4x4<UNIT>& out)
{ // calculate unit matrix
	for(size_t i=0; i<4; ++i) {
		for(size_t j=0; j<4; ++j) {
			out.data[i].data[j] = i==j ? 1.0 : 0.0;
        }
    }
}

template <typename UNIT>
void mat4x4_copy(mat4x4<UNIT>& out, const mat4x4<UNIT>& in)
{
	vec4_copy(out.data[0], in.data[0]);
    vec4_copy(out.data[1], in.data[1]);
    vec4_copy(out.data[2], in.data[2]);
    vec4_copy(out.data[3], in.data[3]);
}

template <typename UNIT>
void mat4x4_mul(mat4x4<UNIT>& out, const mat4x4<UNIT>& in1, const mat4x4<UNIT>& in2)
{
	mat4x4<UNIT> temp;
	for(size_t c=0; c<4; ++c) {
        for(size_t r=0; r<4; ++r) {
		    temp.data[c].data[r] = 0.0;
		    for(size_t k=0; k<4; ++k) {
			    temp.data[c].data[r] += in1.data[k].data[r] * in2.data[c].data[k];
            }
        }
	}
	mat4x4_copy(out, temp);
}

template <typename UNIT>
void mat4x4_mul_vec4(vec4<UNIT>& out, const mat4x4<UNIT>& mat_in, const vec4<UNIT>& vec_in)
{
	for(size_t j=0; j<4; ++j) {
		out[j] = 0.0;
		for(size_t i=0; i<4; ++i) {
			out.data[j] += mat_in.data[i].data[j] * vec_in.data[i];
        }
	}
}

template <typename UNIT>
void mat4x4_rotate_X(mat4x4<UNIT>& out, const mat4x4<UNIT>& in, const UNIT angle)
{
	float s = sinf(angle);
	float c = cosf(angle);
	mat4x4<UNIT> r = { // Rotation matrix
		vec4<UNIT>{1.f, 0.f, 0.f, 0.f},
		vec4<UNIT>{0.f,   c,   s, 0.f},
		vec4<UNIT>{0.f,  -s,   c, 0.f},
		vec4<UNIT>{0.f, 0.f, 0.f, 1.f}
	};
	mat4x4_mul(out, in, r);
}

template <typename UNIT>
void mat4x4_rotate_Y(mat4x4<UNIT>& out, const mat4x4<UNIT>& in, const UNIT angle)
{
	float s = sinf(angle);
	float c = cosf(angle);
	mat4x4<UNIT> r = { // Rotation matrix
		vec4<UNIT>{   c, 0.f,  -s, 0.f},
		vec4<UNIT>{ 0.f, 1.f, 0.f, 0.f},
		vec4<UNIT>{   s, 0.f,   c, 0.f},
		vec4<UNIT>{ 0.f, 0.f, 0.f, 1.f}
	};
	mat4x4_mul(out, in, r);
}

template <typename UNIT>
void mat4x4_rotate_Z(mat4x4<UNIT>& out, const mat4x4<UNIT>& in, const UNIT angle)
{
	float s = sinf(angle);
	float c = cosf(angle);
	mat4x4<UNIT> r = { // Rotation matrix
		vec4<UNIT>{   c,   s, 0.0, 0.0},
		vec4<UNIT>{  -s,   c, 0.0, 0.0},
		vec4<UNIT>{ 0.0, 0.0, 1.0, 0.0},
		vec4<UNIT>{ 0.0, 0.0, 0.0, 1.0}
	};
	mat4x4_mul(out, in, r);
}

template <typename UNIT>
void mat4x4_ortho(mat4x4<UNIT>& M, UNIT l, UNIT r, UNIT b, UNIT t, UNIT n, UNIT f)
{
	M.data[0].data[0] = 2.0/(r-l);
	M.data[0].data[1] = M.data[0].data[2] = M.data[0].data[3] = 0.0;

	M.data[1].data[1] = 2.0/(t-b);
	M.data[1].data[0] = M.data[1].data[2] = M.data[1].data[3] = 0.0;

	M.data[2].data[2] = -2.0/(f-n);
	M.data[2].data[0] = M.data[2].data[1] = M.data[2].data[3] = 0.0;
	
	M.data[3].data[0] = -(r+l)/(r-l);
	M.data[3].data[1] = -(t+b)/(t-b);
	M.data[3].data[2] = -(f+n)/(f-n);
	M.data[3].data[3] = 1.0;
}