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
		glm::vec3 eye = this->root->transform->position;
		glm::vec3 focus = glm::vec3(0.0f, 0.0f, 0.0f);//eye + (this->root->transform->forward);

		glm::mat4 view = glm::mat4(1.0f);
		//view *= glm::translate(glm::vec3(0.5f, 0.5f, 0.5f));
		//view *= glm::scale(glm::vec3(0.5f, 0.5f, 0.5f));
		view *= MainCamera->perspective;

		view *= glm::lookAt(glm::vec3(2.0f, 3.2f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//view *= glm::lookAt(eye, focus, this->root->transform->up);
		//view *= glm::lookAt(eye, focus, glm::vec3(0.0f, 1.0f, 0.0f));
		//view *= glm::scale(0.5f, 0.5f, 0.5f);
		//view *= this->root->transform->space;

		SetUniform(UNIFORM_DIRECTIONAL_LIGHT_VECTOR, glm::value_ptr(this->root->transform->forward));
		SetUniform(UNIFORM_DIRECTIONAL_LIGHT_COLOR, &this->color);
		SetUniform(UNIFORM_WS_TO_LS, glm::value_ptr(view));
	}
	else if (this->mode == LIGHTMODE_POINT)
	{
		glm::vec3 deltaFalloff = this->falloff;// * DeltaTime;

		SetUniform(UNIFORM_ADD_POINT_LIGHT);
		SetUniform(UNIFORM_POINT_LIGHT_POSITION, glm::value_ptr(this->root->transform->translation));
		SetUniform(UNIFORM_POINT_LIGHT_COLOR, &this->color);
		SetUniform(UNIFORM_POINT_LIGHT_FALLOFF, glm::value_ptr(deltaFalloff));
	}
}
void LightNode::unload()
{
}
void LightNode::destroy()
{
}
	
void LightNode::onStart()
{
}
void LightNode::onFrameUpdate()
{
}
void LightNode::onFixedUpdate()
{
}

HEX_END
#endif