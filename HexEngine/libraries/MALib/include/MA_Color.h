#ifndef _MA_COLOR_H_
#define _MA_COLOR_H_
_MALIB_BEGIN

#ifndef _MA_MATH_H_
#include "MA_Math.h"
#endif
#ifndef _MA_DRAWING_H_
#include "MA_Drawing.h"
#endif
	
struct MALIB_API COLOR;

struct MALIB_API COLOR
{
	COLOR();
	COLOR(float r, float g, float b, float a);
	COLOR(float r, float g, float b);
	COLOR(unsigned int c, PIXELFORMAT format);
	COLOR(const COLOR& c);
	~COLOR();

	COLOR operator+(const COLOR& c);
	COLOR operator-(const COLOR& c);
	COLOR operator*(const COLOR& c);
	COLOR operator/(const COLOR& c);
	COLOR operator+(float scalar);
	COLOR operator-(float scalar);
	COLOR operator*(float scalar);
	COLOR operator/(float scalar);
	void operator+=(const COLOR& c);
	void operator-=(const COLOR& c);
	void operator*=(const COLOR& c);
	void operator/=(const COLOR& c);
	void operator+=(float scalar);
	void operator-=(float scalar);
	void operator*=(float scalar);
	void operator/=(float scalar);
	void operator=(const COLOR& c);
	
	float r, g, b, a;
};

_MALIB_END
#endif