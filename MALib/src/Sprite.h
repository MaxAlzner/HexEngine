#ifndef __SPRITE_H_
#define __SPRITE_H_

struct ANIMATIONSET
{
	const char* name;
	unsigned int step;
	unsigned int frames;
	float* data;
};

class SpriteAnimation
{
public:
	SpriteAnimation();
	~SpriteAnimation();
		
	void add(const char* name, int imageWidth, int imageHeight, 
		int columnSpan, int rowSpan, int startColumn, int startRow, 
		int frames = 1, bool flipped = false, int frameDelay = 0);
	void play(const char* name);
	void step();
	void clear();
	
	void getCell(VERTEX2* outUV1, VERTEX2* outUV2);
	void getCell(float* outUV1u, float* outUV1v, float* outUV2u, float* outUV2v);
	
private:
	unsigned int current;
	vector<ANIMATIONSET> animations;
};

#endif