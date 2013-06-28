#include "..\include\HexMain.h"

#ifdef _LIGHTNODE_H_
HEX_BEGIN

HEX_API LightNode::LightNode()
{
	this->mode = HEX_LIGHTMODE_NONE;
	this->intensity = 1.0f;
	this->color = MALib::COLOR();
}
HEX_API LightNode::~LightNode()
{
}
		
HEX_API void LightNode::load()
{
	if (this->mode == HEX_LIGHTMODE_DIRECTIONAL)
	{
		glm::vec3 light_dir(0.5f, -0.5f, 0.0f);
		light_dir = glm::normalize<float>(light_dir);
		SetUniform(HEX_UNIFORM_DIRECTIONAL_LIGHT, glm::value_ptr(light_dir));
	}
}
HEX_API void LightNode::destroy()
{
}
	
HEX_API void LightNode::onFrameUpdate()
{
}
HEX_API void LightNode::onFixedUpdate()
{
}

HEX_END
#endif