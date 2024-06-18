#pragma once

// SIMD
#include <mmintrin.h>
// std library
#include <iostream>
// project headers
#include "../types.hpp"

template <typename UNIT>
void vec3_scale(vec3<UNIT>& out, UNIT scalar, vec3<UNIT> in)
{
    out.data[0] = scalar * in.data[0];
    out.data[1] = scalar * in.data[1];
    out.data[2] = scalar * in.data[2];
}

template <typename UNIT>
void vec3_add(vec3<UNIT>& out, vec3<UNIT> in1, vec3<UNIT> in2)
{
    out.data[0] = in1.data[0] + in2.data[0];
    out.data[1] = in1.data[1] + in2.data[1];
    out.data[2] = in1.data[2] + in2.data[2];
}

template <typename UNIT>
void vec3_sub(vec3<UNIT>& out, vec3<UNIT> in1, vec3<UNIT> in2)
{
    out.data[0] = in1.data[0] - in2.data[0];
    out.data[1] = in1.data[1] - in2.data[1];
    out.data[2] = in1.data[2] - in2.data[2];
}

template <typename UNIT>
void vec3_normal(vec3<UNIT>& out, vec3<UNIT> in)
{
	float normal = sqrt(in.data[0]*in.data[0] + in.data[1]*in.data[1] + in.data[2]*in.data[2]);
	out.data[0] = in.data[0] / normal;
	out.data[1] = in.data[1] / normal;
	out.data[2] = in.data[2] / normal;
}

template <typename UNIT>
void vec3_cross(vec3<UNIT>& out, vec3<UNIT> in1, vec3<UNIT> in2)
{
	vec3<UNIT> cross;
    cross.data[0] = in1.data[1] * in2.data[2] - in1.data[2] * in2.data[1];
    cross.data[1] = in1.data[2] * in2.data[0] - in1.data[0] * in2.data[2];
    cross.data[2] = in1.data[0] * in2.data[1] - in1.data[1] * in2.data[0];
    out.data[0] = cross.data[0];
    out.data[1] = cross.data[1];
    out.data[2] = cross.data[2];
}
template <typename UNIT>
UNIT vec3_dot(vec3<UNIT> in1, vec3<UNIT> in2)
{
	return in1.data[0] * in2.data[0] + in1.data[1] * in2.data[1] + in1.data[2] * in2.data[2];
}

template <typename UNIT>
void vec4_copy(vec4<UNIT>& out, const vec4<UNIT> in) 
{ 
    out.data[0] = in.data[0];
    out.data[1] = in.data[1];
    out.data[2] = in.data[2];
    out.data[3] = in.data[3];
}

template <typename UNIT>
UNIT vec3_angle(vec3<UNIT> in1, vec3<UNIT> in2)
{
    UNIT angle;
    UNIT comp1 = vec3_dot(in1,in2);
    UNIT comp2 = sqrt(pow(in1.data[0],2) + pow(in1.data[1],2) + pow(in1.data[2],2));
    UNIT comp3 = sqrt(pow(in2.data[0],2) + pow(in2.data[1],2) + pow(in2.data[2],2));
    angle = acos(comp1 / (comp2 * comp3));
    // std::cout << angle << std::endl;
    return static_cast<UNIT>((acos(-1.0)/180.0))*angle;
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
void mat4x4_copy(mat4x4<UNIT>& out, const mat4x4<UNIT> in)
{
	vec4_copy(out.data[0], in.data[0]);
    vec4_copy(out.data[1], in.data[1]);
    vec4_copy(out.data[2], in.data[2]);
    vec4_copy(out.data[3], in.data[3]);
}

template <typename UNIT>
void mat4x4_add(mat4x4<UNIT>& out, const mat4x4<UNIT> in1, const mat4x4<UNIT> in2)
{
    for(size_t i=0; i<4; ++i) {
        for(size_t j=0; j<4; ++j) {
            out.data[i].data[j] = in1.data[i].data[j] + in2.data[i].data[j];
        }
    }
}

template <typename UNIT>
void mat4x4_mul(mat4x4<UNIT>& out, const mat4x4<UNIT> in1, const mat4x4<UNIT> in2)
{
	mat4x4<UNIT> temp;
	for(size_t i=0; i<4; ++i) {
        for(size_t j=0; j<4; ++j) {
		    temp.data[i].data[j] = 0.0;
		    for(size_t k=0; k<4; ++k) {
			    temp.data[i].data[j] += in1.data[k].data[j] * in2.data[i].data[k];
            }
        }
	}
	mat4x4_copy(out, temp);
}

template <typename UNIT>
/* CHECK MAJORNESS */
void mat3x3_mul_vec3(vec3<UNIT>& out, const vec3<UNIT> vec_in, const mat3x3<UNIT> mat_in)
{   
    for(size_t j=0; j<4; ++j) {
		out.data[j] = 0.0;
		for(size_t i=0; i<4; ++i) {
			out.data[j] += mat_in.data[j].data[i] * vec_in.data[i];
        }
	}
}

template <typename UNIT>
void mat3x3_rotate_X(vec3<UNIT>& out, const vec3<UNIT> in, const UNIT angle)
{
	float s = sin(angle);
	float c = cos(angle);
	mat3x3<UNIT> r = { // Rotation matrix
		vec3<UNIT>{1.0, 0.0, 0.0},
		vec3<UNIT>{0.0,   c,   s},
		vec3<UNIT>{0.0,  -s,   c}
	};
	mat3x3_mul_vec3(out, in, r);
}

template <typename UNIT>
void mat3x3_rotate_Y(vec3<UNIT>& out, const vec3<UNIT> in, const UNIT angle)
{
	float s = sin(angle);
	float c = cos(angle);
	mat3x3<UNIT> r = { // Rotation matrix
		vec3<UNIT>{   c, 0.0,  -s},
		vec3<UNIT>{ 0.0, 1.0, 0.0},
		vec3<UNIT>{   s, 0.0,   c}
	};
	mat3x3_mul_vec3(out, in, r);
}

template <typename UNIT>
void mat3x3_rotate_Z(vec3<UNIT>& out, const vec3<UNIT> in, const UNIT angle)
{
	float s = sin(angle);
	float c = cos(angle);
	mat3x3<UNIT> r = { // Rotation matrix
		vec3<UNIT>{   c,   s, 0.0},
		vec3<UNIT>{  -s,   c, 0.0},
		vec3<UNIT>{ 0.0, 0.0, 1.0}
	};
	mat3x3_mul_vec3(out, in, r);
}

template <typename UNIT>
void mat4x4_ortho(mat4x4<UNIT>& M, UNIT l, UNIT r, UNIT b, UNIT t, UNIT n, UNIT f)
{
	M.data[0].data[0] = 2.0/(r-l);
	M.data[0].data[1] = 0.0;
    M.data[0].data[2] = 0.0;
    M.data[0].data[3] = 0.0;
    M.data[1].data[0] = 0.0;
	M.data[1].data[1] = 2.0/(t-b);
    M.data[1].data[2] = 0.0;
    M.data[1].data[3] = 0.0;
    M.data[2].data[0] = 0.0;
    M.data[2].data[1] = 0.0;
	M.data[2].data[2] = -2.0/(f-n);
    M.data[2].data[3] = 0.0;
	M.data[3].data[0] = -(r+l)/(r-l);
	M.data[3].data[1] = -(t+b)/(t-b);
	M.data[3].data[2] = -(f+n)/(f-n);
	M.data[3].data[3] = 1.0;
}

template <typename UNIT>
void mat4x4_translation(mat4x4<UNIT>& out, const mat4x4<UNIT> mat_in, const vec3<UNIT> vec_in)
{
    /* could cause problems if out is not fully initialized */
	for(size_t i=0; i<4; ++i) {
		if (i!=3) { out.data[3].data[i] = mat_in.data[3].data[i] + vec_in.data[i]; }
		else { out.data[3].data[i] = mat_in.data[3].data[i]; }
	}
}

template <typename UNIT>
void mat4x4_translation(mat4x4<UNIT>& out, const mat4x4<UNIT> mat_in, const vec4<UNIT> vec_in)
{
    /* could cause problems if out is not fully initialized */
	for(size_t i=0; i<4; ++i) {
		out.data[3].data[i] = mat_in.data[3].data[i] + vec_in.data[i];
	}
}

template <typename UNIT>
void mat4x4_buildScaler(mat4x4<UNIT>& out, const mat4x4<UNIT> mat_in, const vec3<UNIT> vec_in)
{
	for(size_t i=0; i<4; ++i) {
		for(size_t j=0; j<4; ++j) {
			out.data[i].data[j] = (i==j && j!=3) ? vec_in.data[j] : mat_in.data[i].data[j];
        }
    }
}

template <typename UNIT>
void mat4x4_buildScaler(mat4x4<UNIT>& out, const mat4x4<UNIT> mat_in, const vec4<UNIT> vec_in)
{
	for(size_t i=0; i<4; ++i) {
		for(size_t j=0; j<4; ++j) {
			out.data[i].data[j] = (i==j) ? vec_in.data[j] : mat_in.data[i].data[j];
        }
    }
}

template <typename UNIT>
void mat4x4_projection(mat4x4<UNIT>& out, UNIT FOV, UNIT aspect, UNIT near, UNIT far)
{
	UNIT TRIG_FOV = tan(FOV * 0.5); // tangent of half FOV
    // UNIT right = TRIG_FOV * near;   // half width of near plane
    // UNIT top = right / aspect;      // half height of near plane
    out.data[0].data[0] = 1.0 / TRIG_FOV; // near / right;
    out.data[0].data[1] = 0.0;
    out.data[0].data[2] = 0.0;
    out.data[0].data[3] = 0.0;
    out.data[1].data[0] = 0.0;
    out.data[1].data[1] = aspect / TRIG_FOV; // near / top;
    out.data[1].data[2] = 0.0;
    out.data[1].data[3] = 0.0;
    out.data[2].data[0] = 0.0;
    out.data[2].data[1] = 0.0;
    out.data[2].data[2] = -(far + near) / (far - near);
    out.data[2].data[3] = -1.0;
    out.data[3].data[0] = 0.0;
    out.data[3].data[1] = 0.0;
    out.data[3].data[2] = -(2 * far * near) / (far - near);
    out.data[3].data[3] = 0.0;
}

template <typename UNIT>
// position = eye, center = target/center, up = up
void mat4x4_lookAt(mat4x4<UNIT>& out, vec3<UNIT> position, vec3<UNIT> center, vec3<UNIT> up)
{
    vec3<UNIT> back, right;
    // back.eye = normalize(eye - center)
    vec3_sub(back, position, center);
    vec3_normal(back, back);
    // right.eye = normalize(up x back)
    vec3_cross(right, up, back);
    vec3_normal(right, right);
    // up = normalize(back x right)
    vec3_cross(up, back, right);
    vec3_normal(up, up);
    //      | 1 0 0 -eye.x |        | r.x r.y r.z 0 |               | r.x r.y r.z -eye.x |
    //  T = | 0 1 0 -eye.y |    R = | u.x u.u u.z 0 |   M = R * T = | u.x u.y u.z -eye.y |
    //      | 0 0 1 -eye.z |        | b.x b.y b.z 0 |               | b.x b.y b.z -eye.z |
    //      | 0 0 0   1    |        |  0   0   0  1 |               |  0   0   0     1   |
    mat4x4<UNIT> T; mat4x4_id(T);
    T.data[3].data[0] = -position.data[0];
    T.data[3].data[1] = -position.data[1];
    T.data[3].data[2] = -position.data[2];
    mat4x4<UNIT> R; mat4x4_id(R);
    for (size_t i=0; i<3; ++i) {
        R.data[i].data[0] = right.data[i];
        R.data[i].data[1] = up.data[i];
        R.data[i].data[2] = back.data[i];
    }
    mat4x4_mul(out, T, R);

	// for (size_t itr = 0; itr < 4; ++itr) {
    //     for (size_t j = 0; j < 4; ++j) {
    //         std::cout << out.data[j].data[itr] << ", ";
    //     } std::cout << std::endl;
    // }
}

template <typename UNIT>
void mat4_eulerAngles(mat4x4<UNIT>& out, vec3<UNIT> r)
{
    /* could cause issues if out not fully initialized */
    UNIT sP = sin(r.data[0]);
    UNIT cP = cos(r.data[0]);
    UNIT sR = sin(r.data[1]);
    UNIT cR = cos(r.data[1]);
    UNIT sY = sin(r.data[2]);
    UNIT cY = cos(r.data[2]);

    out.data[0].data[0] = cY * cP;
    out.data[0].data[1] = -cY * sP * cR + sY * sR;
    out.data[0].data[2] = cY * sP * sR + sY * cR;
    out.data[1].data[0] = sP;
    out.data[1].data[1] = cP * cR;
    out.data[1].data[2] = -cP * sR;
    out.data[2].data[0] = -sY * cP;
    out.data[2].data[1] = sY * sP * cR + cY * sR;
    out.data[2].data[2] = -sY * sP * sR + cY * cR;
}