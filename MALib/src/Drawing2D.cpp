#include "StdAfx.h"

void CORE::Drawing::PutPixel(unsigned int *video, int width, int height, int x, int y, unsigned int color)
{
	int index = (y * width) + x;
	if (ARGB::GetAlpha(color) < 0xFF) video[index] = ARGB::BlendColor(video[index], color);
	else video[index] = color;
}
int CORE::Drawing::GetPixel(unsigned int* video, int width, int height, int x, int y)
{
	if (x < 0 || x > width) return 0;
	if (y < 0 || y > height) return 0;
	return *(video + (y * width) + x);
}
void CORE::Drawing::DrawBitmap(unsigned int *video, int width, int height, int x1, int y1, 
	unsigned int *image, int nImageWidth, int nImageHeight, int option)
{
	int x2 = x1 + nImageWidth - 1;
	int y2 = y1 + nImageHeight - 1;
	clipBounds(x1, y1, 0, 0, width, height);
	clipBounds(x2, y2, 0, 0, width, height);
	for(int y = 0; y < y2; y++)
	{
		for(int x = 0; x < x2; x++)
		{
			unsigned int color = 0;
			if (option & OPTION_FLIPPED) color = GetPixel(image, nImageWidth, nImageHeight, nImageWidth - x, y);
			else color = GetPixel(image, nImageWidth, nImageHeight, x, y);

			if (ARGB::GetAlpha(color) == 0x00) continue;

			PutPixel(video, width, height, x + x1, y + y1, color);
		}
	}
}
void CORE::Drawing::DrawBitmapCell(unsigned int *video, int width, int height, int xDest, int yDest, 
	unsigned int *image, int nCellColumn, int nCellRow, int nCellWidth, int nCellHeight, 
	int nImageWidth, int nImageHeight, int option) {

	int src_x = nCellWidth * nCellColumn;
	int src_y = nCellHeight * nCellRow;

	for(int y = 0; y < nCellHeight; y++)
	{
		for(int x = 0; x < nCellWidth; x++)
		{
			unsigned int color = 0;
			if (option & OPTION_FLIPPED) color = GetPixel(image, nImageWidth, nImageHeight, src_x + (nCellWidth - x), src_y + y);
			else color = GetPixel(image, nImageWidth, nImageHeight, src_x + x, src_y + y);

			if (ARGB::GetAlpha(color) == 0x00) continue;

				PutPixel(video, width, height, xDest + x, yDest + y, color);
		}
	}
}
void CORE::Drawing::ClearBitmap(unsigned int *video, int width, int height, unsigned int color)
{
	DrawBox(video, width, height, 0, 0, width, height, color);
}
void CORE::Drawing::DrawCircle(unsigned int *video, int width, int height, int cx, int cy, int radius, unsigned int color)
{
	int x1 = cx - radius;
	int y1 = cy - radius;
	int x2 = cx + radius;
	int y2 = cy + radius;
	clipBounds(x1, y1, 0, 0, width, height);
	clipBounds(x2, y2, 0, 0, width, height);
	int radiusSquared = radius * radius;
	for(int i = y1; i < y2; i++)
	{
		for(int k = x1; k < x2; k++)
		{
			int dist2 = ((k - cx) * (k - cx)) + ((i - cy) * (i - cy));
			if(radiusSquared >= dist2)
			{
				PutPixel(video, width, height, k, i, color);
			}
		}
	}
}
void CORE::Drawing::DrawBox(unsigned int *video, int width, int height, int x1, int y1, int x2, int y2, unsigned int color)
{
	if (x1 > x2) swap(x1, x2);
	if (y1 > y2) swap(y1, y2);
	clipBounds(x1, y1, 0, 0, width, height);
	clipBounds(x2, y2, 0, 0, width, height);
	for(int i = y1; i < y2; i++)
	{
		for(int k = x1; k < x2; k++)
		{
			PutPixel(video, width, height, k, i, color);
		}
	}
}
void CORE::Drawing::DrawRectangle(unsigned int *video, int width, int height, int x, int y, int w, int h, unsigned int color)
{
	DrawBox(video, width, height, x, y, x + w, y + h, color);
}
void CORE::Drawing::DrawLine(unsigned int* video, int width, int height, int x1, int y1, int x2, int y2, unsigned int color)
{
	clipBounds(x1, y1, 0, 0, width, height);
	clipBounds(x2, y2, 0, 0, width - 1, height - 1);
	if (x1 == x2 && y1 == y2) {PutPixel(video, width, height, x1, y1, color);return;}
	float slope = float(y2 - y1) / float(x2 - x1);
	int y = 0;
	if (x1 < x2)
	{
		for (int x = x1; x < x2; x++)
		{
			y = int(slope * float(x - x1)) + y1;
			PutPixel(video, width, height, x, y, color);
		}
	}
	else if (x1 > x2)
	{
		for (int x = x1; x > x2; x--)
		{
			y = int(slope * float(x - x1)) + y1;
			PutPixel(video, width, height, x, y, color);
		}
	}
	else
	{
		if (y1 > y2) swap(y1, y2);
		DrawBox(video, width, height, x1, y1, x1 + 1, y2, color);
	}
}
void CORE::Drawing::DrawTriangle(unsigned int* video, int width, int height, 
	int x1, int y1, int x2, int y2, int x3, int y3, unsigned int color)
{
	int xmin = x1;
	int ymin = y1;
	int xmax = x3;
	int ymax = y3;
	if (xmin > x2) xmin = x2;
	if (xmin > x3) xmin = x3;
	if (ymin > y2) ymin = y2;
	if (ymin > y3) ymin = y3;
	if (xmax < x2) xmax = x2;
	if (xmax < x1) xmax = x1;
	if (ymax < y2) ymax = y2;
	if (ymax < y1) ymax = y1;
	clipBounds(xmin, ymin, 0, 0, width, height);
	clipBounds(xmax, ymax, 0, 0, width, height);
	float alpha, beta, gamma = 0.0;
	for (int i = ymin; i < ymax; i++)
	{
		for (int k = xmin; k < xmax; k++)
		{
			alpha = float(((y2 - y3) * k) + ((x3 - x2) * i) + (x2 * y3) - (x3 * y2)) / 
							float(((y2 - y3) * x1) + ((x3 - x2) * y1) + (x2 * y3) - (x3 * y2));
			beta = float(((y3 - y1) * k) + ((x1 - x3) * i) + (x3 * y1) - (x1 * y3)) / 
							float(((y3 - y1) * x2) + ((x1 - x3) * y2) + (x3 * y1) - (x1 * y3));
			gamma = float(((y1 - y2) * k) + ((x2 - x1) * i) + (x1 * y2) - (x2 * y1)) / 
							float(((y1 - y2) * x3) + ((x2 - x1) * y3) + (x1 * y2) - (x2 * y1));
			if (alpha >= 0.0 && beta >= 0.0 && gamma >= 0.0)
			{
				PutPixel(video, width, height, k, i, color);
			}
		}
	}
}
void CORE::Drawing::DrawFace(unsigned int* video, int width, int height, 
	VERTEX &v1, VERTEX &v2, VERTEX &v3, 
	COLOR &c1, COLOR &c2, COLOR &c3)
{
	int xmin = int(v1.x);
	int ymin = int(v1.y);
	int xmax = int(v3.x);
	int ymax = int(v3.y);
	if (xmin > v2.x) xmin = int(v2.x);
	if (xmin > v3.x) xmin = int(v3.x);
	if (ymin > v2.y) ymin = int(v2.y);
	if (ymin > v3.y) ymin = int(v3.y);
	if (xmax < v2.x) xmax = int(v2.x);
	if (xmax < v1.x) xmax = int(v1.x);
	if (ymax < v2.y) ymax = int(v2.y);
	if (ymax < v1.y) ymax = int(v1.y);
	xmax++;
	ymax++;
	clipBounds(xmin, ymin, 0, 0, width, height);
	clipBounds(xmax, ymax, 0, 0, width, height);
	float alpha, beta, gamma = 0.f;
	unsigned int color;
	for (int i = ymin; i < ymax; i++)
	{
		for (int k = xmin; k < xmax; k++)
		{
			float x = float(k);
			float y = float(i);
			alpha = (((v2.y - v3.y) * k) + ((v3.x - v2.x) * i) + (v2.x * v3.y) - (v3.x * v2.y)) / 
				(((v2.y - v3.y) * v1.x) + ((v3.x - v2.x) * v1.y) + (v2.x * v3.y) - (v3.x * v2.y));
			beta = (((v3.y - v1.y) * k) + ((v1.x - v3.x) * i) + (v3.x * v1.y) - (v1.x * v3.y)) / 
				(((v3.y - v1.y) * v2.x) + ((v1.x - v3.x) * v2.y) + (v3.x * v1.y) - (v1.x * v3.y));
			gamma = 1.f - (alpha + beta);
			if (alpha >= 0.f && beta >= 0.f && gamma >= 0.f)
			{
				color = ARGB::CreateARGB(
					0xFF * unsigned int((alpha * c1.a) + (beta * c2.a) + (gamma * c3.a)), 
					0xFF * unsigned int((alpha * c1.r) + (beta * c2.r) + (gamma * c3.r)), 
					0xFF * unsigned int((alpha * c1.g) + (beta * c2.g) + (gamma * c3.g)), 
					0xFF * unsigned int((alpha * c1.b) + (beta * c2.b) + (gamma * c3.b)));
						
				PutPixel(video, width, height, k, i, color);
			}
		}
	}
}