#ifndef _MATRIX_MATH_H
#define _MATRIX_MATH_H

#include <stdio.h>
#include <math.h>

#define Cos(th) (cos(3.1415926/180*(th)))
#define Sin(th) (sin(3.1415926/180*(th)))
#define ONE_DEG_IN_RAD (2.0 * M_PI) / 360.0 // 0.017444444
#define ONE_RAD_IN_DEG 57.2957795

struct vec2;
struct vec3;
struct vec4;
struct versor;

struct vec2{
	vec2();
	vec2(float x);
	vec2(float x, float y);
	// Truncate Vec3 and Vec4 into Vec2
	vec2 (const vec3& vv);
	vec2 (const vec4& vv);
	//	General Operators
	vec2 operator+ (const vec2& val);	// addition
	vec2 operator+ (float val);
	vec2& operator+= (const vec2& val);
	vec2& operator+= (float val);
	vec2 operator- (const vec2& val);	// subtraction
	vec2 operator- (float val);
	vec2& operator-= (const vec2& val);
	vec2& operator-= (float val);
	vec2 operator* (const vec2& val);	// multiplication
	vec2 operator* (float val);
	vec2& operator*= (const vec2& val);
	vec2& operator*= (float val);
	vec2 operator/ (const vec2& val);	// Division
	vec2 operator/ (float val);
	vec2& operator/= (const vec2& val);
	vec2& operator/= (float val);
	vec2& operator= (const vec2& val);	// Equal
	vec2& operator= (float val);
	vec2 operator- (void)const;				// Negate
	float v[2];
};

struct vec3{
	vec3();
	vec3(float x);
	vec3(float x, float y, float z);
	// Creating a vec3 with vec2
	vec3 (const vec2& vv, float z);
	vec3 (float x, vec2& vv);
	//	Truncate Vec4 into Vec3
	vec3 (const vec4& vv);
	//	General Operators
	vec3 operator+ (const vec3& val);	// addition
	vec3 operator+ (float val);
	vec3& operator+= (const vec3& val);
	vec3& operator+= (float val);
	vec3 operator- (const vec3& val);	// subtraction
	vec3 operator- (float val);
	vec3& operator-= (const vec3& val);
	vec3& operator-= (float val);
	vec3 operator* (const vec3& val);	// multiplication
	vec3 operator* (float val);
	vec3& operator*= (const vec3& val);
	vec3& operator*= (float val);
	vec3 operator/ (const vec3& val);	// Division
	vec3 operator/ (float val);
	vec3& operator/= (const vec3& val);
	vec3& operator/= (float val);
	vec3& operator= (const vec3& val);	// Equal
	vec3& operator= (float val);
	vec3 operator- (void)const;				// Negate

	float v[3];
};

struct vec4{
	vec4();
	vec4(float x);
	vec4(float x, float y, float z, float w);
	// Creating a vec4 with a vec 2
	vec4 (const vec2& vv, float z, float w);
	vec4 (float x, const vec2& vv, float w);
	vec4(float x, float y, const vec2& vv);
	vec4(const vec2& vv1, const vec2& vv2);
	// Creating a vec4 with a vec3
	vec4 (const vec3& vv, float w);
	vec4 (float x, const vec3& vv);
	//	General Operators
	vec4 operator+ (const vec4& val);	// addition
	vec4 operator+ (float val);
	vec4& operator+= (const vec4& val);
	vec4& operator+= (float val);
	vec4 operator- (const vec4& val);	// subtraction
	vec4 operator- (float val);
	vec4& operator-= (const vec4& val);
	vec4& operator-= (float val);
	vec4 operator* (const vec4& val);	// multiplication
	vec4 operator* (float val);
	vec4& operator*= (const vec4& val);
	vec4& operator*= (float val);
	vec4 operator/ (const vec4& val);	// Division
	vec4 operator/ (float val);
	vec4& operator/= (const vec4& val);
	vec4& operator/= (float val);
	vec4& operator= (const vec4& val);	// Equal
	vec4& operator= (float val);
	vec4 operator- (void)const;				// Negate
	float v[4];
};

// Row Ordered
struct mat3 {
	mat3 ();
	mat3 (float val);
	mat3 (float a, float b, float c,
		  float d, float e, float f,
		  float g, float h, float i);
	vec3 operator* (const vec3& val);
	mat3 operator* (const mat3& val);
	mat3& operator= (const mat3& val);
	float m[9];
};

struct mat4 {
	mat4 ();
	mat4 (float val);
	mat4 (float a, float b, float c, float d,
		  float e, float f, float g, float h,
		  float i, float j, float k, float l,
		  float mm, float n, float o, float p);
	vec4 operator* (const vec4& val);
	mat4 operator* (const mat4& val);
	mat4& operator= (const mat4& val);
	float m[16];
};

// Print
void print (const vec2& val);
void print (const vec3& val);
void print (const vec4& val);
void print (const mat3& mat);
void print (const mat4& mat);

// Vector Functions
float length (const vec2& val);
float length (const vec3& val);
float length (const vec4& val);
float length2 (const vec2& val);
float length2 (const vec3& val);
float length2 (const vec4& val);
vec2 normalize (const vec2& val);
vec3 normalize (const vec3& val);
vec4 normalize (const vec4& val);
float dot(const vec2& a, const vec2& b);
float dot(const vec3& a, const vec3& b);
float dot(const vec4& a, const vec4& b);
vec3 cross(const vec3& a, const vec3& b);
vec4 cross(const vec4& a, const vec4& b);

// Matrix Functions
mat3 identity3();
mat4 identity4();
mat3 transpose( const mat3& mat);
mat4 transpose( const mat4& mat);
float determinant (const mat3& mat);
float determinant (const mat4& mat);
mat3 inverse (const mat3& mat);
mat4 inverse (const mat4& mat);

// Transformation Functions
mat4 translate (const mat4& mat, const vec3& val);
mat4 translate (const mat4& mat, float x, float y, float z);
mat4 rotate (const mat4& mat, float deg, int x, int y, int z);
mat4 scale(const mat4& mat, const vec3& val);
mat4 scale(const mat4& mat, float x, float y, float z);

// Camera Functions
mat4 look_at (const vec3& eye, vec3 center, const vec3& up);
mat4 perspective (float fovy, float aspect, float near, float far);

#endif