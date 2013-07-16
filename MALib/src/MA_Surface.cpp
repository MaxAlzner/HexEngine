#include "..\include\MALib.h"

#ifdef _MA_SURFACE_H_
_MALIB_BEGIN

MALIB_API SURFACE::SURFACE()
{
	this->data = 0;
	this->name = "";
	this->width = 0;
	this->height = 0;
	this->byteCount = 4;
	this->format = PIXELFORMAT_NONE;
}
MALIB_API SURFACE::SURFACE(const char* name, void* data, unsigned width, unsigned height, PIXELFORMAT format)
{
	this->data = data;
	this->name = name;
	this->width = width;
	this->height = height;
	this->byteCount = ByteCount(format);
	this->format = format;
}
MALIB_API SURFACE::SURFACE(const char* name, unsigned width, unsigned height, PIXELFORMAT format)
{
	this->data = 0;
	this->name = name;
	this->width = width;
	this->height = height;
	this->format = format;
	this->byteCount = ByteCount(format);
	unsigned size = this->width * this->height * this->byteCount;
	this->data = new unsigned char[size];
	memset((void*)this->data, 0, size * sizeof(unsigned char));
}
MALIB_API SURFACE::~SURFACE()
{
	if (this->data != NULL) delete [] this->data;
	this->data = 0;
}
	
bool MALIB_API ImportBMPFile(const char* filepath, SURFACE** outSurface)
{
	if (filepath == NULL || outSurface == NULL) return false;

	FILE* file = 0;
	unsigned char info[54];
	memset(info, 0, sizeof(unsigned char) * 54);
	
	fopen_s(&file, filepath, "rb");
	if (file == 0) 
		return false;

	fread(info, sizeof(unsigned char), 54, file);

	if (info[0] != 'B' || info[1] != 'M')
	{
		fclose(file);
		return false;
	}

	unsigned bitOffset = *(int*)(&info[10]);
	unsigned width = *(int*)(&info[18]);
	unsigned height = *(int*)(&info[22]);
	unsigned byteCount = *(int*)(&info[28]) / 8;
	
	PIXELFORMAT format = PIXELFORMAT_NONE;
	if (byteCount == 3) format = PIXELFORMAT_BGR;
	if (byteCount == 4) format = PIXELFORMAT_BGRA;
	
	unsigned bufferSize = width * height * byteCount;
	unsigned char* buffer = new unsigned char[bufferSize];
	memset((void*)buffer, 0, bufferSize * sizeof(unsigned char));

	fseek(file, bitOffset, SEEK_SET);
	fread(buffer, sizeof(unsigned char), bufferSize, file);
	fclose(file);

	*outSurface = new SURFACE(filepath, (void*)buffer, width, height, format);

	return true;
}
bool MALIB_API ImportTGAFile(const char* filepath, SURFACE** outSurface)
{
	if (filepath == NULL || outSurface == NULL) return false;

	FILE* file = 0;
	unsigned char type[4];
	unsigned char info[6];

	fopen_s(&file, filepath, "rb");
	if (file == 0) 
		return false;

	fread(&type, sizeof(char), 3, file);
	fseek(file, 12, SEEK_SET);
	fread(&info, sizeof(char), 6, file);

	if (type[1] != 0 || (type[2] != 2 && type[3] != 3))
	{
		fclose(file);
		return false;
	}

	unsigned width = info[0] + (info[1] * 256);
	unsigned height = info[2] + (info[3] * 256);
	unsigned byteCount = info[4] / 8;

	if (byteCount != 3 && byteCount != 4)
	{
		fclose(file);
		return false;
	}

	PIXELFORMAT format = PIXELFORMAT_NONE;
	if (byteCount == 3) format = PIXELFORMAT_BGR;
	if (byteCount == 4) format = PIXELFORMAT_BGRA;

	unsigned bufferSize = width * height * byteCount;
	unsigned char* buffer = new unsigned char[bufferSize];
	memset((void*)buffer, 0, bufferSize * sizeof(unsigned char));

	fread(buffer, sizeof(unsigned char), bufferSize, file);
	fclose(file);

	*outSurface = new SURFACE(filepath, (void*)buffer, width, height, format);

	return true;
}

bool MALIB_API ExportBMPFile(const char* filepath, SURFACE* surface)
{
	if (filepath == NULL || surface == NULL) return false;

	FILE* file = 0;

	unsigned char info[54];
	memset(info, 0, sizeof(unsigned char) * 54);
	
	fopen_s(&file, filepath, "wb");
	if (file == 0) 
		return false;
	
	unsigned bufferSize = surface->width * surface->height * surface->byteCount;
	
	info[0] = 'B';
	info[1] = 'M';
	*(int*)(&info[2]) = 54 + bufferSize;// file size
	*(int*)(&info[10]) = 54;
	*(int*)(&info[14]) = 40;
	*(int*)(&info[18]) = surface->width;
	*(int*)(&info[22]) = surface->height;
	*(int*)(&info[26]) = 1;
	*(int*)(&info[28]) = surface->byteCount * 8;
	*(int*)(&info[34]) = bufferSize;

	fwrite(info, sizeof(unsigned char), 54, file);
	fwrite(surface->data, sizeof(unsigned char), bufferSize, file);
	fclose(file);

	return true;
}
bool MALIB_API ExportTGAFile(const char* filepath, SURFACE* surface)
{
	if (filepath == NULL || surface == NULL) return false;

	FILE* file = 0;

	unsigned char type[4];
	unsigned char info[6];
	memset(type, 0, sizeof(unsigned char) * 4);
	memset(info, 0, sizeof(unsigned char) * 6);

	unsigned bufferSize = surface->width * surface->height * surface->byteCount;

	fopen_s(&file, filepath, "wb");
	if (file == 0) 
		return false;

	type[2] = 2;
	*(int*)(&info[0]) = surface->width;
	*(int*)(&info[2]) = surface->height;
	info[4] = surface->byteCount * 8;
	
	fwrite(&type, sizeof(unsigned char), 3, file);
	fseek(file, 12, SEEK_SET);
	fwrite(&info, sizeof(unsigned char), 6, file);

	fwrite(surface->data, sizeof(unsigned char), bufferSize, file);
	fclose(file);

	return true;
}

void MALIB_API CreateSurface(SURFACE** surface, const char* name, unsigned width, unsigned height, PIXELFORMAT format)
{
	*surface = new SURFACE(name, width, height, format);
}
void MALIB_API FreeSurface(SURFACE** surface)
{
	delete *surface;
	*surface = 0;
}
	
_MALIB_END
#endif