#ifndef __VERTEX_H_
#define __VERTEX_H_

class VERTEX4;
class VERTEX3;
class VERTEX2;
typedef VERTEX4 VERTEX;
typedef VERTEX3 VECTOR;
typedef VERTEX2 UVPOINT;

class VERTEX4
{
public:
	VERTEX4();
	VERTEX4(float x, float y, float z, float w = 1.0);
	VERTEX4(const VERTEX3 &v, float w = 1.0);
	VERTEX4(const VERTEX2 &v, float z, float w = 1.0);
	VERTEX4(float x, const VERTEX2 &v, float w = 1.0);
	VERTEX4(const VERTEX2 &v1, const VERTEX2 &v2);
	~VERTEX4();

	VERTEX4 operator+(const VERTEX4 &v);
	VERTEX4 operator-(const VERTEX4 &v);
	VERTEX4 operator*(const VERTEX4 &v);
	VERTEX4 operator/(const VERTEX4 &v);
	VERTEX4 operator+(const VERTEX3 &v);
	VERTEX4 operator-(const VERTEX3 &v);
	VERTEX4 operator*(const VERTEX3 &v);
	VERTEX4 operator/(const VERTEX3 &v);
	VERTEX4 operator+(const VERTEX2 &v);
	VERTEX4 operator-(const VERTEX2 &v);
	VERTEX4 operator*(const VERTEX2 &v);
	VERTEX4 operator/(const VERTEX2 &v);
	VERTEX4 operator+(float scalar);
	VERTEX4 operator-(float scalar);
	VERTEX4 operator*(float scalar);
	VERTEX4 operator/(float scalar);
	void operator+=(const VERTEX4 &v);
	void operator-=(const VERTEX4 &v);
	void operator*=(const VERTEX4 &v);
	void operator/=(const VERTEX4 &v);
	void operator+=(const VERTEX3 &v);
	void operator-=(const VERTEX3 &v);
	void operator*=(const VERTEX3 &v);
	void operator/=(const VERTEX3 &v);
	void operator+=(const VERTEX2 &v);
	void operator-=(const VERTEX2 &v);
	void operator*=(const VERTEX2 &v);
	void operator/=(const VERTEX2 &v);
	void operator+=(float scalar);
	void operator-=(float scalar);
	void operator*=(float scalar);
	void operator/=(float scalar);

	float magnitude();
	void normalize();
	void homogenize();

	float x, y, z, w;
};
class VERTEX3
{
public:
	VERTEX3();
	VERTEX3(float x, float y, float z);
	VERTEX3(const VERTEX2 &v, float z);
	VERTEX3(float x, const VERTEX2 &v);
	VERTEX3(const VERTEX4 &v);
	~VERTEX3();

	VERTEX3 operator+(const VERTEX4 &v);
	VERTEX3 operator-(const VERTEX4 &v);
	VERTEX3 operator*(const VERTEX4 &v);
	VERTEX3 operator/(const VERTEX4 &v);
	VERTEX3 operator+(const VERTEX3 &v);
	VERTEX3 operator-(const VERTEX3 &v);
	VERTEX3 operator*(const VERTEX3 &v);
	VERTEX3 operator/(const VERTEX3 &v);
	VERTEX3 operator+(const VERTEX2 &v);
	VERTEX3 operator-(const VERTEX2 &v);
	VERTEX3 operator*(const VERTEX2 &v);
	VERTEX3 operator/(const VERTEX2 &v);
	VERTEX3 operator+(float scalar);
	VERTEX3 operator-(float scalar);
	VERTEX3 operator*(float scalar);
	VERTEX3 operator/(float scalar);
	void operator+=(const VERTEX4 &v);
	void operator-=(const VERTEX4 &v);
	void operator*=(const VERTEX4 &v);
	void operator/=(const VERTEX4 &v);
	void operator+=(const VERTEX3 &v);
	void operator-=(const VERTEX3 &v);
	void operator*=(const VERTEX3 &v);
	void operator/=(const VERTEX3 &v);
	void operator+=(const VERTEX2 &v);
	void operator-=(const VERTEX2 &v);
	void operator*=(const VERTEX2 &v);
	void operator/=(const VERTEX2 &v);
	void operator+=(float scalar);
	void operator-=(float scalar);
	void operator*=(float scalar);
	void operator/=(float scalar);

	float magnitude();
	void normalize();

	float x, y, z;
};
class VERTEX2
{
public:
	VERTEX2();
	VERTEX2(float x, float y);
	VERTEX2(const VERTEX3 &v);
	VERTEX2(const VERTEX4 &v);
	~VERTEX2();

	VERTEX2 operator+(const VERTEX4 &v);
	VERTEX2 operator-(const VERTEX4 &v);
	VERTEX2 operator*(const VERTEX4 &v);
	VERTEX2 operator/(const VERTEX4 &v);
	VERTEX2 operator+(const VERTEX3 &v);
	VERTEX2 operator-(const VERTEX3 &v);
	VERTEX2 operator*(const VERTEX3 &v);
	VERTEX2 operator/(const VERTEX3 &v);
	VERTEX2 operator+(const VERTEX2 &v);
	VERTEX2 operator-(const VERTEX2 &v);
	VERTEX2 operator*(const VERTEX2 &v);
	VERTEX2 operator/(const VERTEX2 &v);
	VERTEX2 operator+(float scalar);
	VERTEX2 operator-(float scalar);
	VERTEX2 operator*(float scalar);
	VERTEX2 operator/(float scalar);
	void operator+=(const VERTEX4 &v);
	void operator-=(const VERTEX4 &v);
	void operator*=(const VERTEX4 &v);
	void operator/=(const VERTEX4 &v);
	void operator+=(const VERTEX3 &v);
	void operator-=(const VERTEX3 &v);
	void operator*=(const VERTEX3 &v);
	void operator/=(const VERTEX3 &v);
	void operator+=(const VERTEX2 &v);
	void operator-=(const VERTEX2 &v);
	void operator*=(const VERTEX2 &v);
	void operator/=(const VERTEX2 &v);
	void operator+=(float scalar);
	void operator-=(float scalar);
	void operator*=(float scalar);
	void operator/=(float scalar);

	float magnitude();
	void normalize();

	float x, y;
};

VERTEX3 CreateVector(const VERTEX4 &a, const VERTEX4 &b, bool normalize = false);
VERTEX3 CreateVector(const VERTEX3 &a, const VERTEX3 &b, bool normalize = false);
VERTEX3 CreateVector(const VERTEX4 &a, const VERTEX3 &b, bool normalize = false);
VERTEX3 CreateVector(const VERTEX3 &a, const VERTEX4 &b, bool normalize = false);
VERTEX3 CreateVector(float x1, float y1, float z1, float x2, float y2, float z2, bool normalize = false);
VERTEX3 CreateVector(const VERTEX4 &a, const VERTEX4 &b, float &outDist, bool normalize = false);
VERTEX3 CreateVector(const VERTEX3 &a, const VERTEX3 &b, float &outDist, bool normalize = false);
VERTEX3 CreateVector(const VERTEX4 &a, const VERTEX3 &b, float &outDist, bool normalize = false);
VERTEX3 CreateVector(const VERTEX3 &a, const VERTEX4 &b, float &outDist, bool normalize = false);
VERTEX3 CreateVector(float x1, float y1, float z1, float x2, float y2, float z2, float &outDist, bool normalize = false);

float DotProduct(const VERTEX4 &a, const VERTEX4 &b);
float DotProduct(const VERTEX3 &a, const VERTEX3 &b);
float DotProduct(const VERTEX4 &a, const VERTEX3 &b);
float DotProduct(const VERTEX3 &a, const VERTEX4 &b);
float DotProduct(float x1, float y1, float z1, float x2, float y2, float z2);
VERTEX3 CrossProduct(const VERTEX4 &a, const VERTEX4 &b);
VERTEX3 CrossProduct(const VERTEX3 &a, const VERTEX3 &b);
VERTEX3 CrossProduct(const VERTEX4 &a, const VERTEX3 &b);
VERTEX3 CrossProduct(const VERTEX3 &a, const VERTEX4 &b);
VERTEX3 CrossProduct(float x1, float y1, float z1, float x2, float y2, float z2);
VERTEX3 Reflect(const VERTEX4 &v, const VERTEX3 &normal);
VERTEX3 Reflect(const VERTEX3 &v, const VERTEX3 &normal);
VERTEX3 Reflect(float x1, float y1, float z1, float x2, float y2, float z2);
VERTEX3 Tangent(const VERTEX4 &v, const VERTEX3 &normal);
VERTEX3 Tangent(const VERTEX3 &v, const VERTEX3 &normal);
VERTEX3 Tangent(float x1, float y1, float z1, float x2, float y2, float z2);

VERTEX3 CalculateTangent(const VERTEX3 &normal, const VERTEX4 &a, const VERTEX4 &b, const VERTEX4 &c, const VERTEX2 &uv);

VERTEX4 Clamp(VERTEX4 &v, float min = 0.0, float max = 1.0, bool affectW = false);
VERTEX4 Module(VERTEX4 &v, float denominator = 1.0, bool affectW = false);
VERTEX3 Clamp(VERTEX3 &v, float min = 0.0, float max = 1.0);
VERTEX3 Module(VERTEX3 &v, float denominator = 1.0);
VERTEX2 Clamp(VERTEX2 &v, float min = 0.0, float max = 1.0);
VERTEX2 Module(VERTEX2 &v, float denominator = 1.0);

//float Distance(VERTEX3 &v1, VERTEX3 &v2);

float Clamp(float x, float min = 0.0, float max = 1.0);
float Module(float x, float denominator = 1.0);
void Swap(float &x, float &y);
float Max(float x, float y);
float Min(float x, float y);

#endif