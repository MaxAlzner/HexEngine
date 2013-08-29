#include "../include/HexMain.h"

#ifdef _TURNTABLENODE_H_
HEX_BEGIN

ZoomNode::ZoomNode()
{
	this->type = COMPONENT_ZOOM;
	this->moveSpeed = 0.0f;
}
ZoomNode::~ZoomNode()
{
}
		
void ZoomNode::load()
{
}
void ZoomNode::unload()
{
}
void ZoomNode::destroy()
{
}
	
void ZoomNode::onStart()
{
}
void ZoomNode::onFrameUpdate()
{
	glm::vec3 move = this->root->transform->forward * this->moveSpeed * DeltaTime;
	this->root->transform->translate(move.x, move.y, move.z);
}
void ZoomNode::onFixedUpdate()
{
}

HEX_END
#endif