#ifndef __TEXTURE_H_
#define __TEXTURE_H_

struct TEXTURE
{
	TEXTURE()
	{
		this->data = 0;
		this->name = "";
		this->width = 0;
		this->height = 0;
		this->bytes = 0;
	}
	TEXTURE(const char* name, unsigned int* data, unsigned int width, unsigned int height, unsigned int bytes)
	{
		this->data = data;
		this->name = name;
		this->width = width;
		this->height = height;
		this->bytes = bytes;
	}
	TEXTURE(const char* name, int width, int height)
	{
		this->data = 0;
		this->name = name;
		this->width = width;
		this->height = height;
		this->bytes = bytes;
		this->data = new unsigned int[width * height];
	}
	~TEXTURE()
	{
		if (this->data != NULL) delete [] this->data;
	}
	unsigned int* data;
	const char* name;
	unsigned int width, height, bytes;
};

#endif