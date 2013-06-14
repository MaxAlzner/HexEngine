#ifndef _MA_MATRIX_H_
#define _MA_MATRIX_H_

struct MALIB_API MAT4x4
{
	MAT4x4();
	MAT4x4(const VEC4 &v1, const VEC4 &v2, const VEC4 &v3, const VEC4 &v4);
	MAT4x4(const float v1[4], const float v2[4], const float v3[4], const float v4[4]);
	MAT4x4(const float m[16]);
	MAT4x4(float f00, float f01, float f02, float f03, float f10, float f11, float f12, float f13, float f20, float f21, float f22, float f23, float f30, float f31, float f32, float f33);
	MAT4x4(const MAT4x4& m);
	~MAT4x4();
	
	MAT4x4 operator*(const MAT4x4 &m);
	MAT4x4 operator*(const VEC4 &v);
	void operator*=(const MAT4x4 &m);
	void operator*=(const VEC4 &v);

	float m[16];
};

typedef MAT4x4 MAT;

extern MALIB_API const MAT4x4 MA_Identity;

MALIB_API MAT4x4 ToIdentity(const MAT4x4& m);
MALIB_API MAT4x4 Transpose(const MAT4x4& m);
MALIB_API MAT4x4 Translate(float x, float y, float z);
MALIB_API MAT4x4 Rotate(float x, float y, float z);
MALIB_API MAT4x4 RotateAround(const VEC3& v, float x);
MALIB_API MAT4x4 Scale(float x, float y, float z);
MALIB_API MAT4x4 Perspective(float fovAngleY, float aspectRatio, float nearZ, float farZ);
MALIB_API MAT4x4 Orthographic(float width, float height, float nearZ, float farZ);
MALIB_API MAT4x4 LookAt(const VEC4& position, const VEC4& lookingAt);

#endif