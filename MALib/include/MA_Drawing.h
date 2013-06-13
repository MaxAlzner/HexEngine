#ifndef _MA_DRAWING_H_
#define _MA_DRAWING_H_

namespace CORE
{
#define OPTION_NORMAL 0
#define OPTION_ALPHA 1
#define OPTION_FLIPPED 2

	class Drawing
	{
	public:
		static void PutPixel(unsigned int *video, int width, int height, int x, int y, unsigned int color);
		static int GetPixel(unsigned int* video, int width, int height, int x, int y);
		static void DrawBitmap(unsigned int *video, int width, int height, int x1, int y1, 
			unsigned int *image, int nImageWidth, int nImageHeight, int option = OPTION_NORMAL);
		static void DrawBitmapCell(unsigned int *video, int width, int height, int xDest, int yDest, 
			unsigned int *image, int nCellColumn, int nCellRow, int nCellWidth, int nCellHeight, 
			int nImageWidth, int nImageHeight, int option = OPTION_NORMAL);
		static void ClearBitmap(unsigned int *video, int width, int height, unsigned int color);
		static void DrawCircle(unsigned int *video, int width, int height, int cx, int cy, int r, unsigned int color);
		static void DrawBox(unsigned int* video, int width, int height, int x1, int y1, int x2, int y2, unsigned int color);
		static void DrawRectangle(unsigned int* video, int width, int height, int x, int y, int w, int h, unsigned int color);
		static void DrawLine(unsigned int* video, int width, int height, int x1, int y1, int x2, int y2, unsigned int color);
		static void DrawTriangle(unsigned int* video, int width, int height, 
			int x1, int y1, int x2, int y2, int x3, int y3, unsigned int color);
		static void DrawFace(unsigned int* video, int width, int height, 
			VERTEX &v1, VERTEX &v2, VERTEX &v3, 
			COLOR &c1, COLOR &c2, COLOR &c3);
	};
}

#endif