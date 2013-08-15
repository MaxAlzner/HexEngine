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

MaterialNode::MaterialNode()
{
	this->colorTexture = 0;
	this->normalTexture = 0;
	this->specularTexture = 0;
	this->colorMap = 0;
	this->normalMap = 0;
	this->specularMap = 0;

	this->overlay = MALib::COLOR();
	this->specular = MALib::COLOR();
	this->roughness = 0.8f;
	this->refIndex = 1.4f;
	this->uvRepeat = MALib::VEC2(1.0f, 1.0f);
	this->uvOffset = MALib::VEC2(0.0f, 0.0f);
	this->shadowCaster = false;
	this->built = false;
}
MaterialNode::~MaterialNode()
{
}
		
void MaterialNode::load()
{
	SetTextureSlot(UNIFORM_TEXTURE_COLOR_MAP, this->colorMap);
	SetTextureSlot(UNIFORM_TEXTURE_NORMAL_MAP, this->normalMap);
	SetTextureSlot(UNIFORM_TEXTURE_SPECULAR_MAP, this->specularMap);
	SetUniform(UNIFORM_UV_REPEAT, &this->uvRepeat);
	SetUniform(UNIFORM_UV_OFFSET, &this->uvOffset);
}
void MaterialNode::unload()
{
}
void MaterialNode::build()
{
	MALib::SURFACE* diffuse = GetTexture(this->colorTexture);
	MALib::SURFACE* normal = GetTexture(this->normalTexture);
	MALib::SURFACE* specular = GetTexture(this->specularTexture);

	MaterialNode::BuildTexture(&this->colorMap, diffuse);
	MaterialNode::BuildTexture(&this->normalMap, normal);
	MaterialNode::BuildTexture(&this->specularMap, specular);

	this->built = true;
}
void MaterialNode::destroy()
{
	glDeleteTextures(1, &this->colorMap);
	glDeleteTextures(1, &this->normalMap);
	glDeleteTextures(1, &this->specularMap);
	this->built = false;
}

void MaterialNode::setColorMap(uint texture)
{
	this->colorTexture = texture;
}
void MaterialNode::setNormalMap(uint texture)
{
	this->normalTexture = texture;
}
void MaterialNode::setSpecularMap(uint texture)
{
	this->specularTexture = texture;
}

void MaterialNode::setOverlay(float r, float g, float b)
{
	this->overlay.r = r;
	this->overlay.g = g;
	this->overlay.b = b;
}
void MaterialNode::setSpecular(float r, float g, float b)
{
	this->specular.r = r;
	this->specular.g = g;
	this->specular.b = b;
}
void MaterialNode::setRoughness(float v)
{
	this->roughness = v;
}
void MaterialNode::setRefractionIndex(float v)
{
	this->refIndex = v;
}

void MaterialNode::repeatUV(float u, float v)
{
	this->uvRepeat.x *= u;
	this->uvRepeat.y *= v;
}
void MaterialNode::offsetUV(float u, float v)
{
	this->uvOffset.x *= u;
	this->uvOffset.y *= v;
}

void MaterialNode::makeCaster(bool v)
{
	this->shadowCaster = v;
	Casters.remove(this->root);
	if (this->shadowCaster)
	{
		Casters.add(this->root);
	}
}

void MaterialNode::BuildTexture(GLuint* outID, MALib::SURFACE* texture)
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
void MaterialNode::BuildTexture(GLuint* outID, SDL_Surface* texture)
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