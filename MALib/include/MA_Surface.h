#ifndef _MA_SURFACE_H_
#define _MA_SURFACE_H_
_MALIB_BEGIN
	
#ifndef _INC_STDIO
#include <stdio.h>
#endif
#ifndef _INC_STRING
#include <string.h>
#endif
#ifndef _MA_DRAWING_H_
#include "MA_Drawing.h"
#endif

struct MALIB_API SURFACE
{
	SURFACE();
	SURFACE(const string name, void* data, uint width, uint height, PIXELFORMAT format);
	SURFACE(const string name, uint width, uint height, PIXELFORMAT format);
	~SURFACE();

	void* data;
	string name;
	unsigned width;
	unsigned height;
	unsigned byteCount;
	PIXELFORMAT format;
};
	
bool MALIB_API ImportBMPFile(const string filepath, SURFACE** outSurface);
bool MALIB_API ImportTGAFile(const string filepath, SURFACE** outSurface);

bool MALIB_API ExportBMPFile(const string filepath, SURFACE* surface);
bool MALIB_API ExportTGAFile(const string filepath, SURFACE* surface);

void MALIB_API CreateSurface(SURFACE** outSurface, const string name, uint width, uint height, PIXELFORMAT format, void* data = 0);
void MALIB_API FreeSurface(SURFACE** surface);

_MALIB_END
#endif