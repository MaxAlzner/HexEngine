#include "..\include\MALib.h"

#ifdef _MA_DRAWING_H_
_MALIB_BEGIN
	
MALIB_API uint ByteCount(PIXELFORMAT format)
{
	switch (format)
	{
	case PIXELFORMAT_RGB:
		return 3;
		break;
	case PIXELFORMAT_RGBA:
		return 4;
		break;
	case PIXELFORMAT_ARGB:
		return 4;
		break;
		
	case PIXELFORMAT_BGR:
		return 3;
		break;
	case PIXELFORMAT_BGRA:
		return 4;
		break;
	case PIXELFORMAT_ABGR:
		return 4;
		break;

	default:
		return 0;
		break;
	}
}
MALIB_API uint PackColor(uchar r, uchar g, uchar b, uchar a, PIXELFORMAT format)
{
	if (r > 0xFF) r = 0xFF;
	if (g > 0xFF) g = 0xFF;
	if (b > 0xFF) b = 0xFF;
	if (a > 0xFF) a = 0xFF;
	switch (format)
	{
	case PIXELFORMAT_RGB:
		return (r << 16) + (g << 8) + (b);
		break;
	case PIXELFORMAT_RGBA:
		return (r << 24) + (g << 16) + (b << 8) + (a);
		break;
	case PIXELFORMAT_ARGB:
		return (a << 24) + (r << 16) + (g << 8) + (b);
		break;
		
	case PIXELFORMAT_BGR:
		return (b << 16) + (g << 8) + (r);
		break;
	case PIXELFORMAT_BGRA:
		return (b << 24) + (g << 16) + (r << 8) + (a);
		break;
	case PIXELFORMAT_ABGR:
		return (a << 24) + (b << 16) + (g << 8) + (r);
		break;

	default:
		break;
	}
	return 0;
}
MALIB_API uint PackColor(COLOR& color, PIXELFORMAT format)
{
	return PackColor(uchar(color.r * 255.0f), uchar(color.g * 255.0f), uchar(color.b * 255.0f), uchar(color.a * 255.0f), format);
}
MALIB_API void UnpackColor(uint c, uchar* r, uchar* g, uchar* b, uchar* a, PIXELFORMAT format)
{
	switch (format)
	{
	case PIXELFORMAT_RGB:
		if (r != NULL) *r = (c << 8) >> 24;
		if (g != NULL) *g = (c << 16) >> 24;
		if (b != NULL) *b = (c << 24) >> 24;
		break;
	case PIXELFORMAT_RGBA:
		if (r != NULL) *r = c >> 24;
		if (g != NULL) *g = (c << 8) >> 24;
		if (b != NULL) *b = (c << 16) >> 24;
		if (a != NULL) *a = (c << 24) >> 24;
		break;
	case PIXELFORMAT_ARGB:
		if (a != NULL) *a = c >> 24;
		if (r != NULL) *r = (c << 8) >> 24;
		if (g != NULL) *g = (c << 16) >> 24;
		if (b != NULL) *b = (c << 24) >> 24;
		break;
		
	case PIXELFORMAT_BGR:
		if (b != NULL) *r = (c << 8) >> 24;
		if (g != NULL) *g = (c << 16) >> 24;
		if (r != NULL) *b = (c << 24) >> 24;
		break;
	case PIXELFORMAT_BGRA:
		if (r != NULL) *b = c >> 24;
		if (g != NULL) *g = (c << 8) >> 24;
		if (b != NULL) *r = (c << 16) >> 24;
		if (a != NULL) *a = (c << 24) >> 24;
		break;
	case PIXELFORMAT_ABGR:
		if (r != NULL) *a = c >> 24;
		if (g != NULL) *b = (c << 8) >> 24;
		if (b != NULL) *g = (c << 16) >> 24;
		if (a != NULL) *r = (c << 24) >> 24;
		break;

	default:
		break;
	}
}
MALIB_API void BlendColor(uchar& dest_r, uchar& dest_g, uchar& dest_b, uchar& dest_a, uchar src_r, uchar src_g, uchar src_b, uchar src_a, PIXELFORMAT format)
{
	float pixel_alpha = float(src_a) / 255.0f;
			
	uchar r = dest_r + (uint)(pixel_alpha * float((int)src_r - (int)dest_r));
	uchar g = dest_g + (uint)(pixel_alpha * float((int)src_g - (int)dest_g));
	uchar b = dest_b + (uint)(pixel_alpha * float((int)src_b - (int)dest_b));

	dest_r = r;
	dest_g = g;
	dest_b = b;
	dest_a = 0xFF;
}

MALIB_API void PutPixel(SURFACE* surface, uint x, uint y, uchar r, uchar g, uchar b, uchar a)
{
	if (surface == NULL) return;
	uint index = (y * surface->width * surface->byteCount) + (x * surface->byteCount);
	uchar* dest = (uchar*)surface->data + index;
	switch (surface->format)
	{
	case PIXELFORMAT_RGB:
		dest[0] = r;
		dest[1] = g;
		dest[2] = b;
		break;
	case PIXELFORMAT_RGBA:
		BlendColor(dest[0], dest[1], dest[2], dest[3], r, g, b, a, surface->format);
		break;
	case PIXELFORMAT_ARGB:
		BlendColor(dest[1], dest[2], dest[3], dest[0], r, g, b, a, surface->format);
		break;
		
	case PIXELFORMAT_BGR:
		dest[0] = b;
		dest[1] = g;
		dest[2] = r;
		break;
	case PIXELFORMAT_BGRA:
		BlendColor(dest[2], dest[1], dest[0], dest[3], r, g, b, a, surface->format);
		break;
	case PIXELFORMAT_ABGR:
		BlendColor(dest[3], dest[2], dest[1], dest[0], r, g, b, a, surface->format);
		break;

	default:
		break;
	}
}
MALIB_API void PutPixel(SURFACE* surface, uint x, uint y, uint color)
{
	uchar alpha = 0x00;
	uchar red = 0x00;
	uchar green = 0x00;
	uchar blue = 0x00;
	UnpackColor(color, &red, &green, &blue, &alpha, surface->format);
	PutPixel(surface, x, y, red, green, blue, alpha);
}
MALIB_API void PutPixel(SURFACE* surface, uint x, uint y, COLOR& color)
{
	PutPixel(surface, x, y, uchar(color.r * 255.0f), uchar(color.g * 255.0f), uchar(color.b * 255.0f), uchar(color.a * 255.0f));
}
MALIB_API void GetPixel(SURFACE* surface, uint x, uint y, uchar* r, uchar* g, uchar* b, uchar* a)
{
	if (surface == NULL) return;
	if (x > surface->width) return;
	if (y > surface->height) return;
	uint index = (y * surface->width * surface->byteCount) + (x * surface->byteCount);
	uchar* dest = (uchar*)surface->data + index;
	uchar alpha = 0x00;
	uchar red = 0x00;
	uchar green = 0x00;
	uchar blue = 0x00;
	switch (surface->format)
	{
	case PIXELFORMAT_RGB:
		alpha = 0xFF;
		red = dest[0];
		green = dest[1];
		blue = dest[2];
		break;
	case PIXELFORMAT_RGBA:
		alpha = dest[3];
		red = dest[0];
		green = dest[1];
		blue = dest[2];
		break;
	case PIXELFORMAT_ARGB:
		alpha = dest[0];
		red = dest[1];
		green = dest[2];
		blue = dest[3];
		break;
		
	case PIXELFORMAT_BGR:
		alpha = 0xFF;
		red = dest[2];
		green = dest[1];
		blue = dest[0];
		break;
	case PIXELFORMAT_BGRA:
		alpha = dest[3];
		red = dest[2];
		green = dest[1];
		blue = dest[0];
		break;
	case PIXELFORMAT_ABGR:
		alpha = dest[0];
		red = dest[3];
		green = dest[2];
		blue = dest[1];
		break;

	default:
		break;
	}
	if (r != NULL) *r = red;
	if (g != NULL) *g = green;
	if (b != NULL) *b = blue;
	if (a != NULL) *a = alpha;
}
MALIB_API void GetPixel(SURFACE* surface, uint x, uint y, COLOR* color)
{
	uchar alpha = 0x00;
	uchar red = 0x00;
	uchar green = 0x00;
	uchar blue = 0x00;
	GetPixel(surface, x, y, &red, &green, &blue, &alpha);
	if (color != NULL) *color = COLOR(float(red) / 255.0f, float(green) / 255.0f, float(blue) / 255.0f, float(alpha) / 255.0f);
}

MALIB_API void DrawBitmap(SURFACE* dest, SURFACE* src, uint x, uint y, DRAWMODE option)
{
	uint x1 = x;
	uint y1 = y;
	uint x2 = x + src->width - 1;
	uint y2 = y + src->height - 1;
	if (x1 >= dest->width) x1 = dest->width - 1;
	if (y1 >= dest->height) y1 = dest->height - 1;
	if (x2 >= dest->width) x2 = dest->width - 1;
	if (y2 >= dest->height) y2 = dest->height - 1;
	for(uint i = 0; i < y2; i++)
	{
		for(uint k = 0; k < x2; k++)
		{
			uint u = k;
			uint v = i;
			if (option & DRAWMODE_FLIPPEDX) u = src->width - k;
			if (option & DRAWMODE_FLIPPEDY) v = src->height - i;

			uchar r, g, b, a = 0x00;
			GetPixel(src, u, v, &r, &g, &b, &a);

			PutPixel(dest, k + x1, i + y1, r, g, b, a);
		}
	}
}
MALIB_API void DrawBitmapCell(SURFACE* dest, SURFACE* src, uint x, uint y, uint cellColumn, uint cellRow, uint cellWidth, uint cellHeight, DRAWMODE option)
{
	uint xDest = x;
	uint yDest = y;
	uint xSrc = cellWidth * cellColumn;
	uint ySrc = cellHeight * cellRow;

	for(uint i = 0; i < cellHeight; i++)
	{
		for(uint k = 0; k < cellWidth; k++)
		{
			uint u = xSrc + k;
			uint v = ySrc + i;
			if (option & DRAWMODE_FLIPPEDX) u = xSrc + (cellWidth - k);
			if (option & DRAWMODE_FLIPPEDY) v = ySrc + (cellHeight - i);
			
			uchar r, g, b, a = 0x00;
			GetPixel(src, u, v, &r, &g, &b, &a);

			PutPixel(dest, xDest + k, yDest + i, r, g, b, a);
		}
	}
}
MALIB_API void ClearBitmap(SURFACE* surface, uint color)
{
	DrawBox(surface, 0, 0, surface->width, surface->height, color);
}

MALIB_API void DrawCircle(SURFACE* surface, uint cx, uint cy, uint r, uint color)
{
	uint x1 = cx - r;
	uint y1 = cy - r;
	uint x2 = cx + r;
	uint y2 = cy + r;
	if (cx < r) x1 = 0;
	else if (x1 >= surface->width) x1 = surface->width - 1;
	if (cy < r) y1 = 0;
	else if (y1 >= surface->height) y1 = surface->height - 1;
	if (cx < r) x2 = 0;
	else if (x2 >= surface->width) x2 = surface->width - 1;
	if (cy < r) y2 = 0;
	else if (y2 >= surface->height) y2 = surface->height - 1;
	uint r2 = r * r;
	for(uint i = y1; i < y2; i++)
	{
		for(uint k = x1; k < x2; k++)
		{
			uint dist2 = ((k - cx) * (k - cx)) + ((i - cy) * (i - cy));
			if(r2 >= dist2)
			{
				PutPixel(surface, k, i, color);
			}
		}
	}
}
MALIB_API void DrawBox(SURFACE* surface, uint x1, uint y1, uint x2, uint y2, uint color)
{
	Clip(x1, y1, 0, 0, surface->width - 1, surface->height - 1);
	Clip(x2, y2, 0, 0, surface->width - 1, surface->height - 1);
	for(uint i = y1; i < y2; i++)
	{
		for(uint k = x1; k < x2; k++)
		{
			PutPixel(surface, k, i, color);
		}
	}
}
MALIB_API void DrawRectangle(SURFACE* surface, uint x, uint y, uint width, uint height, uint color)
{
	DrawBox(surface, x, y, x + width, y + height, color);
}
MALIB_API void DrawLine(SURFACE* surface, uint x1, uint y1, uint x2, uint y2, uint color)
{
	Clip(x1, y1, 0, 0, surface->width - 1, surface->height - 1);
	Clip(x2, y2, 0, 0, surface->width - 1, surface->height - 1);
	if (x1 == x2 && y1 == y2)
	{
		PutPixel(surface, x1, y1, color);
		return;
	}
	float slope = (float(y2) - float(y1)) / (float(x2) - float(x1));
	uint y = 0;
	if (x1 < x2)
	{
		for (uint x = x1; x < x2; x++)
		{
			y = uint(slope * float(x - x1)) + y1;
			PutPixel(surface, x, y, color);
		}
	}
	else if (x1 > x2)
	{
		for (uint x = x1; x > x2; x--)
		{
			y = uint(slope * float(x - x1)) + y1;
			PutPixel(surface, x, y, color);
		}
	}
	else
	{
		if (y1 > y2) Swap(y1, y2);
		DrawBox(surface, x1, y1, x1 + 1, y2, color);
	}
}
MALIB_API void DrawTriangle(SURFACE* surface, uint x1, uint y1, uint x2, uint y2, uint x3, uint y3, uint color)
{
	uint xmin = Min(x1, x2, x3);
	uint ymin = Min(y1, y2, y3);
	uint xmax = Max(x1, x2, x3);
	uint ymax = Max(y1, y2, y3);
	Clip(xmin, ymin, 0, 0, surface->width - 1, surface->height - 1);
	Clip(xmax, ymax, 0, 0, surface->width - 1, surface->height - 1);
	float alpha, beta, gamma = 0.0;
	for (uint i = ymin; i < ymax; i++)
	{
		for (uint k = xmin; k < xmax; k++)
		{
			alpha = float(((y2 - y3) * k) + ((x3 - x2) * i) + (x2 * y3) - (x3 * y2)) / 
							float(((y2 - y3) * x1) + ((x3 - x2) * y1) + (x2 * y3) - (x3 * y2));
			beta = float(((y3 - y1) * k) + ((x1 - x3) * i) + (x3 * y1) - (x1 * y3)) / 
							float(((y3 - y1) * x2) + ((x1 - x3) * y2) + (x3 * y1) - (x1 * y3));
			gamma = float(((y1 - y2) * k) + ((x2 - x1) * i) + (x1 * y2) - (x2 * y1)) / 
							float(((y1 - y2) * x3) + ((x2 - x1) * y3) + (x1 * y2) - (x2 * y1));
			if (alpha >= 0.0f && beta >= 0.0f && gamma >= 0.0f)
			{
				PutPixel(surface, k, i, color);
			}
		}
	}
}

_MALIB_END
#endif