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
	uint size;
	uint stride;
	uint components;
	uint vertices;
};

bool MALIB_API ImportVMPFile(const string filepath, VERTEXBUFFER** outVertexBuffer);

bool MALIB_API ExportVMPFile(const string filepath, VERTEXBUFFER* vertexBuffer);

MALIB_API VERTEXBUFFER* CreateVertexBuffer(void* buffer, uint size, uint stride, uint vertices);

void MALIB_API FreeVertexBuffer(VERTEXBUFFER** bake);

_MALIB_END
#endif