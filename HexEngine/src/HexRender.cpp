#include "..\include\HexMain.h"

#ifdef _HEX_RENDER_H_
HEX_BEGIN

HexRender::HexRender()
{
	this->dimensions = MALib::RECT(0, 0, 0, 0);
	this->view = MALib::RECT(0, 0, 0, 0);
	this->framebuffer = 0;
	this->colorMap = 0;
	this->depthMap = 0;
	this->clear = MALib::COLOR(1.0f, 1.0f, 1.0f, 1.0f);
}
HexRender::~HexRender()
{
}

void HexRender::build(uint width, uint height, bool attachColor, bool attachDepth)
{
	this->dimensions = MALib::RECT(width, height);
	this->view = MALib::RECT(RenderRect.width, RenderRect.height);

	if (this->colorMap != 0) glDeleteTextures(1, &this->colorMap);
	if (this->depthMap != 0) glDeleteTextures(1, &this->depthMap);
	if (this->framebuffer != 0) glDeleteFramebuffers(1, &this->framebuffer);

	glGenFramebuffers(1, &this->framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer);

	if (attachColor)
	{
		glGenTextures(1, &this->colorMap);
		glBindTexture(GL_TEXTURE_2D, this->colorMap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->dimensions.width, this->dimensions.height, 0, GL_RGBA, GL_UNSIGNED_INT, NULL);
		glGenerateMipmap(GL_TEXTURE_2D);
		
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->colorMap, 0);
	}
	if (attachDepth)
	{
		glGenTextures(1, &this->depthMap);
		glBindTexture(GL_TEXTURE_2D, this->depthMap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
		//glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE);
		//glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, this->dimensions.width, this->dimensions.height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, this->dimensions.width, this->dimensions.height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->depthMap, 0);
	}

	if (!attachColor)
	{
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
	}

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) MALib::LOG_Message("Framebuffer Failed");
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void HexRender::load()
{
	glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer);
	//glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->framebuffer);
	glViewport(this->dimensions.x0, this->dimensions.y0, this->dimensions.width, this->dimensions.height);
	glClearColor(this->clear.r, this->clear.g, this->clear.b, this->clear.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void HexRender::unload()
{
	glViewport(ScreenRect.x0, ScreenRect.y0, ScreenRect.width, ScreenRect.height);
	//glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void HexRender::destroy()
{
	glDeleteTextures(1, &this->colorMap);
	glDeleteTextures(1, &this->depthMap);
	glDeleteFramebuffers(1, &this->framebuffer);
}

void HexRender::blit(HexRender* dest)
{
	if (this == dest) return;
#if 0
	uint draw = 0;
	uint drawX0 = ScreenRect.x0;
	uint drawY0 = ScreenRect.y0;
	uint drawX1 = ScreenRect.x1;
	uint drawY1 = ScreenRect.y1;
	if (dest != NULL)
	{
		draw = dest->framebuffer;
		drawX0 = dest->dimensions.x0;
		drawY0 = dest->dimensions.y0;
		drawX1 = dest->dimensions.x1;
		drawY1 = dest->dimensions.y1;
	}
	uint read = this->framebuffer;
	uint readX0 = this->dimensions.x0;
	uint readY0 = this->dimensions.y0;
	uint readX1 = this->dimensions.x1;
	uint readY1 = this->dimensions.y1;
	if (drawX1 < this->dimensions.x1) drawX1 = readX1;
	if (drawY1 < this->dimensions.y1) drawY1 = readY1;
	glBindFramebuffer(GL_READ_FRAMEBUFFER, read);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, draw);
	if (this->colorMap != 0) glBlitFramebuffer(drawX0, drawY0, drawX1, drawY1, drawX0, drawY0, drawX1, drawY1, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	if (this->depthMap != 0) glBlitFramebuffer(drawX0, drawY0, drawX1, drawY1, drawX0, drawY0, drawX1, drawY1, GL_DEPTH_BUFFER_BIT, GL_LINEAR);
#else
	glBindFramebuffer(GL_READ_FRAMEBUFFER, this->framebuffer);

	if (dest == NULL)
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		if (this->colorMap != 0) 
			glBlitFramebuffer(0, 0, this->dimensions.width, this->dimensions.height, 0, 0, ScreenRect.width, ScreenRect.height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
		if (this->depthMap != 0) 
			glBlitFramebuffer(0, 0, this->dimensions.width, this->dimensions.height, 0, 0, ScreenRect.width, ScreenRect.height, GL_DEPTH_BUFFER_BIT, GL_LINEAR);	
	}
	else
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, dest->framebuffer);
		if (this->colorMap != 0) 
			//glBlitFramebuffer(0, 0, this->dimensions.width, this->dimensions.height, 0, 0, dest->dimensions.width, dest->dimensions.height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
			glBlitFramebuffer(0, 0, dest->dimensions.width, dest->dimensions.height, 0, 0, ScreenRect.width, ScreenRect.height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
		if (this->depthMap != 0) 
			glBlitFramebuffer(0, 0, dest->dimensions.width, dest->dimensions.height, 0, 0, ScreenRect.width, ScreenRect.height, GL_DEPTH_BUFFER_BIT, GL_LINEAR);
	}
#endif

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
	//glViewport(0, 0, ScreenRect.width, ScreenRect.height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SetUniform(flag);

	glBindVertexArray(ScreenVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

HEX_END
#endif