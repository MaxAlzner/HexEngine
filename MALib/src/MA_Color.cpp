#include "..\include\MALib.h"

#ifdef _MA_COLOR_H_
_MALIB_BEGIN

MALIB_API COLOR::COLOR()
{
	this->r = 1.0f;
	this->g = 1.0f;
	this->b = 1.0f;
	this->a = 1.0f;
}
MALIB_API COLOR::COLOR(float r, float g, float b, float a)
{
	this->r = Clamp(r);
	this->g = Clamp(g);
	this->b = Clamp(b);
	this->a = Clamp(a);
}
MALIB_API COLOR::COLOR(float r, float g, float b)
{
	this->r = Clamp(r);
	this->g = Clamp(g);
	this->b = Clamp(b);
	this->a = 1.0f;
}
MALIB_API COLOR::COLOR(uint c, PIXELFORMAT format)
{
	uchar red = 0;
	uchar green = 0;
	uchar blue = 0;
	uchar alpha = 0;
	UnpackColor(c, &red, &green, &blue, &alpha, format);
	this->r = float(red) / 255.0f;
	this->g = float(green) / 255.0f;
	this->b = float(blue) / 255.0f;
	this->a = float(alpha) / 255.0f;
}
MALIB_API COLOR::COLOR(const COLOR& c)
{
	this->r = c.r;
	this->g = c.g;
	this->b = c.b;
	this->a = c.a;
}
MALIB_API COLOR::~COLOR()
{
}

MALIB_API COLOR COLOR::operator+(const COLOR &c)
{
	return COLOR(this->r + c.r, this->g + c.g, this->b + c.b, this->a + c.a);
}
MALIB_API COLOR COLOR::operator-(const COLOR &c)
{
	return COLOR(this->r - c.r, this->g - c.g, this->b - c.b, this->a - c.a);
}
MALIB_API COLOR COLOR::operator*(const COLOR &c)
{
	return COLOR(this->r * c.r, this->g * c.g, this->b * c.b, this->a * c.a);
}
MALIB_API COLOR COLOR::operator/(const COLOR &c)
{
	return COLOR(this->r / c.r, this->g / c.g, this->b / c.b, this->a / c.a);
}
MALIB_API COLOR COLOR::operator+(float scalar)
{
	return COLOR(this->r + scalar, this->g + scalar, this->b + scalar, this->a + scalar);
}
MALIB_API COLOR COLOR::operator-(float scalar)
{
	return COLOR(this->r - scalar, this->g - scalar, this->b - scalar, this->a - scalar);
}
MALIB_API COLOR COLOR::operator*(float scalar)
{
	return COLOR(this->r * scalar, this->g * scalar, this->b * scalar, this->a * scalar);
}
MALIB_API COLOR COLOR::operator/(float scalar)
{
	return COLOR(this->r / scalar, this->g / scalar, this->b / scalar, this->a / scalar);
}
MALIB_API void COLOR::operator+=(const COLOR &c)
{
	this->r += c.r;
	this->g += c.g;
	this->b += c.b;
	this->a += c.a;
}
MALIB_API void COLOR::operator-=(const COLOR &c)
{
	this->r -= c.r;
	this->g -= c.g;
	this->b -= c.b;
	this->a -= c.a;
}
MALIB_API void COLOR::operator*=(const COLOR &c)
{
	this->r *= c.r;
	this->g *= c.g;
	this->b *= c.b;
	this->a *= c.a;
}
MALIB_API void COLOR::operator/=(const COLOR &c)
{
	this->r /= c.r;
	this->g /= c.g;
	this->b /= c.b;
	this->a /= c.a;
}
MALIB_API void COLOR::operator+=(float scalar)
{
	this->r += scalar;
	this->g += scalar;
	this->b += scalar;
	this->a += scalar;
}
MALIB_API void COLOR::operator-=(float scalar)
{
	this->r -= scalar;
	this->g -= scalar;
	this->b -= scalar;
	this->a -= scalar;
}
MALIB_API void COLOR::operator*=(float scalar)
{
	this->r *= scalar;
	this->g *= scalar;
	this->b *= scalar;
	this->a *= scalar;
}
MALIB_API void COLOR::operator/=(float scalar)
{
	this->r /= scalar;
	this->g /= scalar;
	this->b /= scalar;
	this->a /= scalar;
}
MALIB_API void COLOR::operator=(const COLOR &c)
{
	this->r = c.r;
	this->g = c.g;
	this->b = c.b;
	this->a = c.a;
}

_MALIB_END
#endif