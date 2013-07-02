#include "..\include\HexMain.h"

#ifdef _MATERIALNODE_H_
HEX_BEGIN

#define HEX_TEX_PARAMETERS \
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);\
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);\
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);\
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);\
	glPixelStorei(GL_PACK_ALIGNMENT, 4);\
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

HEX_API MaterialNode::MaterialNode()
{
	this->colorMap = 0;
	this->normalMap = 0;
	this->overlay = MALib::COLOR();
	this->specular = MALib::COLOR();
	this->roughness = 0.8f;
	this->refIndex = 1.4f;
	this->uvRepeat = MALib::VEC2(1.0f, 1.0f);
}
HEX_API MaterialNode::~MaterialNode()
{
}
		
HEX_API void MaterialNode::load()
{
	SetTextureSlot(UNIFORM_COLOR_MAP, this->colorMap);
	SetTextureSlot(UNIFORM_NORMAL_MAP, this->normalMap);
	SetUniform(UNIFORM_UV_REPEAT, &this->uvRepeat);
}
HEX_API void MaterialNode::destroy()
{
}

HEX_API void MaterialNode::setColorMap(MALib::SURFACE* texture)
{
	MaterialNode::BuildTexture(&this->colorMap, texture);
}
HEX_API void MaterialNode::setColorMap(SDL_Surface* texture)
{
	MaterialNode::BuildTexture(&this->colorMap, texture);
}
HEX_API void MaterialNode::setNormalMap(MALib::SURFACE* texture)
{
	MaterialNode::BuildTexture(&this->normalMap, texture);
}
HEX_API void MaterialNode::setNormalMap(SDL_Surface* texture)
{
	MaterialNode::BuildTexture(&this->normalMap, texture);
}

HEX_API void MaterialNode::BuildTexture(GLuint* outID, MALib::SURFACE* texture)
{
	if (outID == NULL || texture == NULL) return;

	GLuint id = 0;
	glGenTextures(1, &id);

	glBindTexture(GL_TEXTURE_2D, id);

	GLenum format = 0;
	if      (texture->format == MALib::PIXELFORMAT_RGBA) format = GL_RGBA;
	else if (texture->format == MALib::PIXELFORMAT_RGB)  format = GL_RGB;
	else if (texture->format == MALib::PIXELFORMAT_BGRA) format = GL_BGRA;
	else if (texture->format == MALib::PIXELFORMAT_BGR)  format = GL_BGR;

	HEX_TEX_PARAMETERS
	glTexImage2D(GL_TEXTURE_2D, 0, texture->byteCount, texture->width, texture->height, 0, format, GL_UNSIGNED_BYTE, texture->data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	*outID = id;
}
HEX_API void MaterialNode::BuildTexture(GLuint* outID, SDL_Surface* texture)
{
	if (outID == NULL || texture == NULL) return;

	GLuint id = 0;
	glGenTextures(1, &id);

	glBindTexture(GL_TEXTURE_2D, id);

	GLenum format = GL_RED;
	int channels = texture->format->BytesPerPixel;
	if (channels == 4)
	{
		if (texture->format->Rmask == 0x000000FF) 
			format = GL_RGBA;
		else 
			format = GL_BGRA;
	}
	else if (channels == 3)
	{
		if (texture->format->Rmask == 0x000000FF) 
			format = GL_RGB;
		else 
			format = GL_BGR;
	}
	
	HEX_TEX_PARAMETERS
	glTexImage2D(GL_TEXTURE_2D, 0, channels, texture->w, texture->h, 0, format, GL_UNSIGNED_BYTE, texture->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	*outID = id;
}

HEX_END
#endif