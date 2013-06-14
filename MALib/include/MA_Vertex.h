#ifndef _MA_VERTEX_H_
#define _MA_VERTEX_H_

class MALIB_API VEC4;
class MALIB_API VEC3;
class MALIB_API VEC2;
typedef VEC4 VERTEX;
typedef VEC3 VECTOR;
typedef VEC2 UVPOINT;

class MALIB_API VEC4
{
public:
	VEC4();
	VEC4(float x, float y, float z, float w = 1.0);
	VEC4(const VEC3& v, float w = 1.0);
	VEC4(const VEC2& v, float z, float w = 1.0);
	VEC4(float x, const VEC2& v, float w = 1.0);
	VEC4(const VEC2& v1, const VEC2& v2);
	VEC4(const VEC4& v);
	~VEC4();

	VEC4 operator+(const VEC4& v);
	VEC4 operator-(const VEC4& v);
	VEC4 operator*(const VEC4& v);
	VEC4 operator/(const VEC4& v);
	VEC4 operator+(const VEC3& v);
	VEC4 operator-(const VEC3& v);
	VEC4 operator*(const VEC3& v);
	VEC4 operator/(const VEC3& v);
	VEC4 operator+(const VEC2& v);
	VEC4 operator-(const VEC2& v);
	VEC4 operator*(const VEC2& v);
	VEC4 operator/(const VEC2& v);
	VEC4 operator+(float scalar);
	VEC4 operator-(float scalar);
	VEC4 operator*(float scalar);
	VEC4 operator/(float scalar);
	void operator+=(const VEC4& v);
	void operator-=(const VEC4& v);
	void operator*=(const VEC4& v);
	void operator/=(const VEC4& v);
	void operator+=(const VEC3& v);
	void operator-=(const VEC3& v);
	void operator*=(const VEC3& v);
	void operator/=(const VEC3& v);
	void operator+=(const VEC2& v);
	void operator-=(const VEC2& v);
	void operator*=(const VEC2& v);
	void operator/=(const VEC2& v);
	void operator+=(float scalar);
	void operator-=(float scalar);
	void operator*=(float scalar);
	void operator/=(float scalar);

	float x, y, z, w;
};
class VEC3
{
public:
	VEC3();
	VEC3(float x, float y, float z);
	VEC3(const VEC2& v, float z);
	VEC3(float x, const VEC2& v);
	VEC3(const VEC4& v);
	~VEC3();

	VEC3 operator+(const VEC4& v);
	VEC3 operator-(const VEC4& v);
	VEC3 operator*(const VEC4& v);
	VEC3 operator/(const VEC4& v);
	VEC3 operator+(const VEC3& v);
	VEC3 operator-(const VEC3& v);
	VEC3 operator*(const VEC3& v);
	VEC3 operator/(const VEC3& v);
	VEC3 operator+(const VEC2& v);
	VEC3 operator-(const VEC2& v);
	VEC3 operator*(const VEC2& v);
	VEC3 operator/(const VEC2& v);
	VEC3 operator+(float scalar);
	VEC3 operator-(float scalar);
	VEC3 operator*(float scalar);
	VEC3 operator/(float scalar);
	void operator+=(const VEC4& v);
	void operator-=(const VEC4& v);
	void operator*=(const VEC4& v);
	void operator/=(const VEC4& v);
	void operator+=(const VEC3& v);
	void operator-=(const VEC3& v);
	void operator*=(const VEC3& v);
	void operator/=(const VEC3& v);
	void operator+=(const VEC2& v);
	void operator-=(const VEC2& v);
	void operator*=(const VEC2& v);
	void operator/=(const VEC2& v);
	void operator+=(float scalar);
	void operator-=(float scalar);
	void operator*=(float scalar);
	void operator/=(float scalar);

	float x, y, z;
};
class VEC2
{
public:
	VEC2();
	VEC2(float x, float y);
	VEC2(const VEC3& v);
	VEC2(const VEC4& v);
	~VEC2();

	VEC2 operator+(const VEC4& v);
	VEC2 operator-(const VEC4& v);
	VEC2 operator*(const VEC4& v);
	VEC2 operator/(const VEC4& v);
	VEC2 operator+(const VEC3& v);
	VEC2 operator-(const VEC3& v);
	VEC2 operator*(const VEC3& v);
	VEC2 operator/(const VEC3& v);
	VEC2 operator+(const VEC2& v);
	VEC2 operator-(const VEC2& v);
	VEC2 operator*(const VEC2& v);
	VEC2 operator/(const VEC2& v);
	VEC2 operator+(float scalar);
	VEC2 operator-(float scalar);
	VEC2 operator*(float scalar);
	VEC2 operator/(float scalar);
	void operator+=(const VEC4& v);
	void operator-=(const VEC4& v);
	void operator*=(const VEC4& v);
	void operator/=(const VEC4& v);
	void operator+=(const VEC3& v);
	void operator-=(const VEC3& v);
	void operator*=(const VEC3& v);
	void operator/=(const VEC3& v);
	void operator+=(const VEC2& v);
	void operator-=(const VEC2& v);
	void operator*=(const VEC2& v);
	void operator/=(const VEC2& v);
	void operator+=(float scalar);
	void operator-=(float scalar);
	void operator*=(float scalar);
	void operator/=(float scalar);

	float x, y;
};

MALIB_API VEC3 CreateVector(const VEC4& a, const VEC4& b, bool normalize = false);
MALIB_API VEC3 CreateVector(const VEC3& a, const VEC3& b, bool normalize = false);
MALIB_API VEC3 CreateVector(const VEC4& a, const VEC3& b, bool normalize = false);
MALIB_API VEC3 CreateVector(const VEC3& a, const VEC4& b, bool normalize = false);
MALIB_API VEC3 CreateVector(const VEC4& a, const VEC4& b, float& outDist, bool normalize = false);
MALIB_API VEC3 CreateVector(const VEC3& a, const VEC3& b, float& outDist, bool normalize = false);
MALIB_API VEC3 CreateVector(const VEC4& a, const VEC3& b, float& outDist, bool normalize = false);
MALIB_API VEC3 CreateVector(const VEC3& a, const VEC4& b, float& outDist, bool normalize = false);

MALIB_API float Dot(const VEC4& a, const VEC4& b);
MALIB_API float Dot(const VEC3& a, const VEC3& b);
MALIB_API float Dot(const VEC4& a, const VEC3& b);
MALIB_API float Dot(const VEC3& a, const VEC4& b);
MALIB_API VEC3 Cross(const VEC4& a, const VEC4& b);
MALIB_API VEC3 Cross(const VEC3& a, const VEC3& b);
MALIB_API VEC3 Cross(const VEC4& a, const VEC3& b);
MALIB_API VEC3 Cross(const VEC3& a, const VEC4& b);
MALIB_API VEC3 Reflect(const VEC4& vertex, const VEC3& normal);
MALIB_API VEC3 Reflect(const VEC3& vertex, const VEC3& normal);
MALIB_API VEC3 Tangent(const VEC4& vertex, const VEC3& normal);
MALIB_API VEC3 Tangent(const VEC3& vertex, const VEC3& normal);
MALIB_API float Distance(VEC4& a, VEC4& b);
MALIB_API float Distance(VEC3& a, VEC3& b);
MALIB_API float Distance(VEC4& a, VEC3& b);
MALIB_API float Distance(VEC3& a, VEC4& b);

MALIB_API float Magnitude(VEC4& v);
MALIB_API float Magnitude(VEC3& v);
MALIB_API float Magnitude(VEC2& v);
MALIB_API float Normalize(VEC4& v);
MALIB_API float Normalize(VEC3& v);
MALIB_API float Normalize(VEC2& v);
MALIB_API float Homogenize(VEC4& v);

MALIB_API VEC4 Clamp(VEC4& v, float min = 0.0, float max = 1.0, bool affectW = false);
MALIB_API VEC3 Clamp(VEC3& v, float min = 0.0, float max = 1.0);
MALIB_API VEC2 Clamp(VEC2& v, float min = 0.0, float max = 1.0);
MALIB_API VEC4 Module(VEC4& v, float denominator = 1.0, bool affectW = false);
MALIB_API VEC3 Module(VEC3& v, float denominator = 1.0);
MALIB_API VEC2 Module(VEC2& v, float denominator = 1.0);

MALIB_API float Clamp(float x, float min = 0.0, float max = 1.0);
MALIB_API float Module(float x, float denominator = 1.0);
MALIB_API void Swap(float& x, float& y);
MALIB_API float Max(float x, float y);
MALIB_API float Min(float x, float y);

#endif