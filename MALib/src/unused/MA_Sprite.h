#ifndef _MA_SPRITE_H_
#define _MA_SPRITE_H_

#ifndef _MA_VERTEX_H_
#include "MA_Vertex.h"
#endif
#ifndef _MA_ARRAY_H_
#include "MA_Array.h"
#endif

struct MALIB_API ANIMATIONSET
{
	const char* name;
	unsigned int step;
	unsigned int frames;
	float* data;
};

class MALIB_API SpriteAnimation
{
public:
	SpriteAnimation();
	~SpriteAnimation();
		
	void add(const char* name, int imageWidth, int imageHeight, int columnSpan, int rowSpan, int startColumn, int startRow, int frames = 1, bool flipped = false, int frameDelay = 0);
	void play(const char* name);
	void step();
	void clear();
	
	void getCell(VEC2* outUV1, VEC2* outUV2);
	void getCell(float* outUV1u, float* outUV1v, float* outUV2u, float* outUV2v);
	
private:
	unsigned int current;
	ARRAY<ANIMATIONSET> animations;
};

#endif