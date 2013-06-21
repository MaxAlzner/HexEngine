#include "..\include\MALib.h"

#ifdef _MA_MATRIX_H_
_MALIB_BEGIN

MALIB_API const MAT4x4 Identity = MAT4x4();

MALIB_API MAT4x4 ToIdentity(const MAT4x4& m)
{
	return MAT4x4(
		1.f, 0.f, 0.f, 0.f, 
		0.f, 1.f, 0.f, 0.f, 
		0.f, 0.f, 1.f, 0.f, 
		0.f, 0.f, 0.f, 1.f
		);
}
MALIB_API MAT4x4 Transpose(const MAT4x4& m)
{
#if 0
	return MAT4x4(
		m.m[0], m.m[4], m.m[ 8], m.m[12], 
		m.m[1], m.m[5], m.m[ 9], m.m[13], 
		m.m[2], m.m[6], m.m[10], m.m[14], 
		m.m[3], m.m[7], m.m[11], m.m[15]
		);
#else
	return MAT4x4(
		m.r0c0, m.r1c0, m.r2c0, m.r3c0, 
		m.r0c1, m.r1c1, m.r2c1, m.r3c1, 
		m.r0c2, m.r1c2, m.r2c2, m.r3c2, 
		m.r0c3, m.r1c3, m.r2c3, m.r3c3
		);
#endif
}
MALIB_API MAT4x4 Multiply(const MAT4x4& m1, const MAT4x4& m2)
{
#if 0
	return MAT4x4(
		(m1.m[0] * m2.m[0]) + (m1.m[1] * m2.m[4]) + (m1.m[2] * m2.m[8]) + (m1.m[3] * m2.m[12]), 
		(m1.m[0] * m2.m[1]) + (m1.m[1] * m2.m[5]) + (m1.m[2] * m2.m[9]) + (m1.m[3] * m2.m[13]), 
		(m1.m[0] * m2.m[0]) + (m1.m[1] * m2.m[6]) + (m1.m[2] * m2.m[10]) + (m1.m[3] * m2.m[14]), 
		(m1.m[0] * m2.m[0]) + (m1.m[1] * m2.m[7]) + (m1.m[2] * m2.m[11]) + (m1.m[3] * m2.m[15]), 

		(m1.m[4] * m2.m[0]) + (m1.m[5] * m2.m[4]) + (m1.m[6] * m2.m[8]) + (m1.m[7] * m2.m[12]), 
		(m1.m[4] * m2.m[1]) + (m1.m[5] * m2.m[5]) + (m1.m[6] * m2.m[9]) + (m1.m[7] * m2.m[13]), 
		(m1.m[4] * m2.m[2]) + (m1.m[5] * m2.m[6]) + (m1.m[6] * m2.m[10]) + (m1.m[7] * m2.m[14]), 
		(m1.m[4] * m2.m[3]) + (m1.m[5] * m2.m[7]) + (m1.m[6] * m2.m[11]) + (m1.m[7] * m2.m[15]), 

		(m1.m[8] * m2.m[0]) + (m1.m[9] * m2.m[4]) + (m1.m[10] * m2.m[8]) + (m1.m[11] * m2.m[12]), 
		(m1.m[8] * m2.m[1]) + (m1.m[9] * m2.m[5]) + (m1.m[10] * m2.m[9]) + (m1.m[11] * m2.m[13]), 
		(m1.m[8] * m2.m[2]) + (m1.m[9] * m2.m[6]) + (m1.m[10] * m2.m[10]) + (m1.m[11] * m2.m[14]), 
		(m1.m[8] * m2.m[3]) + (m1.m[9] * m2.m[7]) + (m1.m[10] * m2.m[11]) + (m1.m[11] * m2.m[15]), 

		(m1.m[12] * m2.m[0]) + (m1.m[13] * m2.m[4]) + (m1.m[10] * m2.m[8]) + (m1.m[15] * m2.m[12]), 
		(m1.m[12] * m2.m[1]) + (m1.m[13] * m2.m[5]) + (m1.m[10] * m2.m[9]) + (m1.m[15] * m2.m[13]), 
		(m1.m[12] * m2.m[2]) + (m1.m[13] * m2.m[6]) + (m1.m[10] * m2.m[10]) + (m1.m[15] * m2.m[14]), 
		(m1.m[12] * m2.m[3]) + (m1.m[13] * m2.m[7]) + (m1.m[10] * m2.m[11]) + (m1.m[15] * m2.m[15])
		);
#else
	return MAT4x4(
		(m1.r0c0 * m2.r0c0) + (m1.r0c1 * m2.r1c0) + (m1.r0c2 * m2.r2c0) + (m1.r0c3 * m2.r3c0), 
		(m1.r0c0 * m2.r0c1) + (m1.r0c1 * m2.r1c1) + (m1.r0c2 * m2.r2c1) + (m1.r0c3 * m2.r3c1), 
		(m1.r0c0 * m2.r0c2) + (m1.r0c1 * m2.r1c2) + (m1.r0c2 * m2.r2c2) + (m1.r0c3 * m2.r3c2), 
		(m1.r0c0 * m2.r0c3) + (m1.r0c1 * m2.r1c3) + (m1.r0c2 * m2.r2c3) + (m1.r0c3 * m2.r3c3), 
		
		(m1.r1c0 * m2.r0c0) + (m1.r1c1 * m2.r1c0) + (m1.r1c2 * m2.r2c0) + (m1.r1c3 * m2.r3c0), 
		(m1.r1c0 * m2.r0c2) + (m1.r1c1 * m2.r1c1) + (m1.r1c2 * m2.r2c1) + (m1.r1c3 * m2.r3c1), 
		(m1.r1c0 * m2.r0c2) + (m1.r1c1 * m2.r1c2) + (m1.r1c2 * m2.r2c2) + (m1.r1c3 * m2.r3c2), 
		(m1.r1c0 * m2.r0c3) + (m1.r1c1 * m2.r1c3) + (m1.r1c2 * m2.r2c3) + (m1.r1c3 * m2.r3c3), 
		
		(m1.r2c0 * m2.r0c0) + (m1.r2c1 * m2.r1c0) + (m1.r2c2 * m2.r2c0) + (m1.r2c3 * m2.r3c0), 
		(m1.r2c0 * m2.r0c1) + (m1.r2c1 * m2.r1c1) + (m1.r2c2 * m2.r2c1) + (m1.r2c3 * m2.r3c1), 
		(m1.r2c0 * m2.r0c2) + (m1.r2c1 * m2.r1c2) + (m1.r2c2 * m2.r2c2) + (m1.r2c3 * m2.r3c2), 
		(m1.r2c0 * m2.r0c3) + (m1.r2c1 * m2.r1c3) + (m1.r2c2 * m2.r2c3) + (m1.r2c3 * m2.r3c3), 
		
		(m1.r3c0 * m2.r0c0) + (m1.r3c1 * m2.r1c0) + (m1.r3c2 * m2.r2c0) + (m1.r3c3 * m2.r3c0), 
		(m1.r3c0 * m2.r0c1) + (m1.r3c1 * m2.r1c1) + (m1.r3c2 * m2.r2c1) + (m1.r3c3 * m2.r3c1), 
		(m1.r3c0 * m2.r0c2) + (m1.r3c1 * m2.r1c2) + (m1.r3c2 * m2.r2c2) + (m1.r3c3 * m2.r3c2), 
		(m1.r3c0 * m2.r0c3) + (m1.r3c1 * m2.r1c3) + (m1.r3c2 * m2.r2c3) + (m1.r3c3 * m2.r3c3)
		);
#endif
}
MALIB_API MAT4x4 Multiply(const MAT4x4& m, const VEC4& column)
{
#if 0
	return MAT4x4(
		m.m[ 0] * column.x, m.m[ 1] * column.x, m.m[ 2] * column.x, m.m[ 3] * column.x, 
		m.m[ 4] * column.y, m.m[ 5] * column.y, m.m[ 6] * column.y, m.m[ 7] * column.y, 
		m.m[ 8] * column.z, m.m[ 9] * column.z, m.m[10] * column.z, m.m[11] * column.z, 
		m.m[12] * column.w, m.m[13] * column.w, m.m[14] * column.w, m.m[15] * column.w
		);
#else
	return MAT4x4(
		m.r0c0 * column.x, m.r0c1 * column.x, m.r0c2 * column.x, m.r0c3 * column.x, 
		m.r1c0 * column.y, m.r1c1 * column.y, m.r1c2 * column.y, m.r1c3 * column.y, 
		m.r2c0 * column.z, m.r2c1 * column.z, m.r2c2 * column.z, m.r2c3 * column.z, 
		m.r3c0 * column.w, m.r3c1 * column.w, m.r3c2 * column.w, m.r3c3 * column.w
		);
#endif
}
MALIB_API MAT4x4 Translate(float x, float y, float z)
{
	return MAT4x4(
		1.f, 0.f, 0.f, x, 
		0.f, 1.f, 0.f, y, 
		0.f, 0.f, 1.f, z, 
		0.f, 0.f, 0.f, 1.f
		);
}
MALIB_API MAT4x4 RotateX(float x)
{
	return MAT4x4(
		1.f, 0.f,    0.f,     0.f, 
		0.f, cos(x), -sin(x), 0.f, 
		0.f, sin(x), cos(x),  0.f, 
		0.f, 0.f,    0.f,     1.f
		);
}
MALIB_API MAT4x4 RotateY(float y)
{
	return MAT4x4(
		cos(y),  0.f, sin(y), 0.f, 
		0.f,     1.f, 0.f,    0.f, 
		-sin(y), 0.f, cos(y), 0.f, 
		0.f,     0.f, 0.f,    1.f
		);
}
MALIB_API MAT4x4 RotateZ(float z)
{
	return MAT4x4(
		cos(z), -sin(z), 0.f, 0.f, 
		sin(z), cos(z),  0.f, 0.f, 
		0.f,    0.f,     1.f, 0.f, 
		0.f,    0.f,     0.f, 1.f
		);
}
MALIB_API MAT4x4 Rotate(float x, float y, float z)
{
	MAT4x4 m;

	if (x != 0.0f) m *= MAT4x4(
		1.f, 0.f,    0.f,     0.f, 
		0.f, cos(x), -sin(x), 0.f, 
		0.f, sin(x), cos(x),  0.f, 
		0.f, 0.f,    0.f,     1.f
		);
	if (y != 0.0f) m *= MAT4x4(
		cos(y),  0.f, sin(y), 0.f, 
		0.f,     1.f, 0.f,    0.f, 
		-sin(y), 0.f, cos(y), 0.f, 
		0.f,     0.f, 0.f,    1.f
		);
	if (z != 0.0f) m *= MAT4x4(
		cos(z), -sin(z), 0.f, 0.f, 
		sin(z), cos(z),  0.f, 0.f, 
		0.f,    0.f,     1.f, 0.f, 
		0.f,    0.f,     0.f, 1.f
		);

	return m;
}
MALIB_API MAT4x4 RotateAround(const VEC3& v, float x)
{
	return MAT4x4();
}
MALIB_API MAT4x4 Scale(float x, float y, float z)
{
	return MAT4x4(
		x,   0.f, 0.f, 0.f, 
		0.f, y,   0.f, 0.f, 
		0.f, 0.f, z,   0.f, 
		0.f, 0.f, 0.f, 1.f
		);
}
MALIB_API MAT4x4 Perspective(float fovAngleY, float aspectRatio, float nearZ, float farZ)
{
	float cosFov = cos(fovAngleY * 0.5f);
	float sinFov = sin(fovAngleY * 0.5f);
    float height = cosFov / sinFov;
    float width = height / aspectRatio;
	float zinterp = farZ / (farZ - nearZ);
	return MAT4x4(
		width, 0.f,    0.f,     0.f, 
		0.f,   height, 0.f,     0.f, 
		0.f,   0.f,    zinterp, -zinterp * nearZ, 
		0.f,   0.f,    0.f,     1.f
		);
}
MALIB_API MAT4x4 Orthographic(float width, float height, float nearZ, float farZ)
{
	float range = 1.f / (farZ- nearZ);
	return MAT4x4(
		2.f / width, 0.f,          0.f,   0.f, 
		0.f,         2.f / height, 0.f,   0.f, 
		0.f,         0.f,          range, -range * nearZ, 
		0.f,         0.f,          0.f,   1.f
		);
}
MALIB_API MAT4x4 LookAt(const VEC4& eye, const VEC4& focus)
{
	static VEC3 up(0.0f, 1.0f, 0.0f);
	VEC3 f = CreateVector(eye, focus, true);
	VEC3 s = Cross(f, up);
	VEC3 t = Cross(s, f);
#if 0
	return MAT4x4(
		s.x,  s.y,  s.z,  0.f, 
		t.x,  t.y,  t.z,  0.f, 
		-f.x, -f.y, -f.z, 0.f, 
		0.f,  0.f,  0.f,  1.f
		);
#else
	return MAT4x4(
		s.x,  s.y,  s.z,  0.f, 
		t.x,  t.y,  t.z,  0.f, 
		-f.x, -f.y, -f.z, 0.f, 
		0.f,  0.f,  0.f,  1.f
		) * MAT4x4(
		1.f, 0.f, 0.f, -eye.x, 
		0.f, 1.f, 0.f, -eye.y, 
		0.f, 0.f, 1.f, -eye.z, 
		0.f, 0.f, 0.f, 1.f
		);
#endif
}

MALIB_API MAT4x4::MAT4x4()
{
#if 0
	this->m[0]  = 1.f; this->m[1]  = 0.f; this->m[2]  = 0.f; this->m[3]  = 0.f;
	this->m[4]  = 0.f; this->m[5]  = 1.f; this->m[6]  = 0.f; this->m[7]  = 0.f;
	this->m[8]  = 0.f; this->m[9]  = 0.f; this->m[10] = 1.f; this->m[11] = 0.f;
	this->m[12] = 0.f; this->m[13] = 0.f; this->m[14] = 0.f; this->m[15] = 1.f;
#else
	this->r0c0 = 1.f; this->r0c1 = 0.f; this->r0c2 = 0.f; this->r0c3 = 0.f;
	this->r1c0 = 0.f; this->r1c1 = 1.f; this->r1c2 = 0.f; this->r1c3 = 0.f;
	this->r2c0 = 0.f; this->r2c1 = 0.f; this->r2c2 = 1.f; this->r2c3 = 0.f;
	this->r3c0 = 0.f; this->r3c1 = 0.f; this->r3c2 = 0.f; this->r3c3 = 1.f;
#endif
}
MALIB_API MAT4x4::MAT4x4(const VEC4 &col1, const VEC4 &col2, const VEC4 &col3, const VEC4 &col4)
{
#if 0
	this->m[0]  = col1.x; this->m[1]  = col2.x;	this->m[2]  = col3.x;	this->m[3]  = col4.x;
	this->m[4]  = col1.y; this->m[5]  = col2.y;	this->m[6]  = col3.y;	this->m[7]  = col4.y;
	this->m[8]  = col1.z; this->m[9]  = col2.z;	this->m[10] = col3.z;	this->m[11] = col4.z;
	this->m[12] = col1.w; this->m[13] = col2.w;	this->m[14] = col3.w;	this->m[15] = col4.w;
#else
	this->r0c0 = col1.x; this->r0c1 = col2.x; this->r0c2 = col3.x; this->r0c3 = col4.x;
	this->r1c0 = col1.y; this->r1c1 = col2.y; this->r1c2 = col3.y; this->r1c3 = col4.y;
	this->r2c0 = col1.z; this->r2c1 = col2.z; this->r2c2 = col3.z; this->r2c3 = col4.z;
	this->r3c0 = col1.w; this->r3c1 = col2.w; this->r3c2 = col3.w; this->r3c3 = col4.w;
#endif
}
MALIB_API MAT4x4::MAT4x4(const float col1[4], const float col2[4], const float col3[4], const float col4[4])
{
#if 0
	this->m[0]  = col1[0]; this->m[1]  = col2[0]; this->m[2]  = col3[0]; this->m[3]  = col4[0];
	this->m[4]  = col1[1]; this->m[5]  = col2[1]; this->m[6]  = col3[1]; this->m[7]  = col4[1];
	this->m[8]  = col1[2]; this->m[9]  = col2[2]; this->m[10] = col3[2]; this->m[11] = col4[2];
	this->m[12] = col1[3]; this->m[13] = col2[3]; this->m[14] = col3[3]; this->m[15] = col4[3];
#else
	this->r0c0 = col1[0]; this->r0c1 = col2[0]; this->r0c2 = col3[0]; this->r0c3 = col4[0];
	this->r1c0 = col1[1]; this->r1c1 = col2[1]; this->r1c2 = col3[1]; this->r1c3 = col4[1];
	this->r2c0 = col1[2]; this->r2c1 = col2[2]; this->r2c2 = col3[2]; this->r2c3 = col4[2];
	this->r3c0 = col1[3]; this->r3c1 = col2[3]; this->r3c2 = col3[3]; this->r3c3 = col4[3];
#endif
}
MALIB_API MAT4x4::MAT4x4(const float m[16])
{
#if 0
	this->m[0]  = m[0];  this->m[1]  = m[1];  this->m[2]  = m[2];  this->m[3]  = m[3];
	this->m[4]  = m[4];  this->m[5]  = m[5];  this->m[6]  = m[6];  this->m[7]  = m[7];
	this->m[8]  = m[8];  this->m[9]  = m[9];  this->m[10] = m[10]; this->m[11] = m[11];
	this->m[12] = m[12]; this->m[13] = m[13]; this->m[14] = m[14]; this->m[15] = m[15];
#else
	this->r0c0 = m[ 0]; this->r0c1 = m[ 1]; this->r0c2 = m[ 2]; this->r0c3 = m[ 3];
	this->r1c0 = m[ 4]; this->r1c1 = m[ 5]; this->r1c2 = m[ 6]; this->r1c3 = m[ 7];
	this->r2c0 = m[ 8]; this->r2c1 = m[ 9]; this->r2c2 = m[10]; this->r2c3 = m[11];
	this->r3c0 = m[12]; this->r3c1 = m[13]; this->r3c2 = m[14]; this->r3c3 = m[15];
#endif
}
MALIB_API MAT4x4::MAT4x4(float f00, float f01, float f02, float f03, float f10, float f11, float f12, float f13, float f20, float f21, float f22, float f23, float f30, float f31, float f32, float f33)
{
#if 0
	this->m[0]  = f00; this->m[1]  = f01; this->m[2]  = f02; this->m[3]  = f03;
	this->m[4]  = f10; this->m[5]  = f11; this->m[6]  = f12; this->m[7]  = f13;
	this->m[8]  = f20; this->m[9]  = f21; this->m[10] = f22; this->m[11] = f23;
	this->m[12] = f30; this->m[13] = f31; this->m[14] = f32; this->m[15] = f33;
#else
	this->r0c0 = f00; this->r0c1 = f01; this->r0c2 = f02; this->r0c3 = f03;
	this->r1c0 = f10; this->r1c1 = f11; this->r1c2 = f12; this->r1c3 = f13;
	this->r2c0 = f20; this->r2c1 = f21; this->r2c2 = f22; this->r2c3 = f23;
	this->r3c0 = f30; this->r3c1 = f31; this->r3c2 = f23; this->r3c3 = f33;
#endif
}
MALIB_API MAT4x4::MAT4x4(const MAT4x4& m)
{
#if 0
	this->m[ 0] = m.m[ 0]; this->m[ 1] = m.m[ 1]; this->m[ 2] = m.m[ 2]; this->m[ 3] = m.m[ 3];
	this->m[ 4] = m.m[ 4]; this->m[ 5] = m.m[ 5]; this->m[ 6] = m.m[ 6]; this->m[ 7] = m.m[ 7];
	this->m[ 8] = m.m[ 8]; this->m[ 9] = m.m[ 9]; this->m[10] = m.m[10]; this->m[11] = m.m[11];
	this->m[12] = m.m[12]; this->m[13] = m.m[13]; this->m[14] = m.m[14]; this->m[15] = m.m[15];
#else
	this->r0c0 = m.r0c0; this->r0c1 = m.r0c1; this->r0c2 = m.r0c2; this->r0c3 = m.r0c3;
	this->r1c0 = m.r1c0; this->r1c1 = m.r1c1; this->r1c2 = m.r1c2; this->r1c3 = m.r1c3;
	this->r2c0 = m.r2c0; this->r2c1 = m.r2c1; this->r2c2 = m.r2c2; this->r2c3 = m.r2c3;
	this->r3c0 = m.r3c0; this->r3c1 = m.r3c1; this->r3c2 = m.r3c2; this->r3c3 = m.r3c3;
#endif
}
MALIB_API MAT4x4::~MAT4x4()
{
}

MALIB_API MAT4x4 MAT4x4::operator*(const MAT4x4 &m)
{
	return Multiply(*this, m);
}
MALIB_API MAT4x4 MAT4x4::operator*(const VEC4 &column)
{
	return Multiply(*this, column);
}
MALIB_API void MAT4x4::operator*=(const MAT4x4 &m)
{
	*this = Multiply(*this, m);
}
MALIB_API void MAT4x4::operator*=(const VEC4 &column)
{
	*this = Multiply(*this, column);
}
MALIB_API void MAT4x4::operator=(const MAT4x4& m)
{
#if 0
	this->m[ 0] = m.m[ 0]; this->m[ 1] = m.m[ 1]; this->m[ 2] = m.m[ 2]; this->m[ 3] = m.m[ 3];
	this->m[ 4] = m.m[ 4]; this->m[ 5] = m.m[ 5]; this->m[ 6] = m.m[ 6]; this->m[ 7] = m.m[ 7];
	this->m[ 8] = m.m[ 8]; this->m[ 9] = m.m[ 9]; this->m[10] = m.m[10]; this->m[11] = m.m[11];
	this->m[12] = m.m[12]; this->m[13] = m.m[13]; this->m[14] = m.m[14]; this->m[15] = m.m[15];
#else
	this->r0c0 = m.r0c0; this->r0c1 = m.r0c1; this->r0c2 = m.r0c2; this->r0c3 = m.r0c3;
	this->r1c0 = m.r1c0; this->r1c1 = m.r1c1; this->r1c2 = m.r1c2; this->r1c3 = m.r1c3;
	this->r2c0 = m.r2c0; this->r2c1 = m.r2c1; this->r2c2 = m.r2c2; this->r2c3 = m.r2c3;
	this->r3c0 = m.r3c0; this->r3c1 = m.r3c1; this->r3c2 = m.r3c2; this->r3c3 = m.r3c3;
#endif
}

_MALIB_END
#endif