#ifndef _MA_DRAWING_H_
#define _MA_DRAWING_H_
_MALIB_BEGIN

#ifndef _INC_MATH
#include <math.h>
#endif

#define MA_RGBA_WHITE          0xFFFFFFFF
#define MA_RGBA_GRAY_LIGHT     0xCCCCCCFF
#define MA_RGBA_GRAY_MEDIUM    0x888888FF
#define MA_RGBA_GRAY_DARK      0x444444FF
#define MA_RGBA_BLACK          0x000000FF

#define MA_RGBA_PINK           0xFF0088FF
#define MA_RGBA_RED            0xFF0000FF
#define MA_RGBA_ORANGE         0xFF8800FF
#define MA_RGBA_YELLOW         0xFFFF00FF
#define MA_RGBA_YELLOWGREEN    0x88FF00FF
#define MA_RGBA_GREEN          0x00FF00FF
#define MA_RGBA_TURQUIOSE      0x00FF88FF
#define MA_RGBA_CYAN           0x00FFFFFF
#define MA_RGBA_BLUEGREEN      0x0088FFFF
#define MA_RGBA_BLUE           0x0000FFFF
#define MA_RGBA_VIOLET         0x8800FFFF
#define MA_RGBA_MAGENTA        0xFF00FFFF

typedef struct SURFACE SURFACE;
typedef struct COLOR COLOR;

enum PIXELFORMAT
{
	PIXELFORMAT_NONE         = 0x00000000, 
	PIXELFORMAT_RGB          = 0x00000001, 
	PIXELFORMAT_RGBA         = 0x00000002, 
	PIXELFORMAT_ARGB         = 0x00000003, 
	PIXELFORMAT_BGR          = 0x00000004, 
	PIXELFORMAT_BGRA         = 0x00000005, 
	PIXELFORMAT_ABGR         = 0x00000006, 
};
enum DRAWMODE
{
	DRAWMODE_NORMAL          = 0x00000000, 
	DRAWMODE_FLIPPEDX        = 0x00000001, 
	DRAWMODE_FLIPPEDY        = 0x00000002, 
};

MALIB_API uint ByteCount(PIXELFORMAT format);
MALIB_API uint PackColor(uchar r, uchar g, uchar b, uchar a, PIXELFORMAT format);
MALIB_API uint PackColor(COLOR& color, PIXELFORMAT format);
MALIB_API void UnpackColor(uint c, uchar* r, uchar* g, uchar* b, uchar* a, PIXELFORMAT format);
MALIB_API void BlendColor(uchar& dest_r, uchar& dest_g, uchar& dest_b, uchar& dest_a, uchar src_r, uchar src_g, uchar src_b, uchar src_a, PIXELFORMAT format = PIXELFORMAT_NONE);

MALIB_API void PutPixel(SURFACE* surface, uint x, uint y, uchar r, uchar g, uchar b, uchar a);
MALIB_API void PutPixel(SURFACE* surface, uint x, uint y, uint color);
MALIB_API void PutPixel(SURFACE* surface, uint x, uint y, COLOR& color);
MALIB_API void GetPixel(SURFACE* surface, uint x, uint y, uchar* r, uchar* g, uchar* b, uchar* a);
MALIB_API void GetPixel(SURFACE* surface, uint x, uint y, COLOR* color);

MALIB_API void DrawBitmap(SURFACE* dest, SURFACE* src, uint x, uint y, DRAWMODE option = DRAWMODE_NORMAL);
MALIB_API void DrawBitmapCell(SURFACE* dest, SURFACE* src, uint x, uint y, uint cellColumn, uint cellRow, uint cellWidth, uint cellHeight, DRAWMODE option = DRAWMODE_NORMAL);
MALIB_API void ClearBitmap(SURFACE* surface, uint color);

MALIB_API void DrawCircle(SURFACE* surface, uint cx, uint cy, uint r, uint color);
MALIB_API void DrawBox(SURFACE* surface, uint x1, uint y1, uint x2, uint y2, uint color);
MALIB_API void DrawRectangle(SURFACE* surface, uint x, uint y, uint width, uint height, uint color);
MALIB_API void DrawLine(SURFACE* surface, uint x1, uint y1, uint x2, uint y2, uint color);
MALIB_API void DrawTriangle(SURFACE* surface, uint x1, uint y1, uint x2, uint y2, uint x3, uint y3, uint color);


_MALIB_END
#endif