#include "..\include\MALib.h"

#ifdef _MA_RECT_H_
_MALIB_BEGIN

MALIB_API POINT::POINT()
{
	this->x = 0;
	this->y = 0;
}
MALIB_API POINT::POINT(int x, int y)
{
	this->x = x;
	this->y = y;
}
MALIB_API POINT::POINT(const POINT& p)
{
	this->x = p.x;
	this->y = p.y;
}
MALIB_API POINT::~POINT()
{
}

MALIB_API POINT POINT::operator+(const POINT& v)
{
	return POINT(this->x + v.x, this->y + v.y);
}
MALIB_API POINT POINT::operator-(const POINT& v)
{
	return POINT(this->x - v.x, this->y - v.y);
}
MALIB_API POINT POINT::operator*(const POINT& v)
{
	return POINT(this->x * v.x, this->y * v.y);
}
MALIB_API POINT POINT::operator/(const POINT& v)
{
	return POINT(this->x / v.x, this->y / v.y);
}
MALIB_API POINT POINT::operator+(int scalar)
{
	return POINT(this->x + scalar, this->y + scalar);
}
MALIB_API POINT POINT::operator-(int scalar)
{
	return POINT(this->x - scalar, this->y - scalar);
}
MALIB_API POINT POINT::operator*(int scalar)
{
	return POINT(this->x * scalar, this->y * scalar);
}
MALIB_API POINT POINT::operator/(int scalar)
{
	return POINT(this->x / scalar, this->y / scalar);
}
MALIB_API void POINT::operator+=(const POINT& v)
{
	this->x += v.x;
	this->y += v.y;
}
MALIB_API void POINT::operator-=(const POINT& v)
{
	this->x -= v.x;
	this->y -= v.y;
}
MALIB_API void POINT::operator*=(const POINT& v)
{
	this->x *= v.x;
	this->y *= v.y;
}
MALIB_API void POINT::operator/=(const POINT& v)
{
	this->x /= v.x;
	this->y /= v.y;
}
MALIB_API void POINT::operator+=(int scalar)
{
	this->x += scalar;
	this->y += scalar;
}
MALIB_API void POINT::operator-=(int scalar)
{
	this->x -= scalar;
	this->y -= scalar;
}
MALIB_API void POINT::operator*=(int scalar)
{
	this->x *= scalar;
	this->y *= scalar;
}
MALIB_API void POINT::operator/=(int scalar)
{
	this->x /= scalar;
	this->y /= scalar;
}
MALIB_API void POINT::operator=(const POINT& v)
{
	this->x = v.x;
	this->y = v.y;
}

MALIB_API float Distance(POINT& a, POINT& b)
{
	return sqrt(pow(float(b.x - a.x), 2) + pow(float(b.y - a.y), 2));
}
MALIB_API float Magnitude(POINT& p)
{
	return sqrt(pow(float(p.x), 2) + pow(float(p.y), 2));
}
	
MALIB_API RECT::RECT()
{
	this->x0 = 0;
	this->y0 = 0;
	this->x1 = 0;
	this->y1 = 0;
	this->cx = 0;
	this->cy = 0;
	this->width = 0;
	this->height = 0;
}
MALIB_API RECT::RECT(int x0, int y0, int x1, int y1)
{
	if (x1 < x0) Swap(x0, x1);
	if (y1 < y0) Swap(y0, y1);
	this->x0 = x0;
	this->y0 = y0;
	this->x1 = x1;
	this->y1 = y1;
	this->cx = this->x0 + (this->x1 / 2);
	this->cy = this->y0 + (this->y1 / 2);
	this->width = uint(x1 - x0);
	this->height = uint(y1 - y0);
}
MALIB_API RECT::RECT(uint width, uint height)
{
	this->width = width;
	this->height = height;
	this->x0 = 0;
	this->y0 = 0;
	this->cx = int(this->width) / 2;
	this->cy = int(this->height) / 2;
	this->x1 = int(this->width);
	this->y1 = int(this->height);
}
MALIB_API RECT::RECT(const RECT& rect)
{
	this->x0 = rect.x0;
	this->y0 = rect.y0;
	this->x1 = rect.x1;
	this->y1 = rect.y1;
	this->cx = rect.cx;
	this->cy = rect.cy;
	this->width = rect.width;
	this->height = rect.height;
}
MALIB_API RECT::~RECT()
{
}

MALIB_API void RECT::resize(uint width, uint height)
{
	this->width = width;
	this->height = height;
	uint rw = this->width % 2;
	uint rh = this->height % 2;
	uint hw = this->width / 2;
	uint hh = this->height / 2;
	this->x0 = this->cx - int(hw);
	this->y0 = this->cy - int(hh);
	this->x1 = this->cx + int(rw + hw);
	this->y1 = this->cy + int(rh + hh);
}
 MALIB_API void RECT::move(int x, int y)
 {
	this->cx = x;
	this->cy = y;
	uint rw = this->width % 2;
	uint rh = this->height % 2;
	uint hw = this->width / 2;
	uint hh = this->height / 2;
	this->x0 = this->cx - int(hw);
	this->y0 = this->cy - int(hh);
	this->x1 = this->cx + int(rw + hw);
	this->y1 = this->cy + int(rh + hh);
 }

RECT RECT::operator+(const POINT& p)
{
	return RECT(this->x0 + p.x, this->y0 + p.y, this->x1 + p.x, this->y1 + p.y);
}
RECT RECT::operator-(const POINT& p)
{
	return RECT(this->x0 - p.x, this->y0 - p.y, this->x1 - p.x, this->y1 - p.y);
}
MALIB_API void RECT::operator+=(const POINT& p)
{
	this->x0 += p.x;
	this->y0 += p.y;
	this->x1 += p.x;
	this->y1 += p.y;
	this->cx += p.x;
	this->cy += p.y;
}
MALIB_API void RECT::operator-=(const POINT& p)
{
	this->x0 -= p.x;
	this->y0 -= p.y;
	this->x1 -= p.x;
	this->y1 -= p.y;
	this->cx -= p.x;
	this->cy -= p.y;
}

MALIB_API bool Clipping(const RECT& r1, const RECT& r2)
{
	return 
		InsideRect(r1, POINT(r2.x0, r2.y0)) || 
		InsideRect(r1, POINT(r2.x1, r2.y0)) || 
		InsideRect(r1, POINT(r2.x0, r2.y1)) || 
		InsideRect(r1, POINT(r2.x1, r2.y1));
}
MALIB_API POINT Displacement(const RECT& r1, const RECT& r2)
{
	POINT p;

	if (r2.x0 > r1.cx)
	{
		p.x = r2.x0 - r1.x1;
	}
	else
	{
		p.x = r2.x1 - r1.x0;
	}
	if (r2.y0 > r1.cy)
	{
		p.y = r2.y0 - r1.y1;
	}
	else
	{
		p.y = r2.y1 - r1.y0;
	}

#if 0
	if (r2.cx >= r1.x0 && r2.cx <= r1.x1) p.x = 0;
	if (r2.cy >= r1.y0 && r2.cy <= r1.y1) p.y = 0;
#else
	if ((r2.cx >= r1.x0 && r2.cx <= r1.x1) || (r1.cx >= r2.x0 && r1.cx <= r2.x1)) p.x = 0;
	if ((r2.cy >= r1.y0 && r2.cy <= r1.y1) || (r1.cy >= r2.y0 && r1.cy <= r2.y1)) p.y = 0;
#endif

	return p;
}
MALIB_API POINT Overlap(const RECT& r1, const RECT& r2)
{
	POINT p;

	if (!Clipping(r1, r2)) return p;

	return p;
}
MALIB_API bool InsideRect(const RECT& rect, const POINT& p)
{
	return 
		p.x >= rect.x0 && 
		p.x <= rect.x1 && 
		p.y >= rect.y0 && 
		p.y <= rect.y1;
}

_MALIB_END
#endif