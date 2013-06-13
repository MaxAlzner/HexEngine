#ifndef __MATRIX_H_
#define __MATRIX_H_

class MATRIX4x4
{
public:
	MATRIX4x4();
	MATRIX4x4(const VERTEX4 &v1, const VERTEX4 &v2, const VERTEX4 &v3, const VERTEX4 &v4);
	MATRIX4x4(const float v1[4], const float v2[4], const float v3[4], const float v4[4]);
	MATRIX4x4(const float m[16]);
	MATRIX4x4(
		float f00, float f01, float f02, float f03, 
		float f10, float f11, float f12, float f13, 
		float f20, float f21, float f22, float f23, 
		float f30, float f31, float f32, float f33);
	~MATRIX4x4();
	
	MATRIX4x4 operator*(const MATRIX4x4 &m);
	MATRIX4x4 operator*(const VERTEX4 &v);
	void operator*=(const MATRIX4x4 &m);
	void operator*=(const VERTEX4 &v);

	void toIdentity();
	void transpose();

	float m[16];
};

typedef MATRIX4x4 MATRIX;

#define MATRIX4x4_SIZE 64

MATRIX4x4 Identity();
MATRIX4x4 Translate(float x, float y, float z);
MATRIX4x4 RotateX(float v);
MATRIX4x4 RotateY(float v);
MATRIX4x4 RotateZ(float v);
MATRIX4x4 Rotate(float x, float y, float z);
MATRIX4x4 Scale(float x, float y, float z);
MATRIX4x4 Perspective(float fovAngleY, float aspectRatio, float nearZ, float farZ);
MATRIX4x4 Orthographic(float width, float height, float nearZ, float farZ);
MATRIX4x4 LookAt(VERTEX4 &position, VERTEX4 &lookingAt);

#endif