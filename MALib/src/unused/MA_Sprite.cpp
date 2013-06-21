#include "..\include\MALib.h"

SpriteAnimation::SpriteAnimation()
{
	this->current = 0;
}
SpriteAnimation::~SpriteAnimation()
{
	for (unsigned i = 0; i < this->animations.size(); i++) 
		delete [] this->animations[i].data;
}

void SpriteAnimation::add(const char* name, int imageWidth, int imageHeight, 
	int columnSpan, int rowSpan, int startColumn, int startRow, 
	int frames, bool flipped, int frameDelay)
{
	if (frames < 1) return;
	if (name == NULL) name = "";
	if (columnSpan < 0) columnSpan *= -1;
	if (rowSpan < 0) rowSpan *= -1;
	if (startColumn < 0) startColumn = 0;
	if (startRow < 0) startRow = 0;
	if (frameDelay < 0) frameDelay = 0;
	
	frameDelay++;
	float* anim = new float[frames * frameDelay * 4];
	ANIMATIONSET set;
	set.data = anim;
	set.step = 0;
	set.frames = frames * frameDelay;
	set.name = name;
	this->animations.push_back(set);

	float w = float(imageWidth);
	float h = float(imageHeight);
	float span_w = float(columnSpan) / w;
	float span_h = float(rowSpan) / h;
	float x = float(startColumn);
	float y = float(startRow);
	for (int i = 0; i < frames; i++)
	{
		float u = (float(i) + x) * span_w;
		float v = y * span_h;
		float uv1u = Clamp(u);
		float uv1v = Clamp(v);
		float uv2u = Clamp(u + span_w);
		float uv2v = Clamp(v + span_h);

		for (int k = 0; k < frameDelay; k++)
		{
			int n = (i * frameDelay * 4) + (k * 4);
			anim[n + 0] = uv1u;
			anim[n + 1] = uv1v;
			anim[n + 2] = uv2u;
			anim[n + 3] = uv2v;
			if (flipped)
			{
				anim[n + 0] = uv2u;
				anim[n + 2] = uv1u;
			}
		}
	}
}
void SpriteAnimation::play(const char* name)
{
	unsigned int old = this->current;
	for (unsigned i = 0; i < this->animations.size(); i++)
	{
		if (strcmp(this->animations[i].name, name) == 0)
		{
			this->current = i;
			break;
		}
	}
	if (this->current != old) this->animations[this->current].step = 0;
}
void SpriteAnimation::step()
{
	ANIMATIONSET* set = &this->animations[this->current];

	set->step++;
	if (set->step >= set->frames) 
		set->step = 0;
}
void SpriteAnimation::clear()
{
	this->animations.clear();
	this->current = -1;
}

void SpriteAnimation::getCell(VERTEX2* outUV1, VERTEX2* outUV2)
{
	ANIMATIONSET* set = &this->animations[this->current];

	unsigned int i = set->step * 4;
	*outUV1 = VERTEX2(
		set->data[i], 
		set->data[i + 1]);
	*outUV2 = VERTEX2(
		set->data[i + 2], 
		set->data[i + 3]);
}
void SpriteAnimation::getCell(float* outUV1u, float* outUV1v, float* outUV2u, float* outUV2v)
{
	ANIMATIONSET* set = &this->animations[this->current];
	
	unsigned int i = set->step * 4;
	*outUV1u = set->data[i];
	*outUV1v = set->data[i + 1];
	*outUV2u = set->data[i + 2];
	*outUV2v = set->data[i + 3];
}