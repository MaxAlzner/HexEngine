#include "..\include\MALib.h"

#ifdef _MA_VERTEXBUFFER_H_
_MALIB_BEGIN
	
MALIB_API VERTEXBUFFER::VERTEXBUFFER()
{
	this->buffer = 0;
	this->size = 0;
	this->stride = 0;
	this->components = 0;
	this->vertices = 0;
}
MALIB_API VERTEXBUFFER::~VERTEXBUFFER()
{
	if (this->buffer != NULL) delete [] this->buffer;
}

bool MALIB_API ImportVMPFile(const char* filepath, VERTEXBUFFER** outVertexBuffer)
{
	if (filepath == NULL || outVertexBuffer == NULL) return false;
	
	FILE* file = 0;
	unsigned char info[18];
	memset(info, 0, sizeof(unsigned char) * 18);
	
	fopen_s(&file, filepath, "rb");
	if (file == 0) 
		return false;

	fread(info, sizeof(unsigned char), 18, file);

	if (info[0] != 'V' || info[1] != 'M')
	{
		fclose(file);
		return false;
	}
	
	unsigned size = *(int*)(&info[2]);
	unsigned stride = *(int*)(&info[6]);
	unsigned components = *(int*)(&info[10]);
	unsigned vertices = *(int*)(&info[14]);

	float* buffer = new float[size];
	fseek(file, sizeof(unsigned char) * 18, SEEK_SET);
	fread(buffer, sizeof(float), size, file);
	fclose(file);

	*outVertexBuffer = CreateVertexBuffer(buffer, size, stride, vertices);

	return true;
}

bool MALIB_API ExportVMPFile(const char* filepath, VERTEXBUFFER* vertexBuffer)
{
	if (filepath == NULL || vertexBuffer == NULL) return false;
	
	FILE* file = 0;
	unsigned char info[18];
	memset(info, 0, sizeof(unsigned char) * 18);
	
	fopen_s(&file, filepath, "wb");
	if (file == 0) 
		return false;

	info[0] = 'V';
	info[1] = 'M';
	*(int*)(&info[2]) = vertexBuffer->size;
	*(int*)(&info[6]) = vertexBuffer->stride;
	*(int*)(&info[10]) = vertexBuffer->components;
	*(int*)(&info[14]) = vertexBuffer->vertices;

	float* b = (float*)vertexBuffer->buffer;

	fwrite(info, sizeof(unsigned char), 18, file);
	fseek(file, sizeof(unsigned char) * 18, SEEK_SET);
	fwrite(vertexBuffer->buffer, sizeof(float), vertexBuffer->size, file);
	fclose(file);

	return true;
}

MALIB_API VERTEXBUFFER* CreateVertexBuffer(void* buffer, unsigned size, unsigned stride, unsigned vertices)
{
	VERTEXBUFFER* vb = new VERTEXBUFFER;
	vb->buffer = buffer;
	vb->size = size;
	vb->stride = stride;
	vb->vertices = vertices;
	vb->components = (vb->size / vb->vertices) / 4;
	return vb;
}

void MALIB_API FreeVertexBuffer(VERTEXBUFFER** bake)
{
	delete *bake;
	*bake = 0;
}

_MALIB_END
#endif