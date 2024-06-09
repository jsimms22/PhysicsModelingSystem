#include "../include/math.hpp"

void vec4_dup(vec4 r, vec4 const src) 
{ 
	int i; 
	for(i=0; i<4; ++i) 
		r[i] = src[i]; 
}

void mat4x4_identity(mat4x4 M)
{
	int i, j;
	for(i=0; i<4; ++i)
		for(j=0; j<4; ++j)
			M[i][j] = i==j ? 1.f : 0.f;
}

void mat4x4_dup(mat4x4 M, mat4x4 const N)
{
	int i;
	for(i=0; i<4; ++i)
		vec4_dup(M[i], N[i]);
}

void mat4x4_mul(mat4x4 M, mat4x4 const a, mat4x4 const b)
{
	mat4x4 temp;
	int k, r, c;
	for(c=0; c<4; ++c) for(r=0; r<4; ++r) {
		temp[c][r] = 0.f;
		for(k=0; k<4; ++k)
			temp[c][r] += a[k][r] * b[c][k];
	}
	mat4x4_dup(M, temp);
}

void mat4x4_mul_vec4(vec4 r, mat4x4 const M, vec4 const v)
{
	int i, j;
	for(j=0; j<4; ++j) {
		r[j] = 0.f;
		for(i=0; i<4; ++i)
			r[j] += M[i][j] * v[i];
	}
}

void mat4x4_rotate_X(mat4x4 Q, mat4x4 const M, float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);
	mat4x4 R = {
		{1.f, 0.f, 0.f, 0.f},
		{0.f,   c,   s, 0.f},
		{0.f,  -s,   c, 0.f},
		{0.f, 0.f, 0.f, 1.f}
	};
	mat4x4_mul(Q, M, R);
}
void mat4x4_rotate_Y(mat4x4 Q, mat4x4 const M, float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);
	mat4x4 R = {
		{   c, 0.f,  -s, 0.f},
		{ 0.f, 1.f, 0.f, 0.f},
		{   s, 0.f,   c, 0.f},
		{ 0.f, 0.f, 0.f, 1.f}
	};
	mat4x4_mul(Q, M, R);
}
void mat4x4_rotate_Z(mat4x4 Q, mat4x4 const M, float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);
	mat4x4 R = {
		{   c,   s, 0.f, 0.f},
		{  -s,   c, 0.f, 0.f},
		{ 0.f, 0.f, 1.f, 0.f},
		{ 0.f, 0.f, 0.f, 1.f}
	};
	mat4x4_mul(Q, M, R);
}

void mat4x4_ortho(mat4x4 M, float l, float r, float b, float t, float n, float f)
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