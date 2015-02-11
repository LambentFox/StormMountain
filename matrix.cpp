#include "matrix.h"

/*
 *	Constructors
 */

vec2::vec2(){};
vec3::vec3(){};
vec4::vec4(){};

mat3::mat3(){};
mat4::mat4(){};

vec2::vec2(float x)
{
	for(unsigned int i = 0; i < 2; i++)
		v[i] = x;
}
vec3::vec3(float x)
{
	for(unsigned int i = 0; i < 3; i++)
		v[i] = x;
}
vec4::vec4(float x)
{
	for(unsigned int i = 0; i < 4; i++)
		v[i] = x;
}

vec2::vec2(float x, float y)
{
	v[0] = x; v[1] = y;
}

vec2::vec2(const vec3& vv)
{
	v[0] = vv.v[0]; v[1] = vv.v[1];
}

vec2::vec2(const vec4& vv)
{
	v[0] = vv.v[0]; v[1] = vv.v[1];
}

vec3::vec3(float x, float y, float z)
{
	v[0] = x; v[1] = y; v[2] = z;
}

vec3::vec3(const vec2& vv, float z)
{
	v[0] = vv.v[0]; v[1] = vv.v[1]; v[2] = z;
}
vec3::vec3(float x, vec2& vv)
{
	v[0] = x; v[1] = vv.v[0]; v[2] = vv.v[1];
}
vec3::vec3(const vec4& vv)
{
	v[0] = vv.v[0]; v[1] = vv.v[1]; v[2] = vv.v[2];
}

vec4::vec4(float x, float y, float z, float w)
{
	v[0] = x; v[1] = y; v[2] = z; v[3] = w;
}

vec4::vec4 (const vec2& vv, float z, float w)
{
	v[0] = vv.v[0]; v[1] = vv.v[1];
	v[2] = z; v[3] = w;

}
vec4::vec4 (float x, const vec2& vv, float w)
{
	v[0] = x; v[1] = vv.v[0];
	v[2] = vv.v[1]; v[3] = w;
}
vec4::vec4(float x, float y, const vec2& vv)
{
	v[0] = x; v[1] = y;
	v[2] = vv.v[0];v[3] = vv.v[1];
}
vec4::vec4(const vec2& vv1, const vec2& vv2)
{
	v[0] = vv1.v[0];v[1] = vv1.v[1];
	v[2] = vv2.v[0];v[3] = vv2.v[1];
}

vec4::vec4 (const vec3& vv, float w)
{
	v[0] = vv.v[0]; v[1] = vv.v[1];
	v[2] = vv.v[2]; v[3] = w;
}
vec4::vec4 (float x, const vec3& vv)
{
	v[0] = x; v[1] = vv.v[0];
	v[2] = vv.v[1]; v[3] = vv.v[2];
}

mat3::mat3 (float a, float b, float c,
		  float d, float e, float f,
		  float g, float h, float i)
{
	m[0] = a; m[1] = b; m[2] = c;
	m[3] = d; m[4] = e; m[5] = f;
	m[6] = g; m[7] = h; m[8] = i;
}

mat3::mat3(float val)
{
	for(unsigned int i = 0; i < 9; i++)
		m[i] = val;
}

mat4::mat4 (float a, float b, float c, float d,
		  float e, float f, float g, float h,
		  float i, float j, float k, float l,
		  float mm, float n, float o, float p)
{
	m[0] = a; m[1] = b; m[2] = c; m[3] = d; 
	m[4] = e; m[5] = f; m[6] = g; m[7] = h; 
	m[8] = i; m[9] = j; m[10] = k; m[11] = l;
	m[12] = mm; m[13] = n; m[14] = o; m[15] = p;
}

mat4::mat4(float val)
{
	for(unsigned int i = 0; i < 16; i++)
		m[i] = val;
}

/*
 * Vec2 Operators
 */

vec2 vec2::operator+ (const vec2& val)
{
	vec2 r;
	for(unsigned int i = 0; i < 2; i++)
		r.v[i] = v[i] + val.v[i];
	return r;
}

vec2 vec2::operator+ (float val)
{
	vec2 r;
	for(unsigned int i = 0; i < 2; i++)
		r.v[i] = v[i] + val;
	return r;
}

vec2& vec2::operator+= (const vec2& val)
{
	for(unsigned int i = 0; i < 2; i++)
		v[i] += val.v[i];
	return *this;
}

vec2& vec2::operator+= (float val)
{
	for(unsigned int i = 0; i < 2; i++)
		v[i] += val;
	return *this;
}

vec2 vec2::operator- (const vec2& val)
{
	vec2 r;
	for(unsigned int i = 0; i < 2; i++)
		r.v[i] = v[i] - val.v[i];
	return r;
}

vec2 vec2::operator- (float val)
{
	vec2 r;
	for(unsigned int i = 0; i < 2; i++)
		r.v[i] = v[i] - val;
	return r;
}

vec2& vec2::operator-= (const vec2& val)
{
	for(unsigned int i = 0; i < 2; i++)
		v[i] -= val.v[i];
	return *this;
}

vec2& vec2::operator-= (float val)
{
	for(unsigned int i = 0; i < 2; i++)
		v[i] -= val;
	return *this;
}

vec2 vec2::operator* (const vec2& val)
{
	vec2 r;
	for(unsigned int i = 0; i < 2; i++)
		r.v[i] = v[i] * val.v[i];
	return r;
}

vec2 vec2::operator* (float val)
{
	vec2 r;
	for(unsigned int i = 0; i < 2; i++)
		r.v[i] = v[i] * val;
	return r;
}

vec2& vec2::operator*= (const vec2& val)
{
	for(unsigned int i = 0; i < 2; i++)
		v[i] *= val.v[i];
	return *this;
}

vec2& vec2::operator*= (float val)
{
	for(unsigned int i = 0; i < 2; i++)
		v[i] *= val;
	return *this;
}

vec2 vec2::operator/ (const vec2& val)
{
	vec2 r;
	for(unsigned int i = 0; i < 2; i++)
		r.v[i] = v[i] / val.v[i];
	return r;
}

vec2 vec2::operator/ (float val)
{
	vec2 r;
	for(unsigned int i = 0; i < 2; i++)
		r.v[i] = v[i] / val;
	return r;
}

vec2& vec2::operator/= (const vec2& val)
{
	for(unsigned int i = 0; i < 2; i++)
		v[i] /= val.v[i];
	return *this;
}

vec2& vec2::operator/= (float val)
{
	for(unsigned int i = 0; i < 2; i++)
		v[i] /= val;
	return *this;
}

vec2& vec2::operator= (const vec2& val)
{
	for(unsigned int i = 0; i < 2; i++)
		v[i] = val.v[i];
	return *this;
}

vec2& vec2::operator= (float val)
{
	for(unsigned int i = 0; i < 2; i++)
		v[i] = val;
	return *this;
}

vec2 vec2::operator- (void)const
{
	return(vec2(-v[0],-v[1]));
}

/*
 * Vec 3 Operators
 */

vec3 vec3::operator+ (const vec3& val)
{
	vec3 r;
	for(unsigned int i = 0; i < 3; i++)
		r.v[i] = v[i] + val.v[i];
	return r;
}

vec3 vec3::operator+ (float val)
{
	vec3 r;
	for(unsigned int i = 0; i < 3; i++)
		r.v[i] = v[i] + val;
	return r;
}

vec3& vec3::operator+= (const vec3& val)
{
	for(unsigned int i = 0; i < 3; i++)
		v[i] += val.v[i];
	return *this;
}

vec3& vec3::operator+= (float val)
{
	for(unsigned int i = 0; i < 3; i++)
		v[i] += val;
	return *this;
}

vec3 vec3::operator- (const vec3& val)
{
	vec3 r;
	for(unsigned int i = 0; i < 3; i++)
		r.v[i] = v[i] - val.v[i];
	return r;
}

vec3 vec3::operator- (float val)
{
	vec3 r;
	for(unsigned int i = 0; i < 3; i++)
		r.v[i] = v[i] - val;
	return r;
}

vec3& vec3::operator-= (const vec3& val)
{
	for(unsigned int i = 0; i < 3; i++)
		v[i] -= val.v[i];
	return *this;
}

vec3& vec3::operator-= (float val)
{
	for(unsigned int i = 0; i < 3; i++)
		v[i] -= val;
	return *this;
}

vec3 vec3::operator* (const vec3& val)
{
	vec3 r;
	for(unsigned int i = 0; i < 3; i++)
		r.v[i] = v[i] * val.v[i];
	return r;
}

vec3 vec3::operator* (float val)
{
	vec3 r;
	for(unsigned int i = 0; i < 3; i++)
		r.v[i] = v[i] * val;
	return r;
}

vec3& vec3::operator*= (const vec3& val)
{
	for(unsigned int i = 0; i < 3; i++)
		v[i] *= val.v[i];
	return *this;
}

vec3& vec3::operator*= (float val)
{
	for(unsigned int i = 0; i < 3; i++)
		v[i] *= val;
	return *this;
}

vec3 vec3::operator/ (const vec3& val)
{
	vec3 r;
	for(unsigned int i = 0; i < 3; i++)
		r.v[i] = v[i] / val.v[i];
	return r;
}

vec3 vec3::operator/ (float val)
{
	vec3 r;
	for(unsigned int i = 0; i < 3; i++)
		r.v[i] = v[i] / val;
	return r;
}

vec3& vec3::operator/= (const vec3& val)
{
	for(unsigned int i = 0; i < 3; i++)
		v[i] /= val.v[i];
	return *this;
}

vec3& vec3::operator/= (float val)
{
	for(unsigned int i = 0; i < 3; i++)
		v[i] /= val;
	return *this;
}

vec3& vec3::operator= (const vec3& val)
{
	for(unsigned int i = 0; i < 3; i++)
		v[i] = val.v[i];
	return *this;
}

vec3& vec3::operator= (float val)
{
	for(unsigned int i = 0; i < 3; i++)
		v[i] = val;
	return *this;
}

vec3 vec3::operator- (void)const
{
	return(vec3(-v[0],-v[1],-v[2]));
}

/*
 * Vec4 Operators
 */

vec4 vec4::operator+ (const vec4& val)
{
	vec4 r;
	for(unsigned int i = 0; i < 4; i++)
		r.v[i] = v[i] + val.v[i];
	return r;
}

vec4 vec4::operator+ (float val)
{
	vec4 r;
	for(unsigned int i = 0; i < 4; i++)
		r.v[i] = v[i] + val;
	return r;
}

vec4& vec4::operator+= (const vec4& val)
{
	for(unsigned int i = 0; i < 4; i++)
		v[i] += val.v[i];
	return *this;
}

vec4& vec4::operator+= (float val)
{
	for(unsigned int i = 0; i < 4; i++)
		v[i] += val;
	return *this;
}

vec4 vec4::operator- (const vec4& val)
{
	vec4 r;
	for(unsigned int i = 0; i < 4; i++)
		r.v[i] = v[i] - val.v[i];
	return r;
}

vec4 vec4::operator- (float val)
{
	vec4 r;
	for(unsigned int i = 0; i < 4; i++)
		r.v[i] = v[i] - val;
	return r;
}

vec4& vec4::operator-= (const vec4& val)
{
	for(unsigned int i = 0; i < 4; i++)
		v[i] -= val.v[i];
	return *this;
}

vec4& vec4::operator-= (float val)
{
	for(unsigned int i = 0; i < 4; i++)
		v[i] -= val;
	return *this;
}

vec4 vec4::operator* (const vec4& val)
{
	vec4 r;
	for(unsigned int i = 0; i < 4; i++)
		r.v[i] = v[i] * val.v[i];
	return r;
}

vec4 vec4::operator* (float val)
{
	vec4 r;
	for(unsigned int i = 0; i < 4; i++)
		r.v[i] = v[i] * val;
	return r;
}

vec4& vec4::operator*= (const vec4& val)
{
	for(unsigned int i = 0; i < 4; i++)
		v[i] *= val.v[i];
	return *this;
}

vec4& vec4::operator*= (float val)
{
	for(unsigned int i = 0; i < 4; i++)
		v[i] *= val;
	return *this;
}

vec4 vec4::operator/ (const vec4& val)
{
	vec4 r;
	for(unsigned int i = 0; i < 4; i++)
		r.v[i] = v[i] / val.v[i];
	return r;
}

vec4 vec4::operator/ (float val)
{
	vec4 r;
	for(unsigned int i = 0; i < 4; i++)
		r.v[i] = v[i] / val;
	return r;
}

vec4& vec4::operator/= (const vec4& val)
{
	for(unsigned int i = 0; i < 4; i++)
		v[i] /= val.v[i];
	return *this;
}

vec4& vec4::operator/= (float val)
{
	for(unsigned int i = 0; i < 4; i++)
		v[i] /= val;
	return *this;
}

vec4& vec4::operator= (const vec4& val)
{
	for(unsigned int i = 0; i < 4; i++)
		v[i] = val.v[i];
	return *this;
}

vec4& vec4::operator= (float val)
{
	for(unsigned int i = 0; i < 4; i++)
		v[i] = val;
	return *this;
}

vec4 vec4::operator- (void)const
{
	return(vec4(-v[0],-v[1],-v[2],-v[3]));
}
/*
 *	mat3 Operators
 */

vec3 mat3::operator* (const vec3& val){
	vec3 result();
	float x = m[0]*val.v[0] + m[3]*val.v[1] + m[6]*val.v[2];
	float y = m[1]*val.v[0] + m[4]*val.v[1] + m[7]*val.v[2];
	float z = m[2]*val.v[0] + m[5]*val.v[1] + m[8]*val.v[2];
	return vec3(x, y, z);
}

mat3 mat3::operator* (const mat3& val)
{
	mat3 result(0.0f);
	for(unsigned int col = 0; col < 3; col++){
		for(unsigned int row = 0; row < 3; row++){
			float sum = 0.0f;
			for(unsigned int i = 0; i < 3; i++){
				sum += val.m[(3 * col) + i]*m[row + (3 * i)];
			}
			result.m[row+(3*col)] = sum;
		}	
	}
	return result;
}

mat3& mat3::operator= (const mat3& val)
{
	for(unsigned int i = 0; i < 9; i++)
		m[i] = val.m[i];
	return *this;
}

/*
 *	mat4 Operators
 */

 vec4 mat4::operator* (const vec4& val){
 	float x = m[0]*val.v[0] + m[4]*val.v[1] + m[8]*val.v[2] + m[12]*val.v[3];
	float y = m[1]*val.v[0] + m[5]*val.v[1] + m[9]*val.v[2] + m[13]*val.v[3];
	float z = m[2]*val.v[0] + m[6]*val.v[1] + m[10]*val.v[2] + m[14]*val.v[3];
	float w = m[3]*val.v[0] + m[7]*val.v[1] + m[11]*val.v[2] + m[15]*val.v[3];
	return vec4(x, y, z, w);
}

mat4 mat4::operator* (const mat4& val)
{
	mat4 result(0.0f);
	for(unsigned int col = 0; col < 4; col++){
		for(unsigned int row = 0; row < 4; row++){
			float sum = 0.0f;
			for(unsigned int i = 0; i < 4; i++){
				sum += val.m[(4 * col) + i]*m[row + (4 * i)];
			}
			result.m[row+(4*col)] = sum;
		}	
	}
	return result;
}

mat4& mat4::operator= (const mat4& val)
{
	for(unsigned int i = 0; i < 16; i++)
		m[i] = val.m[i];
	return *this;
}

/*
 * Vector Functions
 */

float length (const vec2& val){return sqrt((val.v[0]*val.v[0])+(val.v[1]*val.v[1]));}
float length2 (const vec2& val){return ((val.v[0]*val.v[0])+(val.v[1]*val.v[1]));}
float length (const vec3& val){return sqrt((val.v[0]*val.v[0])+(val.v[1]*val.v[1])+(val.v[2]*val.v[2]));}
float length2 (const vec3& val){return ((val.v[0]*val.v[0])+(val.v[1]*val.v[1])+(val.v[2]*val.v[2]));}
float length (const vec4& val){return sqrt((val.v[0]*val.v[0])+(val.v[1]*val.v[1])+(val.v[2]*val.v[2])+(val.v[3]*val.v[3]));}
float length2 (const vec4& val){return ((val.v[0]*val.v[0])+(val.v[1]*val.v[1])+(val.v[2]*val.v[2])+(val.v[3]*val.v[3]));}

vec2 normalize (const vec2& val)
{
	float l = length(val);
	if (l == 0.0f)
		return vec2(0.0f,0.0f);
	float x = val.v[0]/l;
	float y = val.v[1]/l;
	return vec2(x,y);
}

vec3 normalize (const vec3& val)
{
	float l = length(val);
	if (l == 0.0f)
		return vec3(0.0f,0.0f,0.0f);
	float x = val.v[0]/l;
	float y = val.v[1]/l;
	float z = val.v[2]/l;
	return vec3(x,y,z);
}

vec4 normalize (const vec4& val)
{
	float l = length(val);
	if (l == 0.0f)
		return vec4(0.0f,0.0f,0.0f,0.0f);
	float x = val.v[0]/l;
	float y = val.v[1]/l;
	float z = val.v[2]/l;
	float w = val.v[3]/l;
	return vec4(x,y,z,w);
}

float dot(const vec2& a, const vec2& b)
{
	float sum = 0.0f;
	for(unsigned int i = 0; i < 2; i++)
		sum += a.v[i] * b.v[i];
	return sum;
}

float dot(const vec3& a, const vec3& b)
{
	float sum = 0.0f;
	for(unsigned int i = 0; i < 3; i++)
		sum += a.v[i] * b.v[i];
	return sum;
}

float dot(const vec4& a, const vec4& b)
{
	float sum = 0.0f;
	for(unsigned int i = 0; i < 4; i++)
		sum += a.v[i] * b.v[i];
	return sum;
}

vec3 cross(const vec3& a, const vec3& b)
{
	float x = a.v[1]*b.v[2] - a.v[2]*b.v[1];
	float y = a.v[2]*b.v[0] - a.v[0]*b.v[2];
	float z = a.v[0]*b.v[1] - a.v[1]*b.v[0];
	return vec3(x,y,z);
}

vec4 cross(const vec4& a, const vec4 b)
{
	vec3 a2(a); vec3 b2(b);
	return vec4(cross(a2,b2),0.0f);
}

/*
 * Matrix Functions
 */
mat3 identity3()
{
	return mat3(
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f);
}

mat4 identity4()
{
	return mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

mat3 transpose( const mat3& mat)
{
	return mat3(
		mat.m[0],mat.m[3],mat.m[6],
		mat.m[1],mat.m[4],mat.m[7],
		mat.m[2],mat.m[5],mat.m[8]);
}

mat4 transpose( const mat4& mat)
{
	return mat4(
		mat.m[0],mat.m[4],mat.m[8],mat.m[12],
		mat.m[1],mat.m[5],mat.m[9],mat.m[13],
		mat.m[2],mat.m[6],mat.m[10],mat.m[14],
		mat.m[3],mat.m[7],mat.m[11],mat.m[15]);
}

float determinant (const mat3& mat){
	return (mat.m[0]*mat.m[4]*mat.m[8] +
			mat.m[1]*mat.m[5]*mat.m[6] +
			mat.m[2]*mat.m[3]*mat.m[7] -
			mat.m[0]*mat.m[5]*mat.m[7] -
			mat.m[1]*mat.m[3]*mat.m[8] -
			mat.m[2]*mat.m[4]*mat.m[6]);
}

float determinant(const mat4& mat){
	return(mat.m[3] * mat.m[6] * mat.m[9] * mat.m[12] - mat.m[2] * mat.m[7] * mat.m[9] * mat.m[12] - mat.m[3] * mat.m[5] * mat.m[10] * mat.m[12] + mat.m[1] * mat.m[7] * mat.m[10] * mat.m[12]+
	mat.m[2] * mat.m[5] * mat.m[11] * mat.m[12] - mat.m[1] * mat.m[6] * mat.m[11] * mat.m[12] - mat.m[3] * mat.m[6] * mat.m[8] * mat.m[13] + mat.m[2] * mat.m[7] * mat.m[8] * mat.m[13]+
	mat.m[3] * mat.m[4] * mat.m[10] * mat.m[13] - mat.m[0] * mat.m[7] * mat.m[10] * mat.m[13] - mat.m[2] * mat.m[4] * mat.m[11] * mat.m[13] + mat.m[0] * mat.m[6] * mat.m[11] * mat.m[13]+
	mat.m[3] * mat.m[5] * mat.m[8] * mat.m[14] - mat.m[1] * mat.m[7] * mat.m[8] * mat.m[14] - mat.m[3] * mat.m[4] * mat.m[9] * mat.m[14] + mat.m[0] * mat.m[7] * mat.m[9] * mat.m[14]+
	mat.m[1] * mat.m[4] * mat.m[11] * mat.m[14] - mat.m[0] * mat.m[5] * mat.m[11] * mat.m[14] - mat.m[2] * mat.m[5] * mat.m[8] * mat.m[15] + mat.m[1] * mat.m[6] * mat.m[8] * mat.m[15]+
	mat.m[2] * mat.m[4] * mat.m[9] * mat.m[15] - mat.m[0] * mat.m[6] * mat.m[9] * mat.m[15] - mat.m[1] * mat.m[4] * mat.m[10] * mat.m[15] + mat.m[0] * mat.m[5] * mat.m[10] * mat.m[15]);
}

mat3 inverse(const mat3& mat)
{
	float det = determinant(mat);
	if(det == 0.0f)
		fprintf(stderr, "Determinant value zero, unable to invert matrix.\n" );

	float inv_det = 1.0f/ det;
	return mat3((mat.m[4]*mat.m[8] - mat.m[5]*mat.m[7])* inv_det,
				(mat.m[2]*mat.m[7] - mat.m[1]*mat.m[8])* inv_det,
				(mat.m[1]*mat.m[5] - mat.m[2]*mat.m[4])* inv_det,
				(mat.m[5]*mat.m[6] - mat.m[3]*mat.m[8])* inv_det,
				(mat.m[0]*mat.m[8] - mat.m[2]*mat.m[6])* inv_det,
				(mat.m[2]*mat.m[3] - mat.m[0]*mat.m[5])* inv_det,
				(mat.m[3]*mat.m[7] - mat.m[4]*mat.m[6])* inv_det,
				(mat.m[1]*mat.m[6] - mat.m[0]*mat.m[7])* inv_det,
				(mat.m[0]*mat.m[4] - mat.m[1]*mat.m[3])* inv_det);
}

mat4 inverse(const mat4& mat)
{
	float det = determinant(mat);
	if(det == 0.0f)
		fprintf(stderr, "Determinant value zero, unable to invert matrix.\n" );

	float inv_det = 1.0f/det;
	return mat4((mat.m[6]*mat.m[11]*mat.m[13] - mat.m[7]*mat.m[10]*mat.m[13] + mat.m[7]*mat.m[9]*mat.m[14] - mat.m[5]*mat.m[11]*mat.m[14] - mat.m[6]*mat.m[9]*mat.m[15] + mat.m[5]*mat.m[10]*mat.m[15])*inv_det,
				(mat.m[3]*mat.m[10]*mat.m[13] - mat.m[2]*mat.m[11]*mat.m[13] - mat.m[3]*mat.m[9]*mat.m[14] + mat.m[1]*mat.m[11]*mat.m[14] + mat.m[2]*mat.m[9]*mat.m[15] - mat.m[1]*mat.m[10]*mat.m[15])*inv_det,
				(mat.m[2]*mat.m[7]*mat.m[13] - mat.m[3]*mat.m[6]*mat.m[13] + mat.m[3]*mat.m[5]*mat.m[14] - mat.m[1]*mat.m[7]*mat.m[14] - mat.m[2]*mat.m[5]*mat.m[15] + mat.m[1]*mat.m[6]*mat.m[15])*inv_det,
				(mat.m[3]*mat.m[6]*mat.m[9] - mat.m[2]*mat.m[7]*mat.m[9] - mat.m[3]*mat.m[5]*mat.m[10] + mat.m[1]*mat.m[7]*mat.m[10] + mat.m[2]*mat.m[5]*mat.m[11] - mat.m[1]*mat.m[6]*mat.m[11])*inv_det,
				(mat.m[7]*mat.m[10]*mat.m[12] - mat.m[6]*mat.m[11]*mat.m[12] - mat.m[7]*mat.m[8]*mat.m[14] + mat.m[4]*mat.m[11]*mat.m[14] + mat.m[6]*mat.m[8]*mat.m[15] - mat.m[4]*mat.m[10]*mat.m[15])*inv_det,
				(mat.m[2]*mat.m[11]*mat.m[12] - mat.m[3]*mat.m[10]*mat.m[12] + mat.m[3]*mat.m[8]*mat.m[14] - mat.m[0]*mat.m[11]*mat.m[14] - mat.m[2]*mat.m[8]*mat.m[15] + mat.m[0]*mat.m[10]*mat.m[15])*inv_det,
				(mat.m[3]*mat.m[6]*mat.m[12] - mat.m[2]*mat.m[7]*mat.m[12] - mat.m[3]*mat.m[4]*mat.m[14] + mat.m[0]*mat.m[7]*mat.m[14] + mat.m[2]*mat.m[4]*mat.m[15] - mat.m[0]*mat.m[6]*mat.m[15])*inv_det,
				(mat.m[2]*mat.m[7]*mat.m[8] - mat.m[3]*mat.m[6]*mat.m[8] + mat.m[3]*mat.m[4]*mat.m[10] - mat.m[0]*mat.m[7]*mat.m[10] - mat.m[2]*mat.m[4]*mat.m[11] + mat.m[0]*mat.m[6]*mat.m[11])*inv_det,
				(mat.m[5]*mat.m[11]*mat.m[12] - mat.m[7]*mat.m[9]*mat.m[12] + mat.m[7]*mat.m[8]*mat.m[13] - mat.m[4]*mat.m[11]*mat.m[13] - mat.m[5]*mat.m[8]*mat.m[15] + mat.m[4]*mat.m[9]*mat.m[15])*inv_det,
				(mat.m[3]*mat.m[9]*mat.m[12] - mat.m[1]*mat.m[11]*mat.m[12] - mat.m[3]*mat.m[8]*mat.m[13] + mat.m[0]*mat.m[11]*mat.m[13] + mat.m[1]*mat.m[8]*mat.m[15] - mat.m[0]*mat.m[9]*mat.m[15])*inv_det,
				(mat.m[1]*mat.m[7]*mat.m[12] - mat.m[3]*mat.m[5]*mat.m[12] + mat.m[3]*mat.m[4]*mat.m[13] - mat.m[0]*mat.m[7]*mat.m[13] - mat.m[1]*mat.m[4]*mat.m[15] + mat.m[0]*mat.m[5]*mat.m[15])*inv_det,
				(mat.m[3]*mat.m[5]*mat.m[8] - mat.m[1]*mat.m[7]*mat.m[8] - mat.m[3]*mat.m[4]*mat.m[9] + mat.m[0]*mat.m[7]*mat.m[9] + mat.m[1]*mat.m[4]*mat.m[11] - mat.m[0]*mat.m[5]*mat.m[11])*inv_det,
				(mat.m[6]*mat.m[9]*mat.m[12] - mat.m[5]*mat.m[10]*mat.m[12] - mat.m[6]*mat.m[8]*mat.m[13] + mat.m[4]*mat.m[10]*mat.m[13] + mat.m[5]*mat.m[8]*mat.m[14] - mat.m[4]*mat.m[9]*mat.m[14])*inv_det,
				(mat.m[1]*mat.m[10]*mat.m[12] - mat.m[2]*mat.m[9]*mat.m[12] + mat.m[2]*mat.m[8]*mat.m[13] - mat.m[0]*mat.m[10]*mat.m[13] - mat.m[1]*mat.m[8]*mat.m[14] + mat.m[0]*mat.m[9]*mat.m[14])*inv_det,
				(mat.m[2]*mat.m[5]*mat.m[12] - mat.m[1]*mat.m[6]*mat.m[12] - mat.m[2]*mat.m[4]*mat.m[13] + mat.m[0]*mat.m[6]*mat.m[13] + mat.m[1]*mat.m[4]*mat.m[14] - mat.m[0]*mat.m[5]*mat.m[14])*inv_det,
				(mat.m[1]*mat.m[6]*mat.m[8] - mat.m[2]*mat.m[5]*mat.m[8] + mat.m[2]*mat.m[4]*mat.m[9] - mat.m[0]*mat.m[6]*mat.m[9] - mat.m[1]*mat.m[4]*mat.m[10] + mat.m[0]*mat.m[5]*mat.m[10])*inv_det);
}
/*
 *	Transformation Functions
 */

mat4 translate (const mat4& mat, const vec3& val)
{
	mat4 id(identity4());
	id.m[12] = val.v[0]; 
	id.m[13] = val.v[1]; 
	id.m[14] = val.v[2];
	return id * mat;
}
mat4 translate (const mat4& mat, float x, float y, float z)
{
	mat4 id(identity4());
	id.m[12] = x; id.m[13] = y; id.m[14] = z;
	return id * mat;	
}

mat4 rotate (const mat4& mat, float deg, int x, int y, int z)
{
	mat4 idx(identity4());
	mat4 idy(identity4());
	mat4 idz(identity4());
	mat4 id(identity4());
	if(x != 0)
	{
		idx.m[5] = Cos(deg); idx.m[9] = -Sin(deg); idx.m[6] = Sin(deg); idx.m[10] = Cos(deg);
		id = idx * id;
	}
	if(y != 0)
	{
		idy.m[0] = Cos(deg); idy.m[2] = -Sin(deg); idy.m[8] = Sin(deg); idy.m[10] = Cos(deg);
		id = idy * id;
	}
	if(z != 0)
	{
		idz.m[0] = Cos(deg); idz.m[4] = -Sin(deg); idz.m[1] = Sin(deg); idz.m[5] = Cos(deg);
		id = idz * id;
	}
	return id * mat;
}

mat4 scale (const mat4& mat, const vec3& val)
{
	mat4 id(identity4());
	id.m[0] = val.v[0]; id.m[5] = val.v[1]; id.m[10] = val.v[2];
	return id * mat;
}

mat4 scale (const mat4& mat, float x, float y, float z)
{
	mat4 id(identity4());
	id.m[0] = x; id.m[5] = y; id.m[10] = z;
	return id * mat;
}


/*
 *	Print
 */

void print (const vec2& val)
{
	printf("[%.2f|%.2f]\n", val.v[0], val.v[1]);
}
void print (const vec3& val)
{
	printf("[%.2f|%.2f|%.2f]\n", val.v[0], val.v[1], val.v[2]);
}
void print (const vec4& val)
{
	printf("[%.2f|%.2f|%.2f|%.2f]\n", val.v[0], val.v[1], val.v[2], val.v[3]);
}
void print (const mat3& mat)
{
	for(unsigned int i = 0; i < 3; i++)
		printf("[%.2f|%.2f|%.2f]\n", mat.m[(3*i)], mat.m[(3*i)+1], mat.m[(3*i)+2]);
}
void print (const mat4& mat)
{
	for(unsigned int i = 0; i < 4; i++)
		printf("[%.2f|%.2f|%.2f|%.2f]\n", mat.m[(4*i)], mat.m[(4*i)+1], mat.m[(4*i)+2], mat.m[(4*i)+3]);
}

/*
 *	Camera Functions
 */

mat4 look_at (const vec3& eye, vec3 center, const vec3& up)
{
	// inverse translation
	mat4 p = translate (identity4(), -eye);
	// distance vector
	vec3 d = center - eye;
	// forward vector
	vec3 f = normalize (d);
	// right vector
	vec3 r = normalize (cross (f, up));
	// real up vector
	vec3 u = normalize (cross (r, f));
	mat4 ori = identity4();
	ori.m[0] = r.v[0];
	ori.m[4] = r.v[1];
	ori.m[8] = r.v[2];
	ori.m[1] = u.v[0];
	ori.m[5] = u.v[1];
	ori.m[9] = u.v[2];
	ori.m[2] = -f.v[0];
	ori.m[6] = -f.v[1];
	ori.m[10] = -f.v[2];
	
	return ori * p;//p * ori;

	//vec3 z = -center + eye;
	//normalize(z);
	//vec3 y = up;
	//vec3 x = cross(z,y);
	//y = cross(x,z);
	//normalize(x);
	//normalize(y);

	//return identity4();
}

mat4 perspective (float fovy, float aspect, float near, float far) {
	float fov_rad = fovy * ONE_DEG_IN_RAD;
	float range = tan (fov_rad / 2.0f) * near;
	float sx = (2.0f * near) / (range * aspect + range * aspect);
	float sy = near / range;
	float sz = -(far + near) / (far - near);
	float pz = -(2.0f * far * near) / (far - near);
	mat4 m(0.0f); // make sure bottom-right corner is zero
	m.m[0] = sx;
	m.m[5] = sy;
	m.m[10] = sz;
	m.m[14] = pz;
	m.m[11] = -1.0f;
	return m;
}