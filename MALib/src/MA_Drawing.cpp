#include "..\include\MALib.h"

#ifdef _MA_DRAWING_H_
_MALIB_BEGIN

MALIB_API unsigned int PackColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a, PIXELFORMAT format)
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
MALIB_API void UnpackColor(unsigned int c, unsigned int* r, unsigned int* g, unsigned int* b, unsigned int* a, PIXELFORMAT format)
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

MALIB_API unsigned int BlendColor(unsigned int dest, unsigned int src, PIXELFORMAT format)
{
	unsigned int a1, r1, g1, b1;
	UnpackColor(src, &a1, &r1, &g1, &b1, format);

	unsigned int a2, r2, g2, b2;
	UnpackColor(dest, &a2, &r2, &g2, &b2, format);

	unsigned int a3, r3, g3, b3;
	a3 = a1;
	float pixel_alpha = float(a3) / 255.0f;
			
	r3 = r2 + (unsigned int)(pixel_alpha * float((int)r1 - (int)r2));
	g3 = g2 + (unsigned int)(pixel_alpha * float((int)g1 - (int)g2));
	b3 = b2 + (unsigned int)(pixel_alpha * float((int)b1 - (int)b2));

	return PackColor(r3, g3, b3, a2, format);
}
MALIB_API void PutPixel(unsigned int* data, unsigned int width, unsigned int height, unsigned int x, unsigned int y, unsigned int color, PIXELFORMAT format)
{
	unsigned index = (y * width) + x;
	unsigned alpha = 0xFF;
	UnpackColor(color, NULL, NULL, NULL, NULL, format);
	if (alpha < 0xFF) 
		data[index] = BlendColor(data[index], color);
	else 
		data[index] = color;
}
MALIB_API int GetPixel(unsigned int* data, unsigned int width, unsigned int height, unsigned int x, unsigned int y)
{
	if (x > width) return 0;
	if (y > height) return 0;
	return *(data + (y * width) + x);
}
MALIB_API void DrawBitmap(unsigned int* data, unsigned int width, unsigned int height, unsigned int x, unsigned int y, unsigned int* image, unsigned int imageWidth, unsigned int imageHeight, PIXELFORMAT format, DRAWMODE option)
{
	unsigned x1 = x;
	unsigned y1 = y;
	unsigned x2 = x + imageWidth - 1;
	unsigned y2 = y + imageHeight - 1;
	if (x1 >= width) x1 = width - 1;
	if (y1 >= height) y1 = height - 1;
	if (x2 >= width) x2 = width - 1;
	if (y2 >= height) y2 = height - 1;
	for(unsigned i = 0; i < y2; i++)
	{
		for(unsigned k = 0; k < x2; k++)
		{
			unsigned u = k;
			unsigned v = i;
			if (option & DRAWMODE_FLIPPEDX) u = imageWidth - k;
			if (option & DRAWMODE_FLIPPEDY) v = imageHeight - i;

			unsigned color = GetPixel(image, imageWidth, imageHeight, u, v);

			PutPixel(data, width, height, k + x1, i + y1, color, format);
		}
	}
}
MALIB_API void DrawBitmapCell(unsigned int* data, unsigned int width, unsigned int height, unsigned int xDest, unsigned int yDest, unsigned int* image, unsigned int cellColumn, unsigned int cellRow, unsigned int cellWidth, unsigned int cellHeight, unsigned int imageWidth, unsigned int imageHeight, PIXELFORMAT format, DRAWMODE option)
{
	unsigned xSrc = cellWidth * cellColumn;
	unsigned ySrc = cellHeight * cellRow;

	for(unsigned i = 0; i < cellHeight; i++)
	{
		for(unsigned k = 0; k < cellWidth; k++)
		{
			unsigned u = xSrc + k;
			unsigned v = ySrc + i;
			if (option & DRAWMODE_FLIPPEDX) u = xSrc + (cellWidth - k);
			if (option & DRAWMODE_FLIPPEDY) v = ySrc + (cellHeight - i);

			unsigned color = GetPixel(image, imageWidth, imageHeight, u, v);

			PutPixel(data, width, height, xDest + k, yDest + i, color, format);
		}
	}
}
MALIB_API void ClearBitmap(unsigned int* data, unsigned int width, unsigned int height, unsigned int color, PIXELFORMAT format)
{
	DrawBox(data, width, height, 0, 0, width, height, color, format);
}
MALIB_API void DrawCircle(unsigned int* data, unsigned int width, unsigned int height, unsigned int cx, unsigned int cy, unsigned int r, unsigned int color, PIXELFORMAT format)
{
	unsigned x1 = cx - r;
	unsigned y1 = cy - r;
	unsigned x2 = cx + r;
	unsigned y2 = cy + r;
	if (cx < r) x1 = 0;
	else if (x1 >= width) x1 = width - 1;
	if (cy < r) y1 = 0;
	else if (y1 >= height) y1 = height - 1;
	if (cx < r) x2 = 0;
	else if (x2 >= width) x2 = width - 1;
	if (cy < r) y2 = 0;
	else if (y2 >= height) y2 = height - 1;
	unsigned r2 = r * r;
	for(unsigned i = y1; i < y2; i++)
	{
		for(unsigned k = x1; k < x2; k++)
		{
			unsigned dist2 = ((k - cx) * (k - cx)) + ((i - cy) * (i - cy));
			if(r2 >= dist2)
			{
				PutPixel(data, width, height, k, i, color, format);
			}
		}
	}
}
MALIB_API void DrawBox(unsigned int* data, unsigned int width, unsigned int height, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int color, PIXELFORMAT format)
{
	Clip(x1, y1, 0, 0, width - 1, height - 1);
	Clip(x2, y2, 0, 0, width - 1, height - 1);
	for(unsigned i = y1; i < y2; i++)
	{
		for(unsigned k = x1; k < x2; k++)
		{
			PutPixel(data, width, height, k, i, color, format);
		}
	}
}
MALIB_API void DrawRectangle(unsigned int* data, unsigned int width, unsigned int height, unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int color, PIXELFORMAT format)
{
	DrawBox(data, width, height, x, y, x + w, y + h, color, format);
}
MALIB_API void DrawLine(unsigned int* data, unsigned int width, unsigned int height, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int color, PIXELFORMAT format)
{
	Clip(x1, y1, 0, 0, width - 1, height - 1);
	Clip(x2, y2, 0, 0, width - 1, height - 1);
	if (x1 == x2 && y1 == y2)
	{
		PutPixel(data, width, height, x1, y1, color, format);
		return;
	}
	float slope = float(y2 - y1) / float(x2 - x1);
	unsigned y = 0;
	if (x1 < x2)
	{
		for (unsigned x = x1; x < x2; x++)
		{
			y = unsigned(slope * float(x - x1)) + y1;
			PutPixel(data, width, height, x, y, color, format);
		}
	}
	else if (x1 > x2)
	{
		for (unsigned x = x1; x > x2; x--)
		{
			y = unsigned(slope * float(x - x1)) + y1;
			PutPixel(data, width, height, x, y, color, format);
		}
	}
	else
	{
		if (y1 > y2) Swap(y1, y2);
		DrawBox(data, width, height, x1, y1, x1 + 1, y2, color, format);
	}
}
MALIB_API void DrawTriangle(unsigned int* data, unsigned int width, unsigned int height, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int x3, unsigned int y3, unsigned int color, PIXELFORMAT format)
{
	unsigned xmin = Min(x1, x2, x3);
	unsigned ymin = Min(y1, y2, y3);
	unsigned xmax = Max(x1, x2, x3);
	unsigned ymax = Max(y1, y2, y3);
	Clip(xmin, ymin, 0, 0, width - 1, height - 1);
	Clip(xmax, ymax, 0, 0, width - 1, height - 1);
	float alpha, beta, gamma = 0.0;
	for (unsigned i = ymin; i < ymax; i++)
	{
		for (unsigned k = xmin; k < xmax; k++)
		{
			alpha = float(((y2 - y3) * k) + ((x3 - x2) * i) + (x2 * y3) - (x3 * y2)) / 
							float(((y2 - y3) * x1) + ((x3 - x2) * y1) + (x2 * y3) - (x3 * y2));
			beta = float(((y3 - y1) * k) + ((x1 - x3) * i) + (x3 * y1) - (x1 * y3)) / 
							float(((y3 - y1) * x2) + ((x1 - x3) * y2) + (x3 * y1) - (x1 * y3));
			gamma = float(((y1 - y2) * k) + ((x2 - x1) * i) + (x1 * y2) - (x2 * y1)) / 
							float(((y1 - y2) * x3) + ((x2 - x1) * y3) + (x1 * y2) - (x2 * y1));
			if (alpha >= 0.0f && beta >= 0.0f && gamma >= 0.0f)
			{
				PutPixel(data, width, height, k, i, color, format);
			}
		}
	}
}

_MALIB_END
#endif