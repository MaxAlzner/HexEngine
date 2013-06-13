#include "..\main.h"

VERTEX4::VERTEX4()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
	this->w = 1.0f;
}
VERTEX4::VERTEX4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}
VERTEX4::VERTEX4(const VERTEX3 &v, float w)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = w;
}
VERTEX4::VERTEX4(const VERTEX2 &v, float z, float w)
{
	this->x = v.x;
	this->y = v.y;
	this->z = z;
	this->w = w;
}
VERTEX4::VERTEX4(float x, const VERTEX2 &v, float w)
{
	this->x = x;
	this->y = v.x;
	this->z = v.y;
	this->w = w;
}
VERTEX4::VERTEX4(const VERTEX2 &v1, const VERTEX2 &v2)
{
	this->x = v1.x;
	this->y = v1.y;
	this->z = v2.x;
	this->w = v2.y;
}
VERTEX4::~VERTEX4()
{
}

VERTEX4 VERTEX4::operator+(const VERTEX4 &v)
{
	return VERTEX4(this->x + v.x, this->y + v.y, this->z + v.z, this->w + v.w);
}
VERTEX4 VERTEX4::operator-(const VERTEX4 &v)
{
	return VERTEX4(this->x - v.x, this->y - v.y, this->z - v.z, this->w - v.w);
}
VERTEX4 VERTEX4::operator*(const VERTEX4 &v)
{
	return VERTEX4(this->x * v.x, this->y * v.y, this->z * v.z, this->w * v.w);
}
VERTEX4 VERTEX4::operator/(const VERTEX4 &v)
{
	return VERTEX4(this->x / v.x, this->y / v.y, this->z / v.z, this->w / v.w);
}
VERTEX4 VERTEX4::operator+(const VERTEX3 &v)
{
	return VERTEX4(this->x + v.x, this->y + v.y, this->z + v.z, this->w);
}
VERTEX4 VERTEX4::operator-(const VERTEX3 &v)
{
	return VERTEX4(this->x - v.x, this->y - v.y, this->z - v.z, this->w);
}
VERTEX4 VERTEX4::operator*(const VERTEX3 &v)
{
	return VERTEX4(this->x * v.x, this->y * v.y, this->z * v.z, this->w);
}
VERTEX4 VERTEX4::operator/(const VERTEX3 &v)
{
	return VERTEX4(this->x / v.x, this->y / v.y, this->z / v.z, this->w);
}
VERTEX4 VERTEX4::operator+(const VERTEX2 &v)
{
	return VERTEX4(this->x + v.x, this->y + v.y, this->z, this->w);
}
VERTEX4 VERTEX4::operator-(const VERTEX2 &v)
{
	return VERTEX4(this->x - v.x, this->y - v.y, this->z, this->w);
}
VERTEX4 VERTEX4::operator*(const VERTEX2 &v)
{
	return VERTEX4(this->x * v.x, this->y * v.y, this->z, this->w);
}
VERTEX4 VERTEX4::operator/(const VERTEX2 &v)
{
	return VERTEX4(this->x / v.x, this->y / v.y, this->z, this->w);
}
VERTEX4 VERTEX4::operator+(float scalar)
{
	return VERTEX4(this->x + scalar, this->y + scalar, this->z + scalar, this->w + scalar);
}
VERTEX4 VERTEX4::operator-(float scalar)
{
	return VERTEX4(this->x - scalar, this->y - scalar, this->z - scalar, this->w - scalar);
}
VERTEX4 VERTEX4::operator*(float scalar)
{
	return VERTEX4(this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar);
}
VERTEX4 VERTEX4::operator/(float scalar)
{
	return VERTEX4(this->x / scalar, this->y / scalar, this->z / scalar, this->w / scalar);
}
void VERTEX4::operator+=(const VERTEX4 &v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	this->w += v.w;
}
void VERTEX4::operator-=(const VERTEX4 &v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	this->w -= v.w;
}
void VERTEX4::operator*=(const VERTEX4 &v)
{
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;
	this->w *= v.w;
}
void VERTEX4::operator/=(const VERTEX4 &v)
{
	this->x /= v.x;
	this->y /= v.y;
	this->z /= v.z;
	this->w /= v.w;
}
void VERTEX4::operator+=(const VERTEX3 &v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
}
void VERTEX4::operator-=(const VERTEX3 &v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
}
void VERTEX4::operator*=(const VERTEX3 &v)
{
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;
}
void VERTEX4::operator/=(const VERTEX3 &v)
{
	this->x /= v.x;
	this->y /= v.y;
	this->z /= v.z;
}
void VERTEX4::operator+=(const VERTEX2 &v)
{
	this->x += v.x;
	this->y += v.y;
}
void VERTEX4::operator-=(const VERTEX2 &v)
{
	this->x -= v.x;
	this->y -= v.y;
}
void VERTEX4::operator*=(const VERTEX2 &v)
{
	this->x *= v.x;
	this->y *= v.y;
}
void VERTEX4::operator/=(const VERTEX2 &v)
{
	this->x /= v.x;
	this->y /= v.y;
}
void VERTEX4::operator+=(float scalar)
{
	this->x += scalar;
	this->y += scalar;
	this->z += scalar;
	this->w += scalar;
}
void VERTEX4::operator-=(float scalar)
{
	this->x -= scalar;
	this->y -= scalar;
	this->z -= scalar;
	this->w -= scalar;
}
void VERTEX4::operator*=(float scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	this->z *= scalar;
	this->w *= scalar;
}
void VERTEX4::operator/=(float scalar)
{
	this->x /= scalar;
	this->y /= scalar;
	this->z /= scalar;
	this->w /= scalar;
}

float VERTEX4::magnitude()
{
	return sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z) + (this->w * this->w));
}
void VERTEX4::normalize()
{
	float m = this->magnitude();
	if (m == 0) return;
	this->x /= m;
	this->y /= m;
	this->z /= m;
	this->w /= m;
}
void VERTEX4::homogenize()
{
	if (this->w == 0) return;
	this->x /= this->w;
	this->y /= this->w;
	this->z /= this->w;
	this->w /= this->w;
}

VERTEX3::VERTEX3()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}
VERTEX3::VERTEX3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
VERTEX3::VERTEX3(const VERTEX2 &v, float z)
{
	this->x = v.x;
	this->y = v.y;
	this->z = z;
}
VERTEX3::VERTEX3(float x, const VERTEX2 &v)
{
	this->x = x;
	this->y = v.x;
	this->z = v.y;
}
VERTEX3::VERTEX3(const VERTEX4 &v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}
VERTEX3::~VERTEX3()
{
}

VERTEX3 VERTEX3::operator+(const VERTEX4 &v)
{
	return VERTEX3(this->x + v.x, this->y + v.y, this->z + v.z);
}
VERTEX3 VERTEX3::operator-(const VERTEX4 &v)
{
	return VERTEX3(this->x - v.x, this->y - v.y, this->z - v.z);
}
VERTEX3 VERTEX3::operator*(const VERTEX4 &v)
{
	return VERTEX3(this->x * v.x, this->y * v.y, this->z * v.z);
}
VERTEX3 VERTEX3::operator/(const VERTEX4 &v)
{
	return VERTEX3(this->x / v.x, this->y / v.y, this->z / v.z);
}
VERTEX3 VERTEX3::operator+(const VERTEX3 &v)
{
	return VERTEX3(this->x + v.x, this->y + v.y, this->z + v.z);
}
VERTEX3 VERTEX3::operator-(const VERTEX3 &v)
{
	return VERTEX3(this->x - v.x, this->y - v.y, this->z - v.z);
}
VERTEX3 VERTEX3::operator*(const VERTEX3 &v)
{
	return VERTEX3(this->x * v.x, this->y * v.y, this->z * v.z);
}
VERTEX3 VERTEX3::operator/(const VERTEX3 &v)
{
	return VERTEX3(this->x / v.x, this->y / v.y, this->z / v.z);
}
VERTEX3 VERTEX3::operator+(const VERTEX2 &v)
{
	return VERTEX3(this->x + v.x, this->y + v.y, this->z);
}
VERTEX3 VERTEX3::operator-(const VERTEX2 &v)
{
	return VERTEX3(this->x - v.x, this->y - v.y, this->z);
}
VERTEX3 VERTEX3::operator*(const VERTEX2 &v)
{
	return VERTEX3(this->x * v.x, this->y * v.y, this->z);
}
VERTEX3 VERTEX3::operator/(const VERTEX2 &v)
{
	return VERTEX3(this->x / v.x, this->y / v.y, this->z);
}
VERTEX3 VERTEX3::operator+(float scalar)
{
	return VERTEX3(this->x + scalar, this->y + scalar, this->z + scalar);
}
VERTEX3 VERTEX3::operator-(float scalar)
{
	return VERTEX3(this->x - scalar, this->y - scalar, this->z - scalar);
}
VERTEX3 VERTEX3::operator*(float scalar)
{
	return VERTEX3(this->x * scalar, this->y * scalar, this->z * scalar);
}
VERTEX3 VERTEX3::operator/(float scalar)
{
	return VERTEX3(this->x / scalar, this->y / scalar, this->z / scalar);
}
void VERTEX3::operator+=(const VERTEX4 &v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
}
void VERTEX3::operator-=(const VERTEX4 &v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
}
void VERTEX3::operator*=(const VERTEX4 &v)
{
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;
}
void VERTEX3::operator/=(const VERTEX4 &v)
{
	this->x /= v.x;
	this->y /= v.y;
	this->z /= v.z;
}
void VERTEX3::operator+=(const VERTEX3 &v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
}
void VERTEX3::operator-=(const VERTEX3 &v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
}
void VERTEX3::operator*=(const VERTEX3 &v)
{
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;
}
void VERTEX3::operator/=(const VERTEX3 &v)
{
	this->x /= v.x;
	this->y /= v.y;
	this->z /= v.z;
}
void VERTEX3::operator+=(const VERTEX2 &v)
{
	this->x += v.x;
	this->y += v.y;
}
void VERTEX3::operator-=(const VERTEX2 &v)
{
	this->x -= v.x;
	this->y -= v.y;
}
void VERTEX3::operator*=(const VERTEX2 &v)
{
	this->x *= v.x;
	this->y *= v.y;
}
void VERTEX3::operator/=(const VERTEX2 &v)
{
	this->x /= v.x;
	this->y /= v.y;
}
void VERTEX3::operator+=(float scalar)
{
	this->x += scalar;
	this->y += scalar;
	this->z += scalar;
}
void VERTEX3::operator-=(float scalar)
{
	this->x -= scalar;
	this->y -= scalar;
	this->z -= scalar;
}
void VERTEX3::operator*=(float scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	this->z *= scalar;
}
void VERTEX3::operator/=(float scalar)
{
	this->x /= scalar;
	this->y /= scalar;
	this->z /= scalar;
}

float VERTEX3::magnitude()
{
	return sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
}
void VERTEX3::normalize()
{
	float m = this->magnitude();
	if (m == 0) return;
	this->x /= m;
	this->y /= m;
	this->z /= m;
}

VERTEX2::VERTEX2()
{
	this->x = 0.0f;
	this->y = 0.0f;
}
VERTEX2::VERTEX2(float x, float y)
{
	this->x = x;
	this->y = y;
}
VERTEX2::VERTEX2(const VERTEX3 &v)
{
	this->x = v.x;
	this->y = v.y;
}
VERTEX2::VERTEX2(const VERTEX4 &v)
{
	this->x = v.x;
	this->y = v.y;
}
VERTEX2::~VERTEX2()
{
}

VERTEX2 VERTEX2::operator+(const VERTEX4 &v)
{
	return VERTEX2(this->x + v.x, this->y + v.y);
}
VERTEX2 VERTEX2::operator-(const VERTEX4 &v)
{
	return VERTEX2(this->x - v.x, this->y - v.y);
}
VERTEX2 VERTEX2::operator*(const VERTEX4 &v)
{
	return VERTEX2(this->x * v.x, this->y * v.y);
}
VERTEX2 VERTEX2::operator/(const VERTEX4 &v)
{
	return VERTEX2(this->x / v.x, this->y / v.y);
}
VERTEX2 VERTEX2::operator+(const VERTEX3 &v)
{
	return VERTEX2(this->x + v.x, this->y + v.y);
}
VERTEX2 VERTEX2::operator-(const VERTEX3 &v)
{
	return VERTEX2(this->x - v.x, this->y - v.y);
}
VERTEX2 VERTEX2::operator*(const VERTEX3 &v)
{
	return VERTEX2(this->x * v.x, this->y * v.y);
}
VERTEX2 VERTEX2::operator/(const VERTEX3 &v)
{
	return VERTEX2(this->x / v.x, this->y / v.y);
}
VERTEX2 VERTEX2::operator+(const VERTEX2 &v)
{
	return VERTEX2(this->x + v.x, this->y + v.y);
}
VERTEX2 VERTEX2::operator-(const VERTEX2 &v)
{
	return VERTEX2(this->x - v.x, this->y - v.y);
}
VERTEX2 VERTEX2::operator*(const VERTEX2 &v)
{
	return VERTEX2(this->x * v.x, this->y * v.y);
}
VERTEX2 VERTEX2::operator/(const VERTEX2 &v)
{
	return VERTEX2(this->x / v.x, this->y / v.y);
}
VERTEX2 VERTEX2::operator+(float scalar)
{
	return VERTEX2(this->x + scalar, this->y + scalar);
}
VERTEX2 VERTEX2::operator-(float scalar)
{
	return VERTEX2(this->x - scalar, this->y - scalar);
}
VERTEX2 VERTEX2::operator*(float scalar)
{
	return VERTEX2(this->x * scalar, this->y * scalar);
}
VERTEX2 VERTEX2::operator/(float scalar)
{
	return VERTEX2(this->x / scalar, this->y / scalar);
}
void VERTEX2::operator+=(const VERTEX4 &v)
{
	this->x += v.x;
	this->y += v.y;
}
void VERTEX2::operator-=(const VERTEX4 &v)
{
	this->x -= v.x;
	this->y -= v.y;
}
void VERTEX2::operator*=(const VERTEX4 &v)
{
	this->x *= v.x;
	this->y *= v.y;
}
void VERTEX2::operator/=(const VERTEX4 &v)
{
	this->x /= v.x;
	this->y /= v.y;
}
void VERTEX2::operator+=(const VERTEX3 &v)
{
	this->x += v.x;
	this->y += v.y;
}
void VERTEX2::operator-=(const VERTEX3 &v)
{
	this->x -= v.x;
	this->y -= v.y;
}
void VERTEX2::operator*=(const VERTEX3 &v)
{
	this->x *= v.x;
	this->y *= v.y;
}
void VERTEX2::operator/=(const VERTEX3 &v)
{
	this->x /= v.x;
	this->y /= v.y;
}
void VERTEX2::operator+=(const VERTEX2 &v)
{
	this->x += v.x;
	this->y += v.y;
}
void VERTEX2::operator-=(const VERTEX2 &v)
{
	this->x -= v.x;
	this->y -= v.y;
}
void VERTEX2::operator*=(const VERTEX2 &v)
{
	this->x *= v.x;
	this->y *= v.y;
}
void VERTEX2::operator/=(const VERTEX2 &v)
{
	this->x /= v.x;
	this->y /= v.y;
}
void VERTEX2::operator+=(float scalar)
{
	this->x += scalar;
	this->y += scalar;
}
void VERTEX2::operator-=(float scalar)
{
	this->x -= scalar;
	this->y -= scalar;
}
void VERTEX2::operator*=(float scalar)
{
	this->x *= scalar;
	this->y *= scalar;
}
void VERTEX2::operator/=(float scalar)
{
	this->x /= scalar;
	this->y /= scalar;
}

float VERTEX2::magnitude()
{
	return sqrt((this->x * this->x) + (this->y * this->y));
}
void VERTEX2::normalize()
{
	float m = this->magnitude();
	if (m == 0) return;
	this->x /= m;
	this->y /= m;
}

VERTEX3 CreateVector(const VERTEX4 &a, const VERTEX4 &b, bool normalize)
{
	return CreateVector(a.x, a.y, a.z, b.x, b.y, b.z, normalize);
}
VERTEX3 CreateVector(const VERTEX3 &a, const VERTEX3 &b, bool normalize)
{
	return CreateVector(a.x, a.y, a.z, b.x, b.y, b.z, normalize);
}
VERTEX3 CreateVector(const VERTEX4 &a, const VERTEX3 &b, bool normalize)
{
	return CreateVector(a.x, a.y, a.z, b.x, b.y, b.z, normalize);
}
VERTEX3 CreateVector(const VERTEX3 &a, const VERTEX4 &b, bool normalize)
{
	return CreateVector(a.x, a.y, a.z, b.x, b.y, b.z, normalize);
}
VERTEX3 CreateVector(float x1, float y1, float z1, float x2, float y2, float z2, bool normalize)
{
	VERTEX3 v(x2 - x1, y2 - y1, z2 - z1);
	if (normalize) v.normalize();
	return v;
}
VERTEX3 CreateVector(const VERTEX4 &a, const VERTEX4 &b, float &outDist, bool normalize)
{
	return CreateVector(a.x, a.y, a.z, b.x, b.y, b.z, outDist, normalize);
}
VERTEX3 CreateVector(const VERTEX3 &a, const VERTEX3 &b, float &outDist, bool normalize)
{
	return CreateVector(a.x, a.y, a.z, b.x, b.y, b.z, outDist, normalize);
}
VERTEX3 CreateVector(const VERTEX4 &a, const VERTEX3 &b, float &outDist, bool normalize)
{
	return CreateVector(a.x, a.y, a.z, b.x, b.y, b.z, outDist, normalize);
}
VERTEX3 CreateVector(const VERTEX3 &a, const VERTEX4 &b, float &outDist, bool normalize)
{
	return CreateVector(a.x, a.y, a.z, b.x, b.y, b.z, outDist, normalize);
}
VERTEX3 CreateVector(float x1, float y1, float z1, float x2, float y2, float z2, float &outDist, bool normalize)
{
	VERTEX3 v(x2 - x1, y2 - y1, z2 - z1);
	outDist = v.magnitude();
	if (normalize) v.normalize();
	return v;
}

float DotProduct(const VERTEX4 &a, const VERTEX4 &b)
{
	return DotProduct(a.x, a.y, a.z, b.x, b.y, b.z);
}
float DotProduct(const VERTEX3 &a, const VERTEX3 &b)
{
	return DotProduct(a.x, a.y, a.z, b.x, b.y, b.z);
}
float DotProduct(const VERTEX4 &a, const VERTEX3 &b)
{
	return DotProduct(a.x, a.y, a.z, b.x, b.y, b.z);
}
float DotProduct(const VERTEX3 &a, const VERTEX4 &b)
{
	return DotProduct(a.x, a.y, a.z, b.x, b.y, b.z);
}
float DotProduct(float x1, float y1, float z1, float x2, float y2, float z2)
{
	return (x1 * x2) + (y1 * y2) + (z1 * z2);
}
VERTEX3 CrossProduct(const VERTEX4 &a, const VERTEX4 &b)
{
	return CrossProduct(a.x, a.y, a.z, b.x, b.y, b.z);
}
VERTEX3 CrossProduct(const VERTEX3 &a, const VERTEX3 &b)
{
	return CrossProduct(a.x, a.y, a.z, b.x, b.y, b.z);
}
VERTEX3 CrossProduct(const VERTEX4 &a, const VERTEX3 &b)
{
	return CrossProduct(a.x, a.y, a.z, b.x, b.y, b.z);
}
VERTEX3 CrossProduct(const VERTEX3 &a, const VERTEX4 &b)
{
	return CrossProduct(a.x, a.y, a.z, b.x, b.y, b.z);
}
VERTEX3 CrossProduct(float x1, float y1, float z1, float x2, float y2, float z2)
{
	return VERTEX3(
		y1 * z2 - z1 * y2, 
		z1 * x2 - x1 * z2, 
		x1 * y2 - y1 * x2);
}
VERTEX3 Reflect(const VERTEX4 &v, const VERTEX3 &normal)
{
	return Reflect(v.x, v.y, v.z, normal.x, normal.y, normal.z);
}
VERTEX3 Reflect(const VERTEX3 &v, const VERTEX3 &normal)
{
	return Reflect(v.x, v.y, v.z, normal.x, normal.y, normal.z);
}
VERTEX3 Reflect(float x1, float y1, float z1, float x2, float y2, float z2)
{
	VERTEX3 diff(x2 - x1, y2 - y1, z2 - z1);
	return diff * (DotProduct(x2, y2, z2, x1, y1, z1) * 2.0f);
}
VERTEX3 Tangent(const VERTEX4 &v, const VERTEX3 &normal)
{
	return Tangent(v.x, v.y, v.z, normal.x, normal.y, normal.z);
}
VERTEX3 Tangent(const VERTEX3 &v, const VERTEX3 &normal)
{
	return Tangent(v.x, v.y, v.z, normal.x, normal.y, normal.z);
}
VERTEX3 Tangent(float x1, float y1, float z1, float x2, float y2, float z2)
{
	VERTEX3 diff(x2 - x1, y2 - y1, z2 - z1);
	return diff * DotProduct(x2, y2, z2, x1, y1, z1);
}

VERTEX3 CalculateTangent(const VERTEX3 &normal, const VERTEX4 &a, const VERTEX4 &b, const VERTEX4 &c, const VERTEX2 &uv)
{
#if 1
	VERTEX3 c1 = CrossProduct(normal, VERTEX(0.f, 1.f, 0.f));
	VERTEX3 c2 = CrossProduct(normal, VERTEX(0.f, 0.f, 1.f));
	VERTEX3 c3 = CrossProduct(normal, VERTEX(0.f, -1.f, 0.f));
	VERTEX3 c4 = CrossProduct(normal, VERTEX(0.f, 0.f, -1.f));

	VERTEX3 tangent = c1;
	if (c2.magnitude() > tangent.magnitude()) tangent = c2;
	if (c3.magnitude() > tangent.magnitude()) tangent = c3;
	if (c4.magnitude() > tangent.magnitude()) tangent = c4;
#else
	VERTEX3 tangent = CrossProduct(normal, VERTEX(0.f, 1.f, 0.f));
#endif
	return tangent;
}

VERTEX4 Clamp(VERTEX4 &v, float min, float max, bool affectW)
{
	if (v.x < min) v.x = min;
	else if (v.x > max) v.x = max;
	if (v.y < min) v.y = min;
	else if (v.y > max) v.y = max;
	if (v.z < min) v.z = min;
	else if (v.z > max) v.z = max;
	if (affectW)
	{
		if (v.w < min) v.w = min;
		else if (v.w > max) v.w = max;
	}
	return v;
}
VERTEX4 Module(VERTEX4 &v, float denominator, bool affectW)
{
	while (v.x > denominator) v.x -= denominator;
	while (v.x < 0.0) v.x += denominator;
	while (v.y > denominator) v.y -= denominator;
	while (v.y < 0.0) v.y += denominator;
	while (v.z > denominator) v.z -= denominator;
	while (v.z < 0.0) v.z += denominator;
	if (affectW)
	{
		while (v.w > denominator) v.w -= denominator;
		while (v.w < 0.0) v.w += denominator;
	}
	return v;
}
VERTEX3 Clamp(VERTEX3 &v, float min, float max)
{
	if (v.x < min) v.x = min;
	else if (v.x > max) v.x = max;
	if (v.y < min) v.y = min;
	else if (v.y > max) v.y = max;
	if (v.z < min) v.z = min;
	else if (v.z > max) v.z = max;
	return v;
}
VERTEX3 Module(VERTEX3 &v, float denominator)
{
	while (v.x > denominator) v.x -= denominator;
	while (v.x < 0.0) v.x += denominator;
	while (v.y > denominator) v.y -= denominator;
	while (v.y < 0.0) v.y += denominator;
	while (v.z > denominator) v.z -= denominator;
	while (v.z < 0.0) v.z += denominator;
	return v;
}
VERTEX2 Clamp(VERTEX2 &v, float min, float max)
{
	if (v.x < min) v.x = min;
	else if (v.x > max) v.x = max;
	if (v.y < min) v.y = min;
	else if (v.y > max) v.y = max;
	return v;
}
VERTEX2 Module(VERTEX2 &v, float denominator)
{
	while (v.x > denominator) v.x -= denominator;
	while (v.x < 0.0) v.x += denominator;
	while (v.y > denominator) v.y -= denominator;
	while (v.y < 0.0) v.y += denominator;
	return v;
}

float Clamp(float x, float min, float max)
{
	if (x < min) x = min;
	else if (x > max) x = max;
	return x;
}
float Module(float x, float denominator)
{
	while (x > denominator) x -= denominator;
	while (x < 0.0) x += denominator;
	return x;
}
void Swap(float &x, float &y)
{
	float temp = x;
	x = y;
	y = temp;
}
float Max(float x, float y)
{
	if (y < x) return x;
	return y;
}
float Min(float x, float y)
{
	if (y > x) return x;
	return y;
}