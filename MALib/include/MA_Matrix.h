#ifndef _MA_MATRIX_H_
#define _MA_MATRIX_H_
_MALIB_BEGIN

#ifndef _MA_VERTEX_H_
#include "MA_Vertex.h"
#endif

struct MALIB_API MAT4x4;

extern MALIB_API const MAT4x4 Identity;

MALIB_API MAT4x4 ToIdentity(const MAT4x4& m);
MALIB_API MAT4x4 Transpose(const MAT4x4& m);
MALIB_API MAT4x4 Multiply(const MAT4x4& m1, const MAT4x4& m2);
MALIB_API MAT4x4 Multiply(const MAT4x4& m, const VEC4& column);
MALIB_API MAT4x4 Translate(float x, float y, float z);
MALIB_API MAT4x4 RotateX(float x);
MALIB_API MAT4x4 RotateY(float y);
MALIB_API MAT4x4 RotateZ(float z);
MALIB_API MAT4x4 Rotate(float x, float y, float z);
MALIB_API MAT4x4 Scale(float x, float y, float z);
MALIB_API MAT4x4 Perspective(float fovAngleY, float aspectRatio, float nearZ, float farZ);
MALIB_API MAT4x4 Orthographic(float width, float height, float nearZ, float farZ);
MALIB_API MAT4x4 Orthographic(float left, float right, float bottom, float top, float nearZ, float farZ);
MALIB_API MAT4x4 LookAt(const VEC4& eye, const VEC4& focus);

struct MALIB_API MAT4x4
{
	MAT4x4();
	MAT4x4(const VEC4 &col1, const VEC4 &col2, const VEC4 &col3, const VEC4 &col4);
	MAT4x4(const float col1[4], const float col2[4], const float col3[4], const float col4[4]);
	MAT4x4(const float m[16]);
	MAT4x4(float f00, float f01, float f02, float f03, float f10, float f11, float f12, float f13, float f20, float f21, float f22, float f23, float f30, float f31, float f32, float f33);
	MAT4x4(const MAT4x4& m);
	~MAT4x4();
	
	MAT4x4 operator*(const MAT4x4 &m);
	MAT4x4 operator*(const VEC4 &column);
	void operator*=(const MAT4x4 &m);
	void operator*=(const VEC4 &column);
	void operator=(const MAT4x4& m);

#if 0
	float m[16];
#else
	float r0c0, r0c1, r0c2, r0c3;
	float r1c0, r1c1, r1c2, r1c3;
	float r2c0, r2c1, r2c2, r2c3;
	float r3c0, r3c1, r3c2, r3c3;
#endif
};

_MALIB_END
#endif