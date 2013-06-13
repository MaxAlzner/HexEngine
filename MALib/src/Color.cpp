#include "..\main.h"


COLOR::COLOR()
{
	this->a = 1.0;
	this->r = 1.0;
	this->g = 1.0;
	this->b = 1.0;
}
COLOR::COLOR(float a, float r, float g, float b)
{
	if (a < 0.0) a = 0.0;
	else if (a > 1.0) a = 1.0;
	if (r < 0.0) r = 0.0;
	else if (r > 1.0) r = 1.0;
	if (g < 0.0) g = 0.0;
	else if (g > 1.0) g = 1.0;
	if (b < 0.0) b = 0.0;
	else if (b > 1.0) b = 1.0;
	this->a = a;
	this->r = r;
	this->g = g;
	this->b = b;
}
COLOR::COLOR(float r, float g, float b)
{
	if (r < 0.0) r = 0.0;
	else if (r > 1.0) r = 1.0;
	if (g < 0.0) g = 0.0;
	else if (g > 1.0) g = 1.0;
	if (b < 0.0) b = 0.0;
	else if (b > 1.0) b = 1.0;
	this->a = 1.0;
	this->r = r;
	this->g = g;
	this->b = b;
}
COLOR::COLOR(unsigned int argb)
{
	this->a = float(ARGB::GetAlpha(argb)) / float(0xFF), 
	this->r = float(ARGB::GetRed(argb)) / float(0xFF), 
	this->g = float(ARGB::GetGreen(argb)) / float(0xFF), 
	this->b = float(ARGB::GetBlue(argb)) / float(0xFF);
}
COLOR::~COLOR()
{
}

COLOR COLOR::operator+(const COLOR &c)
{
	return COLOR(this->a + c.a, this->r + c.r, this->g + c.g, this->b + c.b);
}
COLOR COLOR::operator-(const COLOR &c)
{
	return COLOR(this->a - c.a, this->r - c.r, this->g - c.g, this->b - c.b);
}
COLOR COLOR::operator*(const COLOR &c)
{
	return COLOR(this->a * c.a, this->r * c.r, this->g * c.g, this->b * c.b);
}
COLOR COLOR::operator/(const COLOR &c)
{
	return COLOR(this->a / c.a, this->r / c.r, this->g / c.g, this->b / c.b);
}
COLOR COLOR::operator+(float scalar)
{
	return COLOR(this->a + scalar, this->r + scalar, this->g + scalar, this->b + scalar);
}
COLOR COLOR::operator-(float scalar)
{
	return COLOR(this->a - scalar, this->r - scalar, this->g - scalar, this->b - scalar);
}
COLOR COLOR::operator*(float scalar)
{
	return COLOR(this->a * scalar, this->r * scalar, this->g * scalar, this->b * scalar);
}
COLOR COLOR::operator/(float scalar)
{
	return COLOR(this->a / scalar, this->r / scalar, this->g / scalar, this->b / scalar);
}
void COLOR::operator+=(const COLOR &c)
{
	this->a += c.a;
	this->r += c.r;
	this->g += c.g;
	this->b += c.b;
}
void COLOR::operator-=(const COLOR &c)
{
	this->a -= c.a;
	this->r -= c.r;
	this->g -= c.g;
	this->b -= c.b;
}
void COLOR::operator*=(const COLOR &c)
{
	this->a *= c.a;
	this->r *= c.r;
	this->g *= c.g;
	this->b *= c.b;
}
void COLOR::operator/=(const COLOR &c)
{
	this->a /= c.a;
	this->r /= c.r;
	this->g /= c.g;
	this->b /= c.b;
}
void COLOR::operator+=(float scalar)
{
	this->a += scalar;
	this->r += scalar;
	this->g += scalar;
	this->b += scalar;
}
void COLOR::operator-=(float scalar)
{
	this->a -= scalar;
	this->r -= scalar;
	this->g -= scalar;
	this->b -= scalar;
}
void COLOR::operator*=(float scalar)
{
	this->a *= scalar;
	this->r *= scalar;
	this->g *= scalar;
	this->b *= scalar;
}
void COLOR::operator/=(float scalar)
{
	this->a /= scalar;
	this->r /= scalar;
	this->g /= scalar;
	this->b /= scalar;
}

COLOR COLOR::CreateColor(float a, float r, float g, float b)
{
	return COLOR(a, r, g, b);
}
COLOR COLOR::CreateColor(unsigned int argb)
{
	return COLOR(argb);
}
COLOR COLOR::Gray(const COLOR &c)
{
	float v = (c.r + c.g + c.b) / 3.0f;
	return COLOR(c.a, v, v, v);
}
unsigned int COLOR::ToARGB(const COLOR &c)
{
	return ARGB::CreateARGB(
		int(c.a * float(0xFF)), 
		int(c.r * float(0xFF)), 
		int(c.g * float(0xFF)), 
		int(c.b * float(0xFF)));
}
unsigned int COLOR::ToRGBA(const COLOR &c)
{
	return RGBA::CreateRGBA(
		int(c.a * float(0xFF)), 
		int(c.r * float(0xFF)), 
		int(c.g * float(0xFF)), 
		int(c.b * float(0xFF)));
}