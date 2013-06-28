#include "..\include\MALib.h"

#ifdef _MA_COLOR_H_
_MALIB_BEGIN

MALIB_API COLOR::COLOR()
{
	this->a = 1.0f;
	this->r = 1.0f;
	this->g = 1.0f;
	this->b = 1.0f;
}
MALIB_API COLOR::COLOR(float a, float r, float g, float b)
{
	this->a = Clamp(a);
	this->r = Clamp(r);
	this->g = Clamp(g);
	this->b = Clamp(b);
}
MALIB_API COLOR::COLOR(float r, float g, float b)
{
	this->a = 1.0f;
	this->r = Clamp(r);
	this->g = Clamp(g);
	this->b = Clamp(b);
}
MALIB_API COLOR::COLOR(unsigned int c, PIXELFORMAT format)
{
	unsigned red = 0;
	unsigned green = 0;
	unsigned blue = 0;
	unsigned alpha = 0;
	UnpackColor(c, &red, &green, &blue, &alpha, format);
	this->a = float(alpha) / 255.0f, 
	this->r = float(red) / 255.0f, 
	this->g = float(green) / 255.0f, 
	this->b = float(blue) / 255.0f;
}
MALIB_API COLOR::COLOR(const COLOR& c)
{
	this->a = c.a;
	this->r = c.r;
	this->g = c.g;
	this->b = c.b;
}
MALIB_API COLOR::~COLOR()
{
}

MALIB_API COLOR COLOR::operator+(const COLOR &c)
{
	return COLOR(this->a + c.a, this->r + c.r, this->g + c.g, this->b + c.b);
}
MALIB_API COLOR COLOR::operator-(const COLOR &c)
{
	return COLOR(this->a - c.a, this->r - c.r, this->g - c.g, this->b - c.b);
}
MALIB_API COLOR COLOR::operator*(const COLOR &c)
{
	return COLOR(this->a * c.a, this->r * c.r, this->g * c.g, this->b * c.b);
}
MALIB_API COLOR COLOR::operator/(const COLOR &c)
{
	return COLOR(this->a / c.a, this->r / c.r, this->g / c.g, this->b / c.b);
}
MALIB_API COLOR COLOR::operator+(float scalar)
{
	return COLOR(this->a + scalar, this->r + scalar, this->g + scalar, this->b + scalar);
}
MALIB_API COLOR COLOR::operator-(float scalar)
{
	return COLOR(this->a - scalar, this->r - scalar, this->g - scalar, this->b - scalar);
}
MALIB_API COLOR COLOR::operator*(float scalar)
{
	return COLOR(this->a * scalar, this->r * scalar, this->g * scalar, this->b * scalar);
}
MALIB_API COLOR COLOR::operator/(float scalar)
{
	return COLOR(this->a / scalar, this->r / scalar, this->g / scalar, this->b / scalar);
}
MALIB_API void COLOR::operator+=(const COLOR &c)
{
	this->a += c.a;
	this->r += c.r;
	this->g += c.g;
	this->b += c.b;
}
MALIB_API void COLOR::operator-=(const COLOR &c)
{
	this->a -= c.a;
	this->r -= c.r;
	this->g -= c.g;
	this->b -= c.b;
}
MALIB_API void COLOR::operator*=(const COLOR &c)
{
	this->a *= c.a;
	this->r *= c.r;
	this->g *= c.g;
	this->b *= c.b;
}
MALIB_API void COLOR::operator/=(const COLOR &c)
{
	this->a /= c.a;
	this->r /= c.r;
	this->g /= c.g;
	this->b /= c.b;
}
MALIB_API void COLOR::operator+=(float scalar)
{
	this->a += scalar;
	this->r += scalar;
	this->g += scalar;
	this->b += scalar;
}
MALIB_API void COLOR::operator-=(float scalar)
{
	this->a -= scalar;
	this->r -= scalar;
	this->g -= scalar;
	this->b -= scalar;
}
MALIB_API void COLOR::operator*=(float scalar)
{
	this->a *= scalar;
	this->r *= scalar;
	this->g *= scalar;
	this->b *= scalar;
}
MALIB_API void COLOR::operator/=(float scalar)
{
	this->a /= scalar;
	this->r /= scalar;
	this->g /= scalar;
	this->b /= scalar;
}
MALIB_API void COLOR::operator=(const COLOR &c)
{
	this->a = c.a;
	this->r = c.r;
	this->g = c.g;
	this->b = c.b;
}

_MALIB_END
#endif