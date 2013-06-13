#include "StdAfx.h"

MATRIX4x4::MATRIX4x4()
{
	this->toIdentity();
}
MATRIX4x4::MATRIX4x4(const VERTEX4 &v1, const VERTEX4 &v2, const VERTEX4 &v3, const VERTEX4 &v4)
{
	this->m[0]  = v1.x; this->m[1]  = v1.y;	this->m[2]  = v1.z;	this->m[3]  = v1.w;
	this->m[4]  = v2.x;	this->m[5]  = v2.y;	this->m[6]  = v2.z;	this->m[7]  = v2.w;
	this->m[8]  = v3.x;	this->m[9]  = v3.y;	this->m[10] = v3.z;	this->m[11] = v3.w;
	this->m[12] = v4.x;	this->m[13] = v4.y;	this->m[14] = v4.z;	this->m[15] = v4.w;
}
MATRIX4x4::MATRIX4x4(const float v1[4], const float v2[4], const float v3[4], const float v4[4])
{
	this->m[0]  = v1[0]; this->m[1]  = v1[1]; this->m[2]  = v1[2]; this->m[3]  = v1[3];
	this->m[4]  = v2[0]; this->m[5]  = v2[1]; this->m[6]  = v2[2]; this->m[7]  = v2[3];
	this->m[8]  = v3[0]; this->m[9]  = v3[1]; this->m[10] = v3[2]; this->m[11] = v3[3];
	this->m[12] = v4[0]; this->m[13] = v4[1]; this->m[14] = v4[2]; this->m[15] = v4[3];
}
MATRIX4x4::MATRIX4x4(const float m[16])
{
	this->m[0]  = m[0];  this->m[1]  = m[1];  this->m[2]  = m[2];  this->m[3]  = m[3];
	this->m[4]  = m[4];  this->m[5]  = m[5];  this->m[6]  = m[6];  this->m[7]  = m[7];
	this->m[8]  = m[8];  this->m[9]  = m[9];  this->m[10] = m[10]; this->m[11] = m[11];
	this->m[12] = m[12]; this->m[13] = m[13]; this->m[14] = m[14]; this->m[15] = m[15];
}
MATRIX4x4::MATRIX4x4(float f00, float f01, float f02, float f03, float f10, float f11, float f12, float f13, float f20, float f21, float f22, float f23, float f30, float f31, float f32, float f33)
{
	this->m[0]  = f00; this->m[1]  = f01; this->m[2]  = f02; this->m[3]  = f03;
	this->m[4]  = f10; this->m[5]  = f11; this->m[6]  = f12; this->m[7]  = f13;
	this->m[8]  = f20; this->m[9]  = f21; this->m[10] = f22; this->m[11] = f23;
	this->m[12] = f30; this->m[13] = f31; this->m[14] = f32; this->m[15] = f33;
}
MATRIX4x4::~MATRIX4x4()
{
}

MATRIX4x4 MATRIX4x4::operator*(const MATRIX4x4 &m)
{
	return MATRIX4x4(
		(this->m[0] * m.m[0]) + (this->m[1] * m.m[4]) + (this->m[2] * m.m[8]) + (this->m[3] * m.m[12]), 
		(this->m[0] * m.m[1]) + (this->m[1] * m.m[5]) + (this->m[2] * m.m[9]) + (this->m[3] * m.m[13]), 
		(this->m[0] * m.m[0]) + (this->m[1] * m.m[6]) + (this->m[2] * m.m[10]) + (this->m[3] * m.m[14]), 
		(this->m[0] * m.m[0]) + (this->m[1] * m.m[7]) + (this->m[2] * m.m[11]) + (this->m[3] * m.m[15]), 

		(this->m[4] * m.m[0]) + (this->m[5] * m.m[4]) + (this->m[6] * m.m[8]) + (this->m[7] * m.m[12]), 
		(this->m[4] * m.m[1]) + (this->m[5] * m.m[5]) + (this->m[6] * m.m[9]) + (this->m[7] * m.m[13]), 
		(this->m[4] * m.m[2]) + (this->m[5] * m.m[6]) + (this->m[6] * m.m[10]) + (this->m[7] * m.m[14]), 
		(this->m[4] * m.m[3]) + (this->m[5] * m.m[7]) + (this->m[6] * m.m[11]) + (this->m[7] * m.m[15]), 

		(this->m[8] * m.m[0]) + (this->m[9] * m.m[4]) + (this->m[10] * m.m[8]) + (this->m[11] * m.m[12]), 
		(this->m[8] * m.m[1]) + (this->m[9] * m.m[5]) + (this->m[10] * m.m[9]) + (this->m[11] * m.m[13]), 
		(this->m[8] * m.m[2]) + (this->m[9] * m.m[6]) + (this->m[10] * m.m[10]) + (this->m[11] * m.m[14]), 
		(this->m[8] * m.m[3]) + (this->m[9] * m.m[7]) + (this->m[10] * m.m[11]) + (this->m[11] * m.m[15]), 

		(this->m[12] * m.m[0]) + (this->m[13] * m.m[4]) + (this->m[10] * m.m[8]) + (this->m[15] * m.m[12]), 
		(this->m[12] * m.m[1]) + (this->m[13] * m.m[5]) + (this->m[10] * m.m[9]) + (this->m[15] * m.m[13]), 
		(this->m[12] * m.m[2]) + (this->m[13] * m.m[6]) + (this->m[10] * m.m[10]) + (this->m[15] * m.m[14]), 
		(this->m[12] * m.m[3]) + (this->m[13] * m.m[7]) + (this->m[10] * m.m[11]) + (this->m[15] * m.m[15])
		);
}
MATRIX4x4 MATRIX4x4::operator*(const VERTEX4 &v)
{
	return MATRIX4x4(
		this->m[0]  * v.x, this->m[1]  * v.x, this->m[2]  * v.x, this->m[3]  * v.x, 
		this->m[4]  * v.y, this->m[5]  * v.y, this->m[6]  * v.y, this->m[7]  * v.y, 
		this->m[8]  * v.z, this->m[9]  * v.z, this->m[10] * v.z, this->m[11] * v.z, 
		this->m[12] * v.w, this->m[13] * v.w, this->m[14] * v.w, this->m[15] * v.w
		);
}
void MATRIX4x4::operator*=(const MATRIX4x4 &m)
{
	this->m[0]  = (this->m[0] * m.m[0]) + (this->m[1] * m.m[4]) + (this->m[2] * m.m[8]) + (this->m[3] * m.m[12]),
	this->m[1]  = (this->m[0] * m.m[1]) + (this->m[1] * m.m[5]) + (this->m[2] * m.m[9]) + (this->m[3] * m.m[13]);
	this->m[2]  = (this->m[0] * m.m[0]) + (this->m[1] * m.m[6]) + (this->m[2] * m.m[10]) + (this->m[3] * m.m[14]);
	this->m[3]  = (this->m[0] * m.m[0]) + (this->m[1] * m.m[7]) + (this->m[2] * m.m[11]) + (this->m[3] * m.m[15]);

	this->m[4]  = (this->m[4] * m.m[0]) + (this->m[5] * m.m[4]) + (this->m[6] * m.m[8]) + (this->m[7] * m.m[12]);
	this->m[5]  = (this->m[4] * m.m[1]) + (this->m[5] * m.m[5]) + (this->m[6] * m.m[9]) + (this->m[7] * m.m[13]);
	this->m[6]  = (this->m[4] * m.m[2]) + (this->m[5] * m.m[6]) + (this->m[6] * m.m[10]) + (this->m[7] * m.m[14]);
	this->m[7]  = (this->m[4] * m.m[3]) + (this->m[5] * m.m[7]) + (this->m[6] * m.m[11]) + (this->m[7] * m.m[15]);

	this->m[8]  = (this->m[8] * m.m[0]) + (this->m[9] * m.m[4]) + (this->m[10] * m.m[8]) + (this->m[11] * m.m[12]);
	this->m[9]  = (this->m[8] * m.m[1]) + (this->m[9] * m.m[5]) + (this->m[10] * m.m[9]) + (this->m[11] * m.m[13]);
	this->m[10] = (this->m[8] * m.m[2]) + (this->m[9] * m.m[6]) + (this->m[10] * m.m[10]) + (this->m[11] * m.m[14]);
	this->m[11] = (this->m[8] * m.m[3]) + (this->m[9] * m.m[7]) + (this->m[10] * m.m[11]) + (this->m[11] * m.m[15]);

	this->m[12] = (this->m[12] * m.m[0]) + (this->m[13] * m.m[4]) + (this->m[10] * m.m[8]) + (this->m[15] * m.m[12]);
	this->m[13] = (this->m[12] * m.m[1]) + (this->m[13] * m.m[5]) + (this->m[10] * m.m[9]) + (this->m[15] * m.m[13]);
	this->m[14] = (this->m[12] * m.m[2]) + (this->m[13] * m.m[6]) + (this->m[10] * m.m[10]) + (this->m[15] * m.m[14]);
	this->m[15] = (this->m[12] * m.m[3]) + (this->m[13] * m.m[7]) + (this->m[10] * m.m[11]) + (this->m[15] * m.m[15]);
}
void MATRIX4x4::operator*=(const VERTEX4 &v)
{
	this->m[0]  *= v.x; this->m[1]  *= v.x; this->m[2]  *= v.x; this->m[3]  *= v.x;
	this->m[4]  *= v.y; this->m[5]  *= v.y; this->m[6]  *= v.y; this->m[7]  *= v.y;
	this->m[8]  *= v.z; this->m[9]  *= v.z; this->m[10] *= v.z; this->m[11] *= v.z;
	this->m[12] *= v.w; this->m[13] *= v.w; this->m[14] *= v.w; this->m[15] *= v.w;
}

void MATRIX4x4::toIdentity()
{
	this->m[0]  = 1.f; this->m[1]  = 0.f; this->m[2]  = 0.f; this->m[3]  = 0.f;
	this->m[4]  = 0.f; this->m[5]  = 1.f; this->m[6]  = 0.f; this->m[7]  = 0.f;
	this->m[8]  = 0.f; this->m[9]  = 0.f; this->m[10] = 1.f; this->m[11] = 0.f;
	this->m[12] = 0.f; this->m[13] = 0.f; this->m[14] = 0.f; this->m[15] = 1.f;
}
void MATRIX4x4::transpose()
{
	MATRIX4x4 tmp(this->m);
	this->m[0]  = tmp.m[0]; this->m[1]  = tmp.m[4]; this->m[2]  = tmp.m[8];  this->m[3]  = tmp.m[12];
	this->m[4]  = tmp.m[1]; this->m[5]  = tmp.m[5]; this->m[6]  = tmp.m[9];  this->m[7]  = tmp.m[13];
	this->m[8]  = tmp.m[2]; this->m[9]  = tmp.m[6]; this->m[10] = tmp.m[10]; this->m[11] = tmp.m[14];
	this->m[12] = tmp.m[3]; this->m[13] = tmp.m[7]; this->m[14] = tmp.m[11]; this->m[15] = tmp.m[15];
}

MATRIX4x4 Indentity()
{
	return MATRIX4x4(
		1.f, 0.f, 0.f, 0.f, 
		0.f, 1.f, 0.f, 0.f, 
		0.f, 0.f, 1.f, 0.f, 
		0.f, 0.f, 0.f, 1.f
		);
}
MATRIX4x4 Translate(float x, float y, float z)
{
	return MATRIX4x4(
		1.f, 0.f, 0.f, x, 
		0.f, 1.f, 0.f, y, 
		0.f, 0.f, 1.f, z, 
		0.f, 0.f, 0.f, 1.f
		);
}
MATRIX4x4 RotateX(float v)
{
	return MATRIX4x4(
		1.f, 0.f,    0.f,     0.f, 
		0.f, cos(v), -sin(v), 0.f, 
		0.f, sin(v), cos(v),  0.f, 
		0.f, 0.f,    0.f,     1.f);
}
MATRIX4x4 RotateY(float v)
{
	return MATRIX4x4(
		cos(v),  0.f, sin(v), 0.f, 
		0.f,     1.f, 0.f,    0.f, 
		-sin(v), 0.f, cos(v), 0.f, 
		0.f,     0.f, 0.f,    1.f);
}
MATRIX4x4 RotateZ(float v)
{
	return MATRIX4x4(
		cos(v), -sin(v), 0.f, 0.f, 
		sin(v), cos(v),  0.f, 0.f, 
		0.f,    0.f,     1.f, 0.f, 
		0.f,    0.f,     0.f, 1.f);
}
MATRIX4x4 Rotate(float x, float y, float z)
{
	MATRIX4x4 m;

	if (x != 0.0f) m *= MATRIX4x4(
		1.f, 0.f,    0.f,     0.f, 
		0.f, cos(x), -sin(x), 0.f, 
		0.f, sin(x), cos(x),  0.f, 
		0.f, 0.f,    0.f,     1.f
		);
	if (y != 0.0f) m *= MATRIX4x4(
		cos(y),  0.f, sin(y), 0.f, 
		0.f,     1.f, 0.f,    0.f, 
		-sin(y), 0.f, cos(y), 0.f, 
		0.f,     0.f, 0.f,    1.f
		);
	if (z != 0.0f) m *= MATRIX4x4(
		cos(z), -sin(z), 0.f, 0.f, 
		sin(z), cos(z),  0.f, 0.f, 
		0.f,    0.f,     1.f, 0.f, 
		0.f,    0.f,     0.f, 1.f
		);

	return m;
}
MATRIX4x4 Scale(float x, float y, float z)
{
	return MATRIX4x4(
		x,   0.f, 0.f, 0.f, 
		0.f, y,   0.f, 0.f, 
		0.f, 0.f, z,   0.f, 
		0.f, 0.f, 0.f, 1.f
		);
}
MATRIX4x4 Perspective(float fovAngleY, float aspectRatio, float nearZ, float farZ)
{
	float cosFov = cos(fovAngleY * 0.5f);
	float sinFov = sin(fovAngleY * 0.5f);
    float height = cosFov / sinFov;
    float width = height / aspectRatio;
	float zinterp = farZ / (farZ - nearZ);
	return MATRIX4x4(
		width, 0.f,    0.f,             0.f, 
		0.f,   height, 0.f,             0.f, 
		0.f,   0.f,    zinterp,         0.f, 
		0.f,   0.f,   -zinterp * nearZ, 1.f
		);
}
MATRIX4x4 Orthographic(float width, float height, float nearZ, float farZ)
{
	float range = 1.f / (farZ- nearZ);
	return MATRIX4x4(
		2.f / width, 0.f,          0.f,             0.f, 
		0.f,         2.f / height, 0.f,             0.f, 
		0.f,         0.f,          range,           0.f, 
		0.f,         0.f,          -range * nearZ,  1.f
		);
}
MATRIX4x4 LookAt(VERTEX4 &position, VERTEX4 &lookingAt)
{
	VERTEX3 up(0.0f, 1.0f, 0.0f);
	VERTEX3 f = CreateVector(position, lookingAt, true);
	VERTEX3 s = CrossProduct(f, up);
	VERTEX3 t = CrossProduct(s, f);
	return MATRIX4x4(
		s.x, t.x, -f.x, 0.f, 
		s.y, t.y, -f.y, 0.f, 
		s.z, t.z, -f.z, 0.f, 
		0.f, 0.f, 0.f, 1.f
		);
}