#ifndef _MA_RECT_H_
#define _MA_RECT_H_
_MALIB_BEGIN

typedef struct MALIB_API POINT
{
	POINT();
	POINT(int x, int y);
	POINT(const POINT& p);
	~POINT();
	
	POINT operator+(const POINT& v);
	POINT operator-(const POINT& v);
	POINT operator*(const POINT& v);
	POINT operator/(const POINT& v);
	POINT operator+(int scalar);
	POINT operator-(int scalar);
	POINT operator*(int scalar);
	POINT operator/(int scalar);
	void operator+=(const POINT& v);
	void operator-=(const POINT& v);
	void operator*=(const POINT& v);
	void operator/=(const POINT& v);
	void operator+=(int scalar);
	void operator-=(int scalar);
	void operator*=(int scalar);
	void operator/=(int scalar);
	void operator=(const POINT& v);

	int x;
	int y;
} POINT;

MALIB_API float Distance(POINT& a, POINT& b);
MALIB_API float Magnitude(POINT& p);

typedef struct MALIB_API RECT
{
	RECT();
	RECT(int x0, int y0, int x1, int y1);
	RECT(uint width, uint height);
	RECT(const RECT& rect);
	~RECT();

	void resize(uint width, uint height);
	void move(int x, int y);

	RECT operator+(const POINT& p);
	RECT operator-(const POINT& p);
	void operator+=(const POINT& p);
	void operator-=(const POINT& p);

	int x0;
	int y0;
	int x1;
	int y1;
	int cx;
	int cy;
	uint width;
	uint height;
} RECT;

MALIB_API bool Clipping(const RECT& r1, const RECT& r2);
MALIB_API POINT Displacement(const RECT& r1, const RECT& r2);
MALIB_API POINT Overlap(const RECT& r1, const RECT& r2);
MALIB_API bool InsideRect(const RECT& rect, const POINT& p);

_MALIB_END
#endif