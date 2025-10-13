#pragma once

// vendors
// project headers
#include "../types.hpp"
// std library
#include <iostream>
// SIMD
#include <mmintrin.h>

template <typename UNIT>
vec3<UNIT> vec3_scale(const UNIT scalar, const vec3<UNIT>& in)
{
    return {scalar * in.data[0], 
            scalar * in.data[1], 
            scalar * in.data[2]};
}

template <typename UNIT>
vec3<UNIT> vec3_add(const vec3<UNIT>& in1, const vec3<UNIT>& in2)
{
    return {in1.data[0] + in2.data[0], 
            in1.data[1] + in2.data[1], 
            in1.data[2] + in2.data[2]};
}

template <typename UNIT>
vec3<UNIT> vec3_sub(const vec3<UNIT>& in1, const vec3<UNIT>& in2)
{
    return {in1.data[0] - in2.data[0], 
            in1.data[1] - in2.data[1], 
            in1.data[2] - in2.data[2]};
}

template <typename UNIT>
vec3<UNIT> vec3_normal(const vec3<UNIT>& in)
{
	const UNIT normal = sqrt((in.data[0] * in.data[0]) + 
                             (in.data[1] * in.data[1]) + 
                             (in.data[2] * in.data[2]));
	return {in.data[0] / normal, 
            in.data[1] / normal, 
            in.data[2] / normal};
}

template <typename UNIT>
vec3<UNIT> vec3_cross(const vec3<UNIT>& in1, const vec3<UNIT>& in2)
{
	return {(in1.data[1] * in2.data[2]) - (in1.data[2] * in2.data[1]),
            (in1.data[2] * in2.data[0]) - (in1.data[0] * in2.data[2]),
            (in1.data[0] * in2.data[1]) - (in1.data[1] * in2.data[0])};
}
template <typename UNIT>
UNIT vec3_dot(const vec3<UNIT>& in1, const vec3<UNIT>& in2)
{
	return (in1.data[0] * in2.data[0]) + 
           (in1.data[1] * in2.data[1]) + 
           (in1.data[2] * in2.data[2]);
}

template <typename UNIT>
UNIT vec3_angle(const vec3<UNIT>& in1, const vec3<UNIT>& in2)
{
    const UNIT comp1 = vec3_dot(in1,in2);
    const UNIT comp2 = sqrt(pow(in1.data[0],2) + pow(in1.data[1],2) + pow(in1.data[2],2));
    const UNIT comp3 = sqrt(pow(in2.data[0],2) + pow(in2.data[1],2) + pow(in2.data[2],2));
    const UNIT angle = acos(comp1 / (comp2 * comp3));
    return static_cast<UNIT>((acos(-1.0) / 180.0)) * angle;
}

template <typename UNIT>
vec4<UNIT> vec4_add(const vec4<UNIT>& in1, const vec4<UNIT>& in2)
{
    return {in1.data[0] + in2.data[0],
            in1.data[1] + in2.data[1],
            in1.data[2] + in2.data[2],
            in1.data[3] + in2.data[3]};
}

// Unit/Identity Matrix
// | 1 0 0 0 |
// | 0 1 0 0 |
// | 0 0 1 0 |
// | 0 0 0 1 |
template <typename UNIT>
mat4x4<UNIT> mat4x4_id()
{ 
    // calculate identity matrix
    mat4x4<UNIT> matrix;
	for(std::size_t i=0; i<4; ++i) 
    {
		for(std::size_t j=0; j<4; ++j) 
        {
			matrix.data[i].data[j] = i==j ? 1.0 : 0.0;
        }
    }

    return matrix;
}

template <typename UNIT>
mat4x4<UNIT> mat4x4_add(const mat4x4<UNIT>& in1, const mat4x4<UNIT>& in2)
{
    mat4x4<UNIT> matrix;
    for(std::size_t i=0; i<4; ++i) 
    {
        for(std::size_t j=0; j<4; ++j) 
        {
            matrix.data[i].data[j] = in1.data[i].data[j] + in2.data[i].data[j];
        }
    }

    return matrix;
}

template <typename UNIT>
mat4x4<UNIT> mat4x4_mul(const mat4x4<UNIT>& in1, const mat4x4<UNIT>& in2)
{
	mat4x4<UNIT> matrix;
	for(std::size_t i=0; i<4; ++i) 
    {
        for(std::size_t j=0; j<4; ++j) 
        {
		    matrix.data[i].data[j] = 0.0;
		    for(std::size_t k=0; k<4; ++k) 
            {
			    matrix.data[i].data[j] += in1.data[k].data[j] * in2.data[i].data[k];
            }
        }
	}
	
    return matrix;
}

template <typename UNIT>
/* CHECK MAJORNESS */
vec3<UNIT> mat3x3_mul_vec3(const vec3<UNIT>& vec_in, const mat3x3<UNIT>& mat_in)
{   
    vec3<UNIT> vector;
    for(std::size_t j=0; j<3; ++j) 
    {
		vector.data[j] = 0.0;
		for(std::size_t i=0; i<3; ++i) 
        {
			vector.data[j] += mat_in.data[j].data[i] * vec_in.data[i];
        }
	}

    return vector;
}

template <typename UNIT>
vec3<UNIT> mat3x3_rotate_X(const vec3<UNIT>& in, const UNIT angle)
{
	const UNIT s = sin(angle);
	const UNIT c = cos(angle);
     // Rotation matrix
	mat3x3<UNIT> r = {vec3<UNIT>{1.0, 0.0, 0.0},
                      vec3<UNIT>{0.0,   c,   s},
                      vec3<UNIT>{0.0,  -s,   c}};
	return mat3x3_mul_vec3(in, r);
}

template <typename UNIT>
vec3<UNIT> mat3x3_rotate_Y(const vec3<UNIT>& in, const UNIT angle)
{
	const UNIT s = sin(angle);
	const UNIT c = cos(angle);
    // Rotation matrix
	mat3x3<UNIT> r = {vec3<UNIT>{   c, 0.0,  -s},
                      vec3<UNIT>{ 0.0, 1.0, 0.0},
                      vec3<UNIT>{   s, 0.0,   c}};
	return mat3x3_mul_vec3(in, r);
}

template <typename UNIT>
vec3<UNIT> mat3x3_rotate_Z(const vec3<UNIT>& in, const UNIT angle)
{
	const UNIT s = sin(angle);
	const UNIT c = cos(angle);
    // Rotation matrix
	mat3x3<UNIT> r = {vec3<UNIT>{   c,   s, 0.0},
		              vec3<UNIT>{  -s,   c, 0.0},
		              vec3<UNIT>{ 0.0, 0.0, 1.0}};
	return mat3x3_mul_vec3(in, r);
}

template <typename UNIT>
mat4x4<UNIT> mat4x4_ortho(const UNIT l, const UNIT r, const UNIT b, const UNIT t, const UNIT n, const UNIT f)
{
    return {{2.0/(r-l), 0.0, 0.0, 0.0},
            {0.0, 2.0/(t-b), 0.0, 0.0},
            {0.0, 0.0, -2.0/(f-n), 0.0},
            {-(r+l)/(r-l), -(t+b)/(t-b), -(f+n)/(f-n), 1.0}};
    /*
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
	M.data[3].data[3] = 1.0;*/
}

template <typename UNIT>
mat4x4<UNIT> mat4x4_translation(const mat4x4<UNIT>& mat_in, const vec3<UNIT>& vec_in)
{
    mat4x4<UNIT> matrix = mat4x4_id<UNIT>();
	for(std::size_t i=0; i<4; ++i) 
    {
        if (i!=3) 
        { 
            matrix.data[3].data[i] = mat_in.data[3].data[i] + vec_in.data[i]; 
        }
        else 
        { 
            matrix.data[3].data[i] += mat_in.data[3].data[i]; 
        }
	}

    return matrix;
}

template <typename UNIT>
mat4x4<UNIT> mat4x4_translation(const mat4x4<UNIT>& mat_in, const vec4<UNIT>& vec_in)
{
    mat4x4<UNIT> matrix;
	for(std::size_t i=0; i<4; ++i) 
    {
		matrix.data[3].data[i] = mat_in.data[3].data[i] + vec_in.data[i];
	}

    return matrix;
}

template <typename UNIT>
mat4x4<UNIT> mat4x4_buildScaler(const vec3<UNIT>& vec_in)
{
    mat4x4<UNIT> matrix = mat4x4_id<UNIT>();
	for(std::size_t i=0; i<4; ++i) 
    {
		for(std::size_t j=0; j<4; ++j) 
        {
			matrix.data[i].data[j] = (i==j && j!=3) ? vec_in.data[j] : matrix.data[i].data[j];
        }
    }

    return matrix;
}

template <typename UNIT>
mat4x4<UNIT> mat4x4_buildScaler(const mat4x4<UNIT>& mat_in, const vec4<UNIT>& vec_in)
{
    mat4x4<UNIT> matrix;
	for(std::size_t i=0; i<4; ++i) 
    {
		for(std::size_t j=0; j<4; ++j) 
        {
			matrix.data[i].data[j] = (i==j) ? vec_in.data[j] : mat_in.data[i].data[j];
        }
    }

    return matrix;
}

template <typename UNIT>
mat4x4<UNIT> mat4x4_projection(const UNIT FOV, const UNIT aspect, const UNIT near, const UNIT far)
{
	const UNIT TRIG_FOV = tan(FOV * 0.5); // tangent of half FOV
    // UNIT right = TRIG_FOV * near;   // half width of near plane
    // UNIT top = right / aspect;      // half height of near plane
    return {{1.0 / TRIG_FOV, 0.0, 0.0, 0.0},
            {0.0, aspect / TRIG_FOV, 0.0, 0.0},
            {0.0, 0.0, -(far + near) / (far - near), -1.0},
            {0.0, 0.0, -(2 * far * near) / (far - near), 0.0}};
    /*
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
    */
}

template <typename UNIT>
// position = eye, center = target/center, up = up
mat4x4<UNIT> mat4x4_lookAt(const vec3<UNIT>& position, const vec3<UNIT>& center, const vec3<UNIT>& up)
{
    // back.eye = normalize(eye - center)
    vec3<UNIT> back = vec3_sub(position, center);
    back = vec3_normal(back);
    // right.eye = normalize(up x back)
    vec3<UNIT> right = vec3_cross(up, back);
    right = vec3_normal(right);
    // up = normalize(back x right)
    vec3<UNIT> upRelative = vec3_cross(back, right);
    upRelative = vec3_normal(upRelative);

    /*------------------------------------------------------------------------------------
          | 1 0 0 -eye.x |        | r.x r.y r.z 0 |               | r.x r.y r.z -eye.x |
      T = | 0 1 0 -eye.y |    R = | u.x u.u u.z 0 |   M = R * T = | u.x u.y u.z -eye.y |
          | 0 0 1 -eye.z |        | b.x b.y b.z 0 |               | b.x b.y b.z -eye.z |
          | 0 0 0   1    |        |  0   0   0  1 |               |  0   0   0     1   |
    ------------------------------------------------------------------------------------*/
    mat4x4<UNIT> T = mat4x4_id<UNIT>();
    T.data[3].data[0] = -position.data[0];
    T.data[3].data[1] = -position.data[1];
    T.data[3].data[2] = -position.data[2];

    mat4x4<UNIT> R = mat4x4_id<UNIT>();
    for (std::size_t i=0; i<3; ++i) 
    {
        R.data[i].data[0] = right.data[i];
        R.data[i].data[1] = upRelative.data[i];
        R.data[i].data[2] = back.data[i];
    }

    return mat4x4_mul(T, R);
}

template <typename UNIT>
mat4x4<UNIT> mat4_eulerAngles(const vec3<UNIT>& r)
{
    /* could cause issues if out not fully initialized */
    const UNIT sP = sin(r.data[0]);
    const UNIT cP = cos(r.data[0]);
    const UNIT sR = sin(r.data[1]);
    const UNIT cR = cos(r.data[1]);
    const UNIT sY = sin(r.data[2]);
    const UNIT cY = cos(r.data[2]);

    mat4x4<UNIT> matrix = mat4x4_id<UNIT>();
    matrix.data[0].data[0] = cY * cP;
    matrix.data[0].data[1] = -cY * sP * cR + sY * sR;
    matrix.data[0].data[2] = cY * sP * sR + sY * cR;
    matrix.data[1].data[0] = sP;
    matrix.data[1].data[1] = cP * cR;
    matrix.data[1].data[2] = -cP * sR;
    matrix.data[2].data[0] = -sY * cP;
    matrix.data[2].data[1] = sY * sP * cR + cY * sR;
    matrix.data[2].data[2] = -sY * sP * sR + cY * cR;
    return matrix;
}