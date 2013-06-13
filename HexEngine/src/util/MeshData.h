#ifndef __MESHDATA_H_
#define __MESHDATA_H_

struct MESHVERT
{
	float pos[4];
	float tex0[2];
	float normal[3];
	float tangent[3];
	float binormal[3];
};

typedef unsigned short MESHINDEX;

struct MESHDATA
{
	MESHDATA()
	{
		this->offset = 0;
		this->vertices = 0;
		this->indices = 0;
		this->name = "";
		this->vertStride = 0;
		this->indexStride = 0;
		this->vertBuffer = NULL;
		this->indexBuffer = NULL;
	}
	~MESHDATA()
	{
		if (this->vertBuffer != NULL) delete [] this->vertBuffer;
		if (this->indexBuffer != NULL) delete [] this->indexBuffer;
	}
	
	unsigned int offset;
	unsigned int vertices;
	unsigned int indices;
	const char* name;
	unsigned int vertStride;
	unsigned int indexStride;
	void* vertBuffer;
	void* indexBuffer;
};

#endif