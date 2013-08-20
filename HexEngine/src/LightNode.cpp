#include "..\include\HexMain.h"

#ifdef _LIGHTNODE_H_
HEX_BEGIN

LightNode::LightNode()
{
	this->mode = LIGHTMODE_NONE;
	this->intensity = 1.0f;
	this->color = MALib::COLOR();
	this->falloff = glm::vec3(1.0f);
	this->framebuffer = 0;
	this->shadowMap = 0;
}
LightNode::~LightNode()
{
}
		
void LightNode::load()
{
	if (this->mode == LIGHTMODE_DIRECTIONAL)
	{
		SetUniform(UNIFORM_DIRECTIONAL_LIGHT_VECTOR, glm::value_ptr(this->root->transform->forward));
		SetUniform(UNIFORM_DIRECTIONAL_LIGHT_COLOR, &this->color);
		SetUniform(UNIFORM_WS_TO_LS, glm::value_ptr(this->lightPerspective));

		if (CurrentFlag == UNIFORM_FLAG_SHADOW_RENDER && ShadowCaster == this)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer);
			glViewport(0, 0, ShadowRect.width, ShadowRect.height);
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			SetUniform(UNIFORM_WS_TO_CS, glm::value_ptr(this->lightSpace));
		}
	}
	else if (this->mode == LIGHTMODE_POINT)
	{
		glm::vec3 deltaFalloff = this->falloff;// + (this->falloff * DeltaTime);

		SetUniform(UNIFORM_ADD_POINT_LIGHT);
		SetUniform(UNIFORM_POINT_LIGHT_POSITION, glm::value_ptr(this->root->transform->translation));
		SetUniform(UNIFORM_POINT_LIGHT_COLOR, &this->color);
		SetUniform(UNIFORM_POINT_LIGHT_FALLOFF, glm::value_ptr(deltaFalloff));
	}
}
void LightNode::unload()
{
	if (this->mode == LIGHTMODE_DIRECTIONAL)
	{
		if (CurrentFlag == UNIFORM_FLAG_SHADOW_RENDER && ShadowCaster == this && MainCamera != NULL)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			SetUniform(UNIFORM_WS_TO_CS, glm::value_ptr(MainCamera->viewSpace));
		}
	}
}
void LightNode::destroy()
{
	if (this->shadowMap != 0) glDeleteTextures(1, &this->shadowMap);
	if (this->framebuffer != 0) glDeleteFramebuffers(1, &this->framebuffer);
}
	
void LightNode::onStart()
{
	if (this->mode == LIGHTMODE_DIRECTIONAL)
	{
		if (this->shadowMap != 0) glDeleteTextures(1, &this->shadowMap);
		if (this->framebuffer != 0) glDeleteFramebuffers(1, &this->framebuffer);

		glGenFramebuffers(1, &this->framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer);

		glGenTextures(1, &this->shadowMap);
		glBindTexture(GL_TEXTURE_2D, this->shadowMap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);

#if 0

		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, ShadowRect.width, ShadowRect.height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->shadowMap, 0);
		
#if 1
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
#else
		uint draw = 0;
		glGenTextures(1, &draw);
		glBindTexture(GL_TEXTURE_2D, draw);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_INT, NULL);
		glGenerateMipmap(GL_TEXTURE_2D);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, draw, 0);
#endif

#else

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, ShadowRect.width, ShadowRect.height, 0, GL_RGBA, GL_UNSIGNED_INT, NULL);
		glGenerateMipmap(GL_TEXTURE_2D);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->shadowMap, 0);

#endif

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) MALib::LOG_Message("Shadow Map framebuffer Failed");

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		ShadowCaster = this;
	}
}
void LightNode::onFrameUpdate()
{
	if (MainCamera == NULL) return;
	glm::vec3 eye = this->root->transform->position + (this->root->transform->forward * -8.0f);
	glm::vec3 focus = glm::vec3(0.0f, 0.0f, 0.0f);
	//focus = eye + (this->root->transform->forward);

	//glm::mat4 view = glm::mat4(1.0f);
	//view *= glm::translate(glm::vec3(0.5f, 0.5f, 0.5f));
	//view *= glm::scale(glm::vec3(0.5f, 0.5f, 0.5f));
	//view *= MainCamera->perspective;

	//view *= glm::lookAt(glm::vec3(2.0f, 3.2f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//view *= glm::lookAt(eye, focus, this->root->transform->up);
	//view *= glm::lookAt(eye, focus, glm::vec3(0.0f, 1.0f, 0.0f));
	//view *= glm::translate(glm::vec3(0.0f, 0.0f, -1.0f));
	//view *= glm::mat4(this->root->transform->space);

	/*view = 
		glm::translate(glm::vec3(0.5f, 0.5f, 0.5f)) * 
		glm::scale(glm::vec3(0.5f, 0.5f, 0.5f)) * 
		glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 20.0f) * 
		glm::lookAt(eye, focus, glm::vec3(0.0f, 1.0f, 0.0f));*/
	//	glm::lookAt(this->root->transform->forward * -10.0f, focus, glm::vec3(0.0f, 1.0f, 0.0f));

	this->lightSpace = glm::lookAt(eye, focus, glm::vec3(0.0f, 1.0f, 0.0f));
	//this->lightSpace = glm::lookAt(this->root->transform->forward * -10.0f, focus, glm::vec3(0.0f, 1.0f, 0.0f));
	//this->lightSpace = glm::lookAt(glm::vec3(2.0f, 3.2f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//this->lightSpace = this->root->transform->space;

	this->lightPerspective = 
		glm::translate(glm::vec3(0.5f, 0.5f, 0.5f)) * 
		glm::scale(glm::vec3(0.5f, 0.5f, 0.5f)) * 
		MainCamera->perspective * 
		this->lightSpace;
}
void LightNode::onFixedUpdate()
{
}

HEX_END
#endif