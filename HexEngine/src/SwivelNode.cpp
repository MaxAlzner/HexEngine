#include "../include/HexMain.h"

#ifdef _TURNTABLENODE_H_
HEX_BEGIN

SwivelNode::SwivelNode()
{
	this->type = COMPONENT_SWIVEL;
	this->turnSpeed = 0.0f;
	this->range = glm::vec2(30.0f, 30.0f);
}
SwivelNode::~SwivelNode()
{
}
		
void SwivelNode::load()
{
}
void SwivelNode::unload()
{
}
void SwivelNode::destroy()
{
}
	
void SwivelNode::onStart()
{
}
void SwivelNode::onFrameUpdate()
{
	this->root->transform->rotate(0.0f, this->turnSpeed * DeltaTime, 0.0f);
}
void SwivelNode::onFixedUpdate()
{
}

HEX_END
#endif