#include "../include/HexMain.h"

#ifdef _TURNTABLENODE_H_
HEX_BEGIN

TurnTableNode::TurnTableNode()
{
	this->type = COMPONENT_TURNTABLE;
	this->turnSpeed = 0.0f;
}
TurnTableNode::~TurnTableNode()
{
}
		
void TurnTableNode::load()
{
}
void TurnTableNode::unload()
{
}
void TurnTableNode::destroy()
{
}
	
void TurnTableNode::onStart()
{
}
void TurnTableNode::onFrameUpdate()
{
	this->root->transform->rotate(0.0f, this->turnSpeed * DeltaTime, 0.0f);
}
void TurnTableNode::onFixedUpdate()
{
}

HEX_END
#endif