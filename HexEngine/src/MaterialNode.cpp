#include "..\include\HexMain.h"

#ifdef _MATERIALNODE_H_
HEX_BEGIN

HEX_API MaterialNode::MaterialNode()
{
	this->colorMap = 0;
	this->overlay = MALib::COLOR();
	this->specular = MALib::COLOR();
	this->roughness = 0.8f;
	this->refIndex = 1.4f;
}
HEX_API MaterialNode::~MaterialNode()
{
}
		
HEX_API void MaterialNode::load()
{
	SetTextureSlot(HEX_UNIFORM_COLOR_MAP, this->colorMap);
}
HEX_API void MaterialNode::destroy()
{
}

HEX_API void MaterialNode::add(MALib::SURFACE* texture)
{
	GLuint id = 0;
	glGenTextures(1, &id);
	this->colorMap = id;

	glBindTexture(GL_TEXTURE_2D, id);

	GLenum format = 0;
	if      (texture->format == MALib::PIXELFORMAT_RGBA) format = GL_RGBA;
	else if (texture->format == MALib::PIXELFORMAT_RGB)  format = GL_RGB;
	else if (texture->format == MALib::PIXELFORMAT_BGRA) format = GL_BGRA;
	else if (texture->format == MALib::PIXELFORMAT_BGR)  format = GL_BGR;
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glPixelStorei(GL_PACK_ALIGNMENT, 4);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	glTexImage2D(GL_TEXTURE_2D, 0, texture->byteCount, texture->width, texture->height, 0, format, GL_UNSIGNED_BYTE, texture->data);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}

HEX_END
#endif