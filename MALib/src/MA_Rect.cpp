#include "..\include\MALib.h"

#ifdef _MA_RECT_H_
_MALIB_BEGIN
	
MALIB_API RECT::RECT()
{
	this->x0 = 0;
	this->y0 = 0;
	this->x1 = 0;
	this->y1 = 0;
	this->width = 0;
	this->height = 0;
}
MALIB_API RECT::RECT(uint x0, uint y0, uint x1, uint y1)
{
	if (x1 < x0) Swap(x0, x1);
	if (y1 < y0) Swap(y0, y1);
	this->x0 = x0;
	this->y0 = y0;
	this->x1 = x1;
	this->y1 = y1;
	this->width = x1 - x0;
	this->height = y1 - y0;
}
MALIB_API RECT::RECT(uint width, uint height)
{
	this->width = width;
	this->height = height;
	this->x0 = 0;
	this->y0 = 0;
	this->x1 = this->width;
	this->y1 = this->height;
}
MALIB_API RECT::~RECT()
{
}

_MALIB_END
#endif