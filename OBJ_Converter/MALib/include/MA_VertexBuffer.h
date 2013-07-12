#ifndef _MA_VERTEXBUFFER_H_
#define _MA_VERTEXBUFFER_H_
_MALIB_BEGIN
	
#ifndef _INC_STDIO
#include <stdio.h>
#endif
#ifndef _INC_STRING
#include <string.h>
#endif

struct MALIB_API VERTEXBUFFER
{
	VERTEXBUFFER();
	~VERTEXBUFFER();

	void* buffer;
	unsigned size;
	unsigned stride;
	unsigned components;
	unsigned vertices;
};

bool MALIB_API ImportVMPFile(const char* filepath, VERTEXBUFFER** outVertexBuffer);

bool MALIB_API ExportVMPFile(const char* filepath, VERTEXBUFFER* vertexBuffer);

MALIB_API VERTEXBUFFER* CreateVertexBuffer(void* buffer, unsigned size, unsigned stride, unsigned vertices);

void MALIB_API FreeVertexBuffer(VERTEXBUFFER** bake);

_MALIB_END
#endif