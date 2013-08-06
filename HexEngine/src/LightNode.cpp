#include "..\include\HexMain.h"

#ifdef _LIGHTNODE_H_
HEX_BEGIN

LightNode::LightNode()
{
	this->mode = LIGHTMODE_NONE;
	this->intensity = 1.0f;
	this->color = MALib::COLOR();
	this->falloff = glm::vec3(1.0f);
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
		if (CurrentFlag == UNIFORM_FLAG_SHADOW_RENDER) 
			SetUniform(UNIFORM_WS_TO_CS, glm::value_ptr(this->lightSpace));
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
	if (this->mode == LIGHTMODE_DIRECTIONAL && CurrentFlag == UNIFORM_FLAG_SHADOW_RENDER && MainCamera != NULL) 
SetUniform(UNIFORM_WS_TO_CS, glm::value_ptr(MainCamera->viewSpace));
}
void LightNode::destroy()
{
}
	
void LightNode::onStart()
{
}
void LightNode::onFrameUpdate()
{
	if (MainCamera == NULL) return;
	glm::vec3 eye = this->root->transform->position;
	glm::vec3 focus = glm::vec3(0.0f, 0.0f, 0.0f);//eye + (this->root->transform->forward);

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
		//glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 20.0f) * 
		this->lightSpace;
}
void LightNode::onFixedUpdate()
{
}

HEX_END
#endif