#ifndef __TEXTURE_H_
#define __TEXTURE_H_

struct TEXTURE
{
	TEXTURE()
	{
		this->video = NULL;
		this->name = "";
		this->width = 0;
		this->height = 0;
		this->id = 0;
	}
	TEXTURE(const char* name, int id, unsigned int* image, int imageWidth, int imageHeight)
	{
		this->video = image;
		this->name = name;
		this->width = imageWidth;
		this->height = imageHeight;
		this->id = id;
	}
	TEXTURE(const char* name, int id, int imageWidth, int imageHeight)
	{
		this->video = new unsigned int[width * height];
		this->name = name;
		this->width = imageWidth;
		this->height = imageHeight;
		this->id = id;
	}
	~TEXTURE()
	{
		if (this->video != NULL) delete [] this->video;
	}
	unsigned int* video;
	const char* name;
	int width, height, widthPadding, id;
};

#endif