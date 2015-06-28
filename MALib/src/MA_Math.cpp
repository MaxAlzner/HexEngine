#include "..\include\MALib.h"

#ifdef _MA_MATH_H_
_MALIB_BEGIN
	
const float PI = 3.14159265358979323846f;

MALIB_API int Clamp(int x, int min, int max)
{
	if (x < min) return min;
	if (x > max) return max;
	return x;
}
MALIB_API uint Clamp(uint x, uint min, uint max)
{
	if (x < min) return min;
	if (x > max) return max;
	return x;
}
MALIB_API float Clamp(float x, float min, float max)
{
	if (x < min) return min;
	if (x > max) return max;
	return x;
}
MALIB_API double Clamp(double x, double min, double max)
{
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

MALIB_API float Module(float x, float denominator)
{
	while (x > denominator) x -= denominator;
	while (x < 0.0) x += denominator;
	return x;
}
MALIB_API double Module(double x, double denominator)
{
	while (x > denominator) x -= denominator;
	while (x < 0.0) x += denominator;
	return x;
}

MALIB_API void Swap(int& x, int& y)
{
	int temp = x;
	x = y;
	y = temp;
}
MALIB_API void Swap(uint& x, uint& y)
{
	uint temp = x;
	x = y;
	y = temp;
}
MALIB_API void Swap(float& x, float& y)
{
	float temp = x;
	x = y;
	y = temp;
}
MALIB_API void Swap(double& x, double& y)
{
	double temp = x;
	x = y;
	y = temp;
}

MALIB_API int Interp(float percent, int min, int max)
{
	if (min > max) Swap(min, max);
	return min + int(percent * float(max - min));
}
MALIB_API uint Interp(float percent, uint min, uint max)
{
	if (min > max) Swap(min, max);
	return min + uint(percent * float(max - min));
}
MALIB_API float Interp(float percent, float min, float max)
{
	if (min > max) Swap(min, max);
	return min + (percent * (max - min));
}
MALIB_API double Interp(float percent, double min, double max)
{
	if (min > max) Swap(min, max);
	return min + double(percent * float(max - min));
}

MALIB_API void Clip(int& x, int& y, int x0, int y0, int x1, int y1)
{
	if (x < x0) x = x0;
	else if (x > x1) x = x1;
	if (y < y0) y = y0;
	else if (y > y1) y = y1;
}
MALIB_API void Clip(uint& x, uint& y, uint x0, uint y0, uint x1, uint y1)
{
	if (x < x0) x = x0;
	else if (x > x1) x = x1;
	if (y < y0) y = y0;
	else if (y > y1) y = y1;
}
MALIB_API void Clip(float& x, float& y, float x0, float y0, float x1, float y1)
{
	if (x < x0) x = x0;
	else if (x > x1) x = x1;
	if (y < y0) y = y0;
	else if (y > y1) y = y1;
}
MALIB_API void Clip(double& x, double& y, double x0, double y0, double x1, double y1)
{
	if (x < x0) x = x0;
	else if (x > x1) x = x1;
	if (y < y0) y = y0;
	else if (y > y1) y = y1;
}

MALIB_API int Sign(int x)
{
	if (x > 0) return 1;
	return -1;
}
MALIB_API int Sign(float x)
{
	if (x > 0) return 1;
	return -1;
}
MALIB_API int Sign(double x)
{
	if (x > 0) return 1;
	return -1;
}

MALIB_API int Pow(int b, uint exp)
{
	if (exp == 0) return 1;
	int final = b;
	for (uint i = 1; i < exp; i++) final *= b;
	return final;
}
MALIB_API uint Pow(uint b, uint exp)
{
	if (exp == 0) return 1;
	uint final = b;
	for (uint i = 1; i < exp; i++) final *= b;
	return final;
}

MALIB_API float ToRadians(float angle)
{
	return angle * (PI / 180.0f);
}
MALIB_API float ToDegrees(float angle)
{
	return angle * (180.0f / PI);
}

MALIB_API int Max(int x, int y)
{
	if (y < x) return x;
	return y;
}
MALIB_API uint Max(uint x, uint y)
{
	if (y < x) return x;
	return y;
}
MALIB_API float Max(float x, float y)
{
	if (y < x) return x;
	return y;
}
MALIB_API double Max(double x, double y)
{
	if (y < x) return x;
	return y;
}
MALIB_API int Max(int x, int y, int z)
{
	int max = x;
	if (y > max) max = y;
	if (z > max) max = z;
	return max;
}
MALIB_API uint Max(uint x, uint y, uint z)
{
	uint max = x;
	if (y > max) max = y;
	if (z > max) max = z;
	return max;
}
MALIB_API float Max(float x, float y, float z)
{
	float max = x;
	if (y > max) max = y;
	if (z > max) max = z;
	return max;
}
MALIB_API double Max(double x, double y, double z)
{
	double max = x;
	if (y > max) max = y;
	if (z > max) max = z;
	return max;
}

MALIB_API int Min(int x, int y)
{
	if (y > x) return x;
	return y;
}
MALIB_API int Min(int x, int y, int z)
{
	int min = x;
	if (y < min) min = y;
	if (z < min) min = z;
	return min;
}
MALIB_API uint Min(uint x, uint y)
{
	if (y > x) return x;
	return y;
}
MALIB_API uint Min(uint x, uint y, uint z)
{
	uint min = x;
	if (y < min) min = y;
	if (z < min) min = z;
	return min;
}
MALIB_API float Min(float x, float y)
{
	if (y > x) return x;
	return y;
}
MALIB_API float Min(float x, float y, float z)
{
	float min = x;
	if (y < min) min = y;
	if (z < min) min = z;
	return min;
}
MALIB_API double Min(double x, double y)
{
	if (y > x) return x;
	return y;
}
MALIB_API double Min(double x, double y, double z)
{
	double min = x;
	if (y < min) min = y;
	if (z < min) min = z;
	return min;
}

_MALIB_END
#endif