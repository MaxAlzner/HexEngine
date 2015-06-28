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
MALIB_API SURFACE::SURFACE(const string name, void* data, uint width, uint height, PIXELFORMAT format)
{
	this->data = data;
	this->name = name;
	this->width = width;
	this->height = height;
	this->byteCount = ByteCount(format);
	this->format = format;
}
MALIB_API SURFACE::SURFACE(const string name, uint width, uint height, PIXELFORMAT format)
{
	this->data = 0;
	this->name = name;
	this->width = width;
	this->height = height;
	this->format = format;
	this->byteCount = ByteCount(format);
	uint size = this->width * this->height * this->byteCount;
	this->data = new uchar[size];
	memset((void*)this->data, 0, size * sizeof(uchar));
}
MALIB_API SURFACE::~SURFACE()
{
	if (this->data != NULL) delete [] this->data;
	this->data = 0;
}
	
bool MALIB_API ImportBMPFile(const string filepath, SURFACE** outSurface)
{
	if (filepath == NULL || outSurface == NULL) return false;

	FILE* file = 0;
	uchar info[54];
	memset(info, 0, sizeof(uchar) * 54);
	
	fopen_s(&file, filepath, "rb");
	if (file == 0) 
		return false;

	fread(info, sizeof(uchar), 54, file);

	if (info[0] != 'B' || info[1] != 'M')
	{
		fclose(file);
		return false;
	}

	uint bitOffset = *(int*)(&info[10]);
	uint width = *(int*)(&info[18]);
	uint height = *(int*)(&info[22]);
	uint byteCount = *(int*)(&info[28]) / 8;
	
	PIXELFORMAT format = PIXELFORMAT_NONE;
	if (byteCount == 3) format = PIXELFORMAT_BGR;
	if (byteCount == 4) format = PIXELFORMAT_BGRA;
	
	uint bufferSize = width * height * byteCount;
	uchar* buffer = new uchar[bufferSize];
	memset((void*)buffer, 0, bufferSize * sizeof(uchar));

	fseek(file, bitOffset, SEEK_SET);
	fread(buffer, sizeof(unsigned char), bufferSize, file);
	fclose(file);

	*outSurface = new SURFACE(filepath, (void*)buffer, width, height, format);

	return true;
}
bool MALIB_API ImportTGAFile(const string filepath, SURFACE** outSurface)
{
	if (filepath == NULL || outSurface == NULL) return false;

	FILE* file = 0;
	uchar type[4];
	uchar info[6];

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

	uint width = info[0] + (info[1] * 256);
	uint height = info[2] + (info[3] * 256);
	uint byteCount = info[4] / 8;

	if (byteCount != 3 && byteCount != 4)
	{
		fclose(file);
		return false;
	}

	PIXELFORMAT format = PIXELFORMAT_NONE;
	if (byteCount == 3) format = PIXELFORMAT_BGR;
	if (byteCount == 4) format = PIXELFORMAT_BGRA;

	uint bufferSize = width * height * byteCount;
	uchar* buffer = new uchar[bufferSize];
	memset((void*)buffer, 0, bufferSize * sizeof(uchar));

	fread(buffer, sizeof(uchar), bufferSize, file);
	fclose(file);

	*outSurface = new SURFACE(filepath, (void*)buffer, width, height, format);

	return true;
}

bool MALIB_API ExportBMPFile(const string filepath, SURFACE* surface)
{
	if (filepath == NULL || surface == NULL) return false;

	FILE* file = 0;

	uchar info[54];
	memset(info, 0, sizeof(uchar) * 54);
	
	fopen_s(&file, filepath, "wb");
	if (file == 0) 
		return false;
	
	uint bufferSize = surface->width * surface->height * surface->byteCount;
	
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

	fwrite(info, sizeof(uchar), 54, file);
	fwrite(surface->data, sizeof(uchar), bufferSize, file);
	fclose(file);

	return true;
}
bool MALIB_API ExportTGAFile(const string filepath, SURFACE* surface)
{
	if (filepath == NULL || surface == NULL) return false;

	FILE* file = 0;

	uchar type[4];
	uchar info[6];
	memset(type, 0, sizeof(uchar) * 4);
	memset(info, 0, sizeof(uchar) * 6);

	uint bufferSize = surface->width * surface->height * surface->byteCount;

	fopen_s(&file, filepath, "wb");
	if (file == 0) 
		return false;

	type[2] = 2;
	*(int*)(&info[0]) = surface->width;
	*(int*)(&info[2]) = surface->height;
	info[4] = surface->byteCount * 8;
	
	fwrite(&type, sizeof(uchar), 3, file);
	fseek(file, 12, SEEK_SET);
	fwrite(&info, sizeof(uchar), 6, file);

	fwrite(surface->data, sizeof(uchar), bufferSize, file);
	fclose(file);

	return true;
}

void MALIB_API CreateSurface(SURFACE** outSurface, const string name, uint width, uint height, PIXELFORMAT format, void* data)
{
	SURFACE* surface = new SURFACE(name, width, height, format);
	if (data != 0)
	{
		memcpy(surface->data, data, surface->width * surface->height * surface->byteCount * sizeof(uchar));
	}
	if (surface != 0) *outSurface = surface;
}
void MALIB_API FreeSurface(SURFACE** surface)
{
	if (surface == 0 || *surface == 0) return;
	delete *surface;
	*surface = 0;
}
	
_MALIB_END
#endif