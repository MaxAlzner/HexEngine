#ifndef _MA_RECT_H_
#define _MA_RECT_H_
_MALIB_BEGIN

struct MALIB_API RECT
{
	RECT();
	RECT(uint x0, uint y0, uint x1, uint y1);
	RECT(uint width, uint height);
	~RECT();

	uint x0;
	uint y0;
	uint x1;
	uint y1;
	uint width;
	uint height;
};

_MALIB_END
#endif