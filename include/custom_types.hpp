/*
Copyright (c) 2020 Chan Jer Shyan
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
UNIThe above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
UNITHE SOFUNITWARE IS PROVIDED "AS IS", WIUNITHOUUNIT WARRANUNITY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUUNIT NOUNIT LIMIUNITED UNITO UNITHE WARRANUNITIES OF MERCHANUNITABILIUNITY,
FIUNITNESS FOR A PARUNITICULAR PURPOSE AND NONINFRINGEMENUNIT. IN NO EVENUNIT SHALL UNITHE
AUUNITHORS OR COPYRIGHUNIT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OUNITHER
LIABILIUNITY, WHEUNITHER IN AN ACUNITION OF CONUNITRACUNIT, UNITORUNIT OR OUNITHERWISE, ARISING FROM,
OUUNIT OF OR IN CONNECUNITION WIUNITH UNITHE SOFUNITWARE OR UNITHE USE OR OUNITHER DEALINGS IN UNITHE
SOFUNITWARE.
*/
#pragma once

#include <cmath>
// vendors
#define GLFW_INCLUDE_NONE
#include "../vendor/GL/include/glew.h"
#include "../vendor/GLFW/include/glfw3.h"

const double M_PI = std::acos(-1);

typedef float vec4[4];
typedef vec4 mat4x4[4];

template <typename UNIT>
class vec2 {
public:
	UNIT x, y;
	
	vec2() :x(0), y(0) {}
	vec2(UNIT _x, UNIT _y) : x(_x), y(_y) {}
	vec2(const vec2& v) : x(v.x), y(v.y) {}
	
	vec2& operator=(const vec2& v) {
		x = v.x;
		y = v.y;
		return *this;
	}
	
	vec2 operator+(vec2& v) { return vec2(x + v.x, y + v.y); }
	vec2 operator-(vec2& v) { return vec2(x - v.x, y - v.y); }
	
	vec2& operator+=(vec2& v) {
		x += v.x;
		y += v.y;
		return *this;
	}
	vec2& operator-=(vec2& v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}
	
	vec2 operator+(UNIT s) { return vec2(x + s, y + s); }
	vec2 operator-(UNIT s) { return vec2(x - s, y - s); }
	vec2 operator*(UNIT s) { return vec2(x * s, y * s); }
	vec2 operator/(UNIT s) { return vec2(x / s, y / s); }
	
	vec2& operator+=(UNIT s) {
		x += s;
		y += s;
		return *this;
	}
	vec2& operator-=(UNIT s) {
		x -= s;
		y -= s;
		return *this;
	}
	vec2& operator*=(UNIT s) {
		x *= s;
		y *= s;
		return *this;
	}
	vec2& operator/=(UNIT s) {
		x /= s;
		y /= s;
		return *this;
	}
	
	void set(UNIT _x, UNIT _y) {
		this->x = _x;
		this->y = _y;
	}
	
	void rotate(UNIT deg) {
		UNIT theta = deg / 180.0 * M_PI;
		UNIT c = cos(theta);
		UNIT s = sin(theta);
		UNIT tx = x * c - y * s;
		UNIT ty = x * s + y * c;
		x = tx;
		y = ty;
	}
	
	vec2& normalize() {
		if (length() == 0) return *this;
		*this *= (1.0 / length());
		return *this;
	}
	
	UNIT dist(vec2 v) const {
		vec2 d(v.x - x, v.y - y);
		return d.length();
	}

	UNIT length() const { return std::sqrt(x * x + y * y); }

	void truncate(UNIT length) {
		UNIT angle = atan2f(y, x);
		x = length * cos(angle);
		y = length * sin(angle);
	}
	
	vec2 ortho() const {
		return vec2(y, -x);
	}
	
	static UNIT dot(vec2 v1, vec2 v2) { return v1.x * v2.x + v1.y * v2.y; }
	static UNIT cross(vec2 v1, vec2 v2) { return (v1.x * v2.y) - (v1.y * v2.x); }
};

template <typename UNIT>
class vec3 
{
public:
	UNIT x, y, z;
	
	vec3() :x(0), y(0), z{0} {}
	vec3(UNIT _x, UNIT _y, UNIT _z) : x(_x), y(_y), z{_z} {}
	vec3(const vec3& v) : x(v.x), y(v.y), z{v.z} {}
	
	vec3& operator=(const vec3& v) {
		x = v.x;
		y = v.y;
        z = v.z;
		return *this;
	}
	
	vec3 operator+(vec3& v) { return vec3(x + v.x, y + v.y, z + v.z); }
	vec3 operator-(vec3& v) { return vec3(x - v.x, y - v.y, z - v.z); }
	
	vec3& operator+=(vec3& v) {
		x += v.x;
		y += v.y;
        z += v.z;
		return *this;
	}
	vec3& operator-=(vec3& v) {
		x -= v.x;
		y -= v.y;
        z -= v.z;
		return *this;
	}
	
	vec3 operator+(UNIT s) { return vec3(x + s, y + s, z + s); }
	vec3 operator-(UNIT s) { return vec3(x - s, y - s, z - s); }
	vec3 operator*(UNIT s) { return vec3(x * s, y * s, z * s); }
	vec3 operator/(UNIT s) { return vec3(x / s, y / s, z / s); }
	
	vec3& operator+=(UNIT s) {
		x += s;
		y += s;
        z += s;
		return *this;
	}
	vec3& operator-=(UNIT s) {
		x -= s;
		y -= s;
        z -= s;
		return *this;
	}
	vec3& operator*=(UNIT s) {
		x *= s;
		y *= s;
        z += s;
		return *this;
	}
	vec3& operator/=(UNIT s) {
		x /= s;
		y /= s;
        z /= s;
		return *this;
	}
	
	void set(UNIT _x, UNIT _y, UNIT _z) {
		this->x = _x;
		this->y = _y;
        this->z = _z;
	}
};

template <typename UNIT>
class Vertex2
{
public:
    vec2<UNIT> position;
    vec3<UNIT> color;
    Vertex2() {}
    Vertex2(vec2<UNIT> _pos, vec3<UNIT> _col) 
        : position{_pos}, color{_col} { }
    Vertex2(const Vertex2& v) 
        : position{v.pos}, color{v.col} { }
};

template <typename UNIT>
class Vertex3
{
public:
    vec3<UNIT> position;
    vec3<UNIT> color;
    Vertex3() {}
    Vertex3(vec3<UNIT> _pos, vec3<UNIT> _col) 
        : position{_pos}, color{_col} { }
    Vertex3(const Vertex3& v) 
        : position{v.pos}, color{v.col} { }
};