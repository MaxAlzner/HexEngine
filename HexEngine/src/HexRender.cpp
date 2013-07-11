#include "..\include\HexMain.h"

#ifdef _HEX_RENDER_H_
HEX_BEGIN

HexRender::HexRender()
{
	this->width = 0;
	this->height = 0;
	this->framebuffer = 0;
	this->colorMap = 0;
	this->depthMap = 0;
}
HexRender::~HexRender()
{
}

void HexRender::build(uint width, uint height, bool attachColor, bool attachDepth)
{
	this->width = width;
	this->height = height;
	if (this->framebuffer == 0) glGenFramebuffers(1, &this->framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer);

	if (this->colorMap != 0) glDeleteTextures(1, &this->colorMap);
	if (this->depthMap != 0) glDeleteTextures(1, &this->depthMap);

	if (attachColor)
	{
		glGenTextures(1, &this->colorMap);
		glBindTexture(GL_TEXTURE_2D, this->colorMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_INT, NULL);
		glGenerateMipmap(GL_TEXTURE_2D);
		
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->colorMap, 0);
	}
	if (attachDepth)
	{
		glGenTextures(1, &this->depthMap);
		glBindTexture(GL_TEXTURE_2D, this->depthMap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
		//glTexParameteri( GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, this->width, this->height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);

		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->depthMap, 0);
	}

	if (!attachColor)
	{
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
	}
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void HexRender::load()
{
	glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer);
	glViewport(0, 0, this->width, this->height);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void HexRender::unload()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void HexRender::destroy()
{
	glDeleteTextures(1, &this->colorMap);
	glDeleteTextures(1, &this->depthMap);
	glDeleteFramebuffers(1, &this->framebuffer);
}

void HexRender::blit()
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, this->framebuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	if (this->colorMap != 0) glBlitFramebuffer(0, 0, ScreenDimensions[0], ScreenDimensions[1], 0, 0, this->width, this->height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	if (this->depthMap != 0) glBlitFramebuffer(0, 0, ScreenDimensions[0], ScreenDimensions[1], 0, 0, this->width, this->height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

uint ScreenVAO = 0;
uint ScreenBuffer = 0;

void InitializePostProcess()
{
	static float ScreenPlane[24] = 
	{
		1.0f, 1.0f, 0.0f, 1.0f, 
		0.0f, 1.0f, 0.0f, 1.0f, 
		1.0f, 0.0f, 0.0f, 1.0f, 
		0.0f, 1.0f, 0.0f, 1.0f, 
		0.0f, 0.0f, 0.0f, 1.0f, 
		1.0f, 0.0f, 0.0f, 1.0f, 
	};

	glGenVertexArrays(1, &ScreenVAO);
	glBindVertexArray(ScreenVAO);
	glGenBuffers(1, &ScreenBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, ScreenBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ScreenBuffer);

	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), ScreenPlane, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}
void UninitializePostProcess()
{
	glDeleteBuffers(1, &ScreenBuffer);
	glDeleteVertexArrays(1, &ScreenVAO);
}

void PostProcess(UNIFORM flag)
{
	glViewport(0, 0, ScreenDimensions[0], ScreenDimensions[1]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SetUniform(flag);

	glBindVertexArray(ScreenVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

HEX_END
#endif