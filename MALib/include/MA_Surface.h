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
	SURFACE(const char* name, void* data, unsigned width, unsigned height, PIXELFORMAT format);
	SURFACE(const char* name, unsigned width, unsigned height, PIXELFORMAT format);
	~SURFACE();

	void* data;
	const char* name;
	unsigned width;
	unsigned height;
	unsigned byteCount;
	PIXELFORMAT format;
};
	
bool MALIB_API ImportBMPFile(const char* filepath, SURFACE** outSurface);
bool MALIB_API ImportTGAFile(const char* filepath, SURFACE** outSurface);

bool MALIB_API ExportBMPFile(const char* filepath, SURFACE* surface);
bool MALIB_API ExportTGAFile(const char* filepath, SURFACE* surface);

void MALIB_API CreateSurface(SURFACE** surface, const char* name, unsigned width, unsigned height, PIXELFORMAT format, void* data = 0);
void MALIB_API FreeSurface(SURFACE** surface);

_MALIB_END
#endif