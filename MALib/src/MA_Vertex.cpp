#include "..\include\MALib.h"

#ifdef _MA_VERTEX_H_
_MALIB_BEGIN

MALIB_API VEC3 CreateVector(const VEC4& a, const VEC4& b, bool normalize)
{
	VEC3 v((VEC4)b - a);
	if (normalize) v = Normalize(v);
	return v;
}
MALIB_API VEC3 CreateVector(const VEC3& a, const VEC3& b, bool normalize)
{
	VEC3 v((VEC4)b - a);
	if (normalize) v = Normalize(v);
	return v;
}
MALIB_API VEC3 CreateVector(const VEC4& a, const VEC3& b, bool normalize)
{
	VEC3 v((VEC4)b - a);
	if (normalize) v = Normalize(v);
	return v;
}
MALIB_API VEC3 CreateVector(const VEC3& a, const VEC4& b, bool normalize)
{
	VEC3 v((VEC4)b - a);
	if (normalize) v = Normalize(v);
	return v;
}
MALIB_API VEC3 CreateVector(const VEC4& a, const VEC4& b, float* outDist, bool normalize)
{
	VEC3 v((VEC4)b - a);
	*outDist = Magnitude(v);
	if (normalize) v = Normalize(v);
	return v;
}
MALIB_API VEC3 CreateVector(const VEC3& a, const VEC3& b, float* outDist, bool normalize)
{
	VEC3 v((VEC4)b - a);
	*outDist = Magnitude(v);
	if (normalize) v = Normalize(v);
	return v;
}
MALIB_API VEC3 CreateVector(const VEC4& a, const VEC3& b, float* outDist, bool normalize)
{
	VEC3 v((VEC4)b - a);
	*outDist = Magnitude(v);
	if (normalize) v = Normalize(v);
	return v;
}
MALIB_API VEC3 CreateVector(const VEC3& a, const VEC4& b, float* outDist, bool normalize)
{
	VEC3 v((VEC4)b - a);
	*outDist = Magnitude(v);
	if (normalize) v = Normalize(v);
	return v;
}

MALIB_API float Dot(const VEC4& a, const VEC4& b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}
MALIB_API float Dot(const VEC3& a, const VEC3& b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}
MALIB_API float Dot(const VEC4& a, const VEC3& b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}
MALIB_API float Dot(const VEC3& a, const VEC4& b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}
MALIB_API VEC3 Cross(const VEC4& a, const VEC4& b)
{
	return Normalize(VEC3((a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z), (a.x * b.y) - (a.y * b.x)));
}
MALIB_API VEC3 Cross(const VEC3& a, const VEC3& b)
{
	return Normalize(VEC3((a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z), (a.x * b.y) - (a.y * b.x)));
}
MALIB_API VEC3 Cross(const VEC4& a, const VEC3& b)
{
	return Normalize(VEC3((a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z), (a.x * b.y) - (a.y * b.x)));
}
MALIB_API VEC3 Cross(const VEC3& a, const VEC4& b)
{
	return Normalize(VEC3((a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z), (a.x * b.y) - (a.y * b.x)));
}
MALIB_API VEC3 Reflect(const VEC3& v, const VEC3& normal)
{
	VEC3 r = VEC3(normal) * (Dot(v, normal) * -2.0f);
	return Normalize(r - v);
	//return Normalize(((VEC4)normal - v) * Dot(v, normal) * 2.0f);
}
MALIB_API VEC3 Tangent(const VEC3& v, const VEC3& normal)
{
	VEC3 t = VEC3(normal) * Dot(v, normal);
	return Normalize(t - v);
	//return Normalize(((VEC4)normal - v) * Dot(v, normal));
}
MALIB_API VEC3 Refract(const VEC3& incoming, const VEC3& normal, const float n1, const float n2)
{
	VEC3 i(incoming);
	VEC3 n(normal);
	float eta = n1 / n2;
	float dot = -Dot(incoming, normal);
	float k = 1.0f - eta * eta * (1.0f - dot * dot);
	return Normalize(
		(i * eta) + 
		(n * (eta * dot - sqrt(k)))
		);
}
MALIB_API float Distance(VEC4& a, VEC4& b)
{
	return sqrt(pow(abs(b.x - a.x), 2) + pow(abs(b.y - a.y), 2) + pow(abs(b.z - a.z), 2));
}
MALIB_API float Distance(VEC3& a, VEC3& b)
{
	return sqrt(pow(abs(b.x - a.x), 2) + pow(abs(b.y - a.y), 2) + pow(abs(b.z - a.z), 2));
}
MALIB_API float Distance(VEC4& a, VEC3& b)
{
	return sqrt(pow(abs(b.x - a.x), 2) + pow(abs(b.y - a.y), 2) + pow(abs(b.z - a.z), 2));
}
MALIB_API float Distance(VEC3& a, VEC4& b)
{
	return sqrt(pow(abs(b.x - a.x), 2) + pow(abs(b.y - a.y), 2) + pow(abs(b.z - a.z), 2));
}

MALIB_API float Magnitude(VEC4& v)
{
	return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
}
MALIB_API float Magnitude(VEC3& v)
{
	return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}
MALIB_API float Magnitude(VEC2& v)
{
	return sqrt((v.x * v.x) + (v.y * v.y));
}
MALIB_API VEC4 Normalize(VEC4& v)
{
	float m = Magnitude(v);
	if (m == 0.0f) return VEC4(0.0f);
	return VEC4(v.x / m, v.y / m, v.z / m, v.w / m);
}
MALIB_API VEC3 Normalize(VEC3& v)
{
	float m = Magnitude(v);
	if (m == 0.0f) return VEC3(0.0f);
	return VEC3(v.x / m, v.y / m, v.z / m);
}
MALIB_API VEC2 Normalize(VEC2& v)
{
	float m = Magnitude(v);
	if (m == 0.0f) return VEC2(0.0f);
	return VEC2(v.x / m, v.y / m);
}
MALIB_API VEC4 Homogenize(VEC4& v)
{
	if (v.w == 0) VEC4(0.0f);
	return VEC4(v.x / v.w, v.y / v.w, v.z / v.w, v.w / v.w);
}

MALIB_API void CalculateNormal(const VEC4& a, const VEC4& b, const VEC4& c, VEC3* outNormal)
{
	VEC3 u = CreateVector(a, b);
	VEC3 v = CreateVector(b, c);
	VEC3 normal;
	normal.x = (u.y * v.z) - (u.z * v.y);
	normal.y = (u.z * v.x) - (u.x * v.z);
	normal.z = (u.x * v.y) - (u.y * v.x);
	normal = Normalize(normal);
	*outNormal = normal;
}
MALIB_API void CalculateTangent(const VEC3& av, const VEC3& bv, const VEC3& cv, const VEC2& at, const VEC2& bt, const VEC2& ct, VEC3* outTangent, VEC3* outBinormal)
{
	// http://www.terathon.com/code/tangent.html
	if (outTangent == NULL) return;

	VEC3 q1 = CreateVector(av, bv);
	VEC3 q2 = CreateVector(av, cv);
	float s1 = bt.x - at.x;
	float t1 = bt.y - at.y;
	float s2 = ct.x - at.x;
	float t2 = ct.y - at.y;

	float det = 1.0f / ((s1 * t2) - (s2 * t1));

	VEC3 t(
		(t2 * q1.x) + (-t1 * q2.x), 
		(t2 * q1.y) + (-t1 * q2.y), 
		(t2 * q1.z) + (-t1 * q2.z)
		);
	VEC3 b(
		(-s2 * q1.x) + (s1 * q2.x), 
		(-s2 * q1.y) + (s1 * q2.y), 
		(-s2 * q1.z) + (s1 * q2.z)
		);
	t *= det;
	b *= det;

	*outTangent = Normalize(t);
	if (outBinormal != NULL) *outBinormal = Normalize(b);
}

MALIB_API VEC4 Clamp(VEC4& v, float min, float max, bool affectW)
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
MALIB_API VEC4 Module(VEC4& v, float denominator, bool affectW)
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
MALIB_API VEC3 Clamp(VEC3& v, float min, float max)
{
	if (v.x < min) v.x = min;
	else if (v.x > max) v.x = max;
	if (v.y < min) v.y = min;
	else if (v.y > max) v.y = max;
	if (v.z < min) v.z = min;
	else if (v.z > max) v.z = max;
	return v;
}
MALIB_API VEC3 Module(VEC3& v, float denominator)
{
	while (v.x > denominator) v.x -= denominator;
	while (v.x < 0.0) v.x += denominator;
	while (v.y > denominator) v.y -= denominator;
	while (v.y < 0.0) v.y += denominator;
	while (v.z > denominator) v.z -= denominator;
	while (v.z < 0.0) v.z += denominator;
	return v;
}
MALIB_API VEC2 Clamp(VEC2& v, float min, float max)
{
	if (v.x < min) v.x = min;
	else if (v.x > max) v.x = max;
	if (v.y < min) v.y = min;
	else if (v.y > max) v.y = max;
	return v;
}
MALIB_API VEC2 Module(VEC2& v, float denominator)
{
	while (v.x > denominator) v.x -= denominator;
	while (v.x < 0.0) v.x += denominator;
	while (v.y > denominator) v.y -= denominator;
	while (v.y < 0.0) v.y += denominator;
	return v;
}

MALIB_API VEC4::VEC4()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
	this->w = 1.0f;
}
MALIB_API VEC4::VEC4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}
MALIB_API VEC4::VEC4(const VEC3& v, float w)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = w;
}
MALIB_API VEC4::VEC4(float x, const VEC3& v)
{
	this->x = x;
	this->y = v.x;
	this->z = v.y;
	this->w = v.z;
}
MALIB_API VEC4::VEC4(const VEC2& v, float z, float w)
{
	this->x = v.x;
	this->y = v.y;
	this->z = z;
	this->w = w;
}
MALIB_API VEC4::VEC4(float x, const VEC2& v, float w)
{
	this->x = x;
	this->y = v.x;
	this->z = v.y;
	this->w = w;
}
MALIB_API VEC4::VEC4(float x, float y, const VEC2& v)
{
	this->x = x;
	this->y = y;
	this->z = v.x;
	this->w = v.y;
}
MALIB_API VEC4::VEC4(const VEC2& v1, const VEC2& v2)
{
	this->x = v1.x;
	this->y = v1.y;
	this->z = v2.x;
	this->w = v2.y;
}
MALIB_API VEC4::VEC4(float v)
{
	this->x = v;
	this->y = v;
	this->z = v;
	this->w = v;
}
MALIB_API VEC4::VEC4(const VEC4& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = v.w;
}
MALIB_API VEC4::~VEC4()
{
}

MALIB_API VEC4 VEC4::operator+(const VEC4& v)
{
	return VEC4(this->x + v.x, this->y + v.y, this->z + v.z, this->w + v.w);
}
MALIB_API VEC4 VEC4::operator-(const VEC4& v)
{
	return VEC4(this->x - v.x, this->y - v.y, this->z - v.z, this->w - v.w);
}
MALIB_API VEC4 VEC4::operator*(const VEC4& v)
{
	return VEC4(this->x * v.x, this->y * v.y, this->z * v.z, this->w * v.w);
}
MALIB_API VEC4 VEC4::operator/(const VEC4& v)
{
	return VEC4(this->x / v.x, this->y / v.y, this->z / v.z, this->w / v.w);
}
MALIB_API VEC4 VEC4::operator+(const VEC3& v)
{
	return VEC4(this->x + v.x, this->y + v.y, this->z + v.z, this->w);
}
MALIB_API VEC4 VEC4::operator-(const VEC3& v)
{
	return VEC4(this->x - v.x, this->y - v.y, this->z - v.z, this->w);
}
MALIB_API VEC4 VEC4::operator*(const VEC3& v)
{
	return VEC4(this->x * v.x, this->y * v.y, this->z * v.z, this->w);
}
MALIB_API VEC4 VEC4::operator/(const VEC3& v)
{
	return VEC4(this->x / v.x, this->y / v.y, this->z / v.z, this->w);
}
MALIB_API VEC4 VEC4::operator+(const VEC2& v)
{
	return VEC4(this->x + v.x, this->y + v.y, this->z, this->w);
}
MALIB_API VEC4 VEC4::operator-(const VEC2& v)
{
	return VEC4(this->x - v.x, this->y - v.y, this->z, this->w);
}
MALIB_API VEC4 VEC4::operator*(const VEC2& v)
{
	return VEC4(this->x * v.x, this->y * v.y, this->z, this->w);
}
MALIB_API VEC4 VEC4::operator/(const VEC2& v)
{
	return VEC4(this->x / v.x, this->y / v.y, this->z, this->w);
}
MALIB_API VEC4 VEC4::operator+(float scalar)
{
	return VEC4(this->x + scalar, this->y + scalar, this->z + scalar, this->w + scalar);
}
MALIB_API VEC4 VEC4::operator-(float scalar)
{
	return VEC4(this->x - scalar, this->y - scalar, this->z - scalar, this->w - scalar);
}
MALIB_API VEC4 VEC4::operator*(float scalar)
{
	return VEC4(this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar);
}
MALIB_API VEC4 VEC4::operator/(float scalar)
{
	return VEC4(this->x / scalar, this->y / scalar, this->z / scalar, this->w / scalar);
}
MALIB_API void VEC4::operator+=(const VEC4& v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	this->w += v.w;
}
MALIB_API void VEC4::operator-=(const VEC4& v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	this->w -= v.w;
}
MALIB_API void VEC4::operator*=(const VEC4& v)
{
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;
	this->w *= v.w;
}
MALIB_API void VEC4::operator/=(const VEC4& v)
{
	this->x /= v.x;
	this->y /= v.y;
	this->z /= v.z;
	this->w /= v.w;
}
MALIB_API void VEC4::operator+=(const VEC3& v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
}
MALIB_API void VEC4::operator-=(const VEC3& v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
}
MALIB_API void VEC4::operator*=(const VEC3& v)
{
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;
}
MALIB_API void VEC4::operator/=(const VEC3& v)
{
	this->x /= v.x;
	this->y /= v.y;
	this->z /= v.z;
}
MALIB_API void VEC4::operator+=(const VEC2& v)
{
	this->x += v.x;
	this->y += v.y;
}
MALIB_API void VEC4::operator-=(const VEC2& v)
{
	this->x -= v.x;
	this->y -= v.y;
}
MALIB_API void VEC4::operator*=(const VEC2& v)
{
	this->x *= v.x;
	this->y *= v.y;
}
MALIB_API void VEC4::operator/=(const VEC2& v)
{
	this->x /= v.x;
	this->y /= v.y;
}
MALIB_API void VEC4::operator+=(float scalar)
{
	this->x += scalar;
	this->y += scalar;
	this->z += scalar;
	this->w += scalar;
}
MALIB_API void VEC4::operator-=(float scalar)
{
	this->x -= scalar;
	this->y -= scalar;
	this->z -= scalar;
	this->w -= scalar;
}
MALIB_API void VEC4::operator*=(float scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	this->z *= scalar;
	this->w *= scalar;
}
MALIB_API void VEC4::operator/=(float scalar)
{
	this->x /= scalar;
	this->y /= scalar;
	this->z /= scalar;
	this->w /= scalar;
}
MALIB_API void VEC4::operator=(const VEC4& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = v.w;
}
MALIB_API void VEC4::operator=(const VEC3& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}
MALIB_API void VEC4::operator=(const VEC2& v)
{
	this->x = v.x;
	this->y = v.y;
}

MALIB_API VEC3::VEC3()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}
MALIB_API VEC3::VEC3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
MALIB_API VEC3::VEC3(const VEC2& v, float z)
{
	this->x = v.x;
	this->y = v.y;
	this->z = z;
}
MALIB_API VEC3::VEC3(float x, const VEC2& v)
{
	this->x = x;
	this->y = v.x;
	this->z = v.y;
}
MALIB_API VEC3::VEC3(const VEC4& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}
MALIB_API VEC3::VEC3(float v)
{
	this->x = v;
	this->y = v;
	this->z = v;
}
MALIB_API VEC3::VEC3(const VEC3& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}
MALIB_API VEC3::~VEC3()
{
}

MALIB_API VEC3 VEC3::operator+(const VEC4& v)
{
	return VEC3(this->x + v.x, this->y + v.y, this->z + v.z);
}
MALIB_API VEC3 VEC3::operator-(const VEC4& v)
{
	return VEC3(this->x - v.x, this->y - v.y, this->z - v.z);
}
MALIB_API VEC3 VEC3::operator*(const VEC4& v)
{
	return VEC3(this->x * v.x, this->y * v.y, this->z * v.z);
}
MALIB_API VEC3 VEC3::operator/(const VEC4& v)
{
	return VEC3(this->x / v.x, this->y / v.y, this->z / v.z);
}
MALIB_API VEC3 VEC3::operator+(const VEC3& v)
{
	return VEC3(this->x + v.x, this->y + v.y, this->z + v.z);
}
MALIB_API VEC3 VEC3::operator-(const VEC3& v)
{
	return VEC3(this->x - v.x, this->y - v.y, this->z - v.z);
}
MALIB_API VEC3 VEC3::operator*(const VEC3& v)
{
	return VEC3(this->x * v.x, this->y * v.y, this->z * v.z);
}
MALIB_API VEC3 VEC3::operator/(const VEC3& v)
{
	return VEC3(this->x / v.x, this->y / v.y, this->z / v.z);
}
MALIB_API VEC3 VEC3::operator+(const VEC2& v)
{
	return VEC3(this->x + v.x, this->y + v.y, this->z);
}
MALIB_API VEC3 VEC3::operator-(const VEC2& v)
{
	return VEC3(this->x - v.x, this->y - v.y, this->z);
}
MALIB_API VEC3 VEC3::operator*(const VEC2& v)
{
	return VEC3(this->x * v.x, this->y * v.y, this->z);
}
MALIB_API VEC3 VEC3::operator/(const VEC2& v)
{
	return VEC3(this->x / v.x, this->y / v.y, this->z);
}
MALIB_API VEC3 VEC3::operator+(float scalar)
{
	return VEC3(this->x + scalar, this->y + scalar, this->z + scalar);
}
MALIB_API VEC3 VEC3::operator-(float scalar)
{
	return VEC3(this->x - scalar, this->y - scalar, this->z - scalar);
}
MALIB_API VEC3 VEC3::operator*(float scalar)
{
	return VEC3(this->x * scalar, this->y * scalar, this->z * scalar);
}
MALIB_API VEC3 VEC3::operator/(float scalar)
{
	return VEC3(this->x / scalar, this->y / scalar, this->z / scalar);
}
MALIB_API void VEC3::operator+=(const VEC4& v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
}
MALIB_API void VEC3::operator-=(const VEC4& v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
}
MALIB_API void VEC3::operator*=(const VEC4& v)
{
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;
}
MALIB_API void VEC3::operator/=(const VEC4& v)
{
	this->x /= v.x;
	this->y /= v.y;
	this->z /= v.z;
}
MALIB_API void VEC3::operator+=(const VEC3& v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
}
MALIB_API void VEC3::operator-=(const VEC3& v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
}
MALIB_API void VEC3::operator*=(const VEC3& v)
{
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;
}
MALIB_API void VEC3::operator/=(const VEC3& v)
{
	this->x /= v.x;
	this->y /= v.y;
	this->z /= v.z;
}
MALIB_API void VEC3::operator+=(const VEC2& v)
{
	this->x += v.x;
	this->y += v.y;
}
MALIB_API void VEC3::operator-=(const VEC2& v)
{
	this->x -= v.x;
	this->y -= v.y;
}
MALIB_API void VEC3::operator*=(const VEC2& v)
{
	this->x *= v.x;
	this->y *= v.y;
}
MALIB_API void VEC3::operator/=(const VEC2& v)
{
	this->x /= v.x;
	this->y /= v.y;
}
MALIB_API void VEC3::operator+=(float scalar)
{
	this->x += scalar;
	this->y += scalar;
	this->z += scalar;
}
MALIB_API void VEC3::operator-=(float scalar)
{
	this->x -= scalar;
	this->y -= scalar;
	this->z -= scalar;
}
MALIB_API void VEC3::operator*=(float scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	this->z *= scalar;
}
MALIB_API void VEC3::operator/=(float scalar)
{
	this->x /= scalar;
	this->y /= scalar;
	this->z /= scalar;
}
MALIB_API void VEC3::operator=(const VEC4& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}
MALIB_API void VEC3::operator=(const VEC3& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}
MALIB_API void VEC3::operator=(const VEC2& v)
{
	this->x = v.x;
	this->y = v.y;
}

MALIB_API VEC2::VEC2()
{
	this->x = 0.0f;
	this->y = 0.0f;
}
MALIB_API VEC2::VEC2(float x, float y)
{
	this->x = x;
	this->y = y;
}
MALIB_API VEC2::VEC2(const VEC3& v)
{
	this->x = v.x;
	this->y = v.y;
}
MALIB_API VEC2::VEC2(const VEC4& v)
{
	this->x = v.x;
	this->y = v.y;
}
MALIB_API VEC2::VEC2(float v)
{
	this->x = v;
	this->y = v;
}
MALIB_API VEC2::VEC2(const VEC2& v)
{
	this->x = v.x;
	this->y = v.y;
}
MALIB_API VEC2::~VEC2()
{
}

MALIB_API VEC2 VEC2::operator+(const VEC4& v)
{
	return VEC2(this->x + v.x, this->y + v.y);
}
MALIB_API VEC2 VEC2::operator-(const VEC4& v)
{
	return VEC2(this->x - v.x, this->y - v.y);
}
MALIB_API VEC2 VEC2::operator*(const VEC4& v)
{
	return VEC2(this->x * v.x, this->y * v.y);
}
MALIB_API VEC2 VEC2::operator/(const VEC4& v)
{
	return VEC2(this->x / v.x, this->y / v.y);
}
MALIB_API VEC2 VEC2::operator+(const VEC3& v)
{
	return VEC2(this->x + v.x, this->y + v.y);
}
MALIB_API VEC2 VEC2::operator-(const VEC3& v)
{
	return VEC2(this->x - v.x, this->y - v.y);
}
MALIB_API VEC2 VEC2::operator*(const VEC3& v)
{
	return VEC2(this->x * v.x, this->y * v.y);
}
MALIB_API VEC2 VEC2::operator/(const VEC3& v)
{
	return VEC2(this->x / v.x, this->y / v.y);
}
MALIB_API VEC2 VEC2::operator+(const VEC2& v)
{
	return VEC2(this->x + v.x, this->y + v.y);
}
MALIB_API VEC2 VEC2::operator-(const VEC2& v)
{
	return VEC2(this->x - v.x, this->y - v.y);
}
MALIB_API VEC2 VEC2::operator*(const VEC2& v)
{
	return VEC2(this->x * v.x, this->y * v.y);
}
MALIB_API VEC2 VEC2::operator/(const VEC2& v)
{
	return VEC2(this->x / v.x, this->y / v.y);
}
MALIB_API VEC2 VEC2::operator+(float scalar)
{
	return VEC2(this->x + scalar, this->y + scalar);
}
MALIB_API VEC2 VEC2::operator-(float scalar)
{
	return VEC2(this->x - scalar, this->y - scalar);
}
MALIB_API VEC2 VEC2::operator*(float scalar)
{
	return VEC2(this->x * scalar, this->y * scalar);
}
MALIB_API VEC2 VEC2::operator/(float scalar)
{
	return VEC2(this->x / scalar, this->y / scalar);
}
MALIB_API void VEC2::operator+=(const VEC4& v)
{
	this->x += v.x;
	this->y += v.y;
}
MALIB_API void VEC2::operator-=(const VEC4& v)
{
	this->x -= v.x;
	this->y -= v.y;
}
MALIB_API void VEC2::operator*=(const VEC4& v)
{
	this->x *= v.x;
	this->y *= v.y;
}
MALIB_API void VEC2::operator/=(const VEC4& v)
{
	this->x /= v.x;
	this->y /= v.y;
}
MALIB_API void VEC2::operator+=(const VEC3& v)
{
	this->x += v.x;
	this->y += v.y;
}
MALIB_API void VEC2::operator-=(const VEC3& v)
{
	this->x -= v.x;
	this->y -= v.y;
}
MALIB_API void VEC2::operator*=(const VEC3& v)
{
	this->x *= v.x;
	this->y *= v.y;
}
MALIB_API void VEC2::operator/=(const VEC3& v)
{
	this->x /= v.x;
	this->y /= v.y;
}
MALIB_API void VEC2::operator+=(const VEC2& v)
{
	this->x += v.x;
	this->y += v.y;
}
MALIB_API void VEC2::operator-=(const VEC2& v)
{
	this->x -= v.x;
	this->y -= v.y;
}
MALIB_API void VEC2::operator*=(const VEC2& v)
{
	this->x *= v.x;
	this->y *= v.y;
}
MALIB_API void VEC2::operator/=(const VEC2& v)
{
	this->x /= v.x;
	this->y /= v.y;
}
MALIB_API void VEC2::operator+=(float scalar)
{
	this->x += scalar;
	this->y += scalar;
}
MALIB_API void VEC2::operator-=(float scalar)
{
	this->x -= scalar;
	this->y -= scalar;
}
MALIB_API void VEC2::operator*=(float scalar)
{
	this->x *= scalar;
	this->y *= scalar;
}
MALIB_API void VEC2::operator/=(float scalar)
{
	this->x /= scalar;
	this->y /= scalar;
}
MALIB_API void VEC2::operator=(const VEC4& v)
{
	this->x = v.x;
	this->y = v.y;
}
MALIB_API void VEC2::operator=(const VEC3& v)
{
	this->x = v.x;
	this->y = v.y;
}
MALIB_API void VEC2::operator=(const VEC2& v)
{
	this->x = v.x;
	this->y = v.y;
}

_MALIB_END
#endif