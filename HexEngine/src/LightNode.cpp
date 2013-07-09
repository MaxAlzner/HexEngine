#include "..\include\HexMain.h"

#ifdef _LIGHTNODE_H_
HEX_BEGIN

LightNode::LightNode()
{
	this->mode = HEX_LIGHTMODE_NONE;
	this->intensity = 1.0f;
	this->color = MALib::COLOR();
	this->falloff = MALib::VEC3(1.0f, 1.0f, 1.0f);
}
LightNode::~LightNode()
{
}
		
void LightNode::load()
{
	if (this->mode == HEX_LIGHTMODE_DIRECTIONAL)
	{
		glm::vec3 eye = this->root->transform->translation;
		glm::vec3 focus = eye + (this->root->transform->forward);

		glm::mat4 view = glm::mat4(1.0f);
		view *= glm::translate(glm::vec3(0.5f, 0.5f, 0.5f));
		view *= glm::scale(glm::vec3(0.5f, 0.5f, 0.5f));
		view *= MainCamera->perspective;

		//view *= glm::lookAt(glm::vec3(3.0f, 3.0f, -4.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		view *= glm::lookAt(eye, focus, this->root->transform->up);
		//view *= this->root->transform->transformation;

		SetUniform(UNIFORM_DIRECTIONAL_LIGHT_VECTOR, glm::value_ptr(this->root->transform->forward));
		SetUniform(UNIFORM_DIRECTIONAL_LIGHT_COLOR, &this->color);
		SetUniform(UNIFORM_WS_TO_LS, glm::value_ptr(view));
		//SetUniform(UNIFORM_WS_TO_LS, glm::value_ptr(this->root->transform->space));
	}
	else if (this->mode == HEX_LIGHTMODE_POINT)
	{
		SetUniform(UNIFORM_ADD_POINT_LIGHT);
		SetUniform(UNIFORM_POINT_LIGHT_POSITION, glm::value_ptr(this->root->transform->translation));
		SetUniform(UNIFORM_POINT_LIGHT_COLOR, &this->color);
		SetUniform(UNIFORM_POINT_LIGHT_FALLOFF, &this->falloff);
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