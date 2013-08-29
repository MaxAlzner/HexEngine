#include "../include/HexMain.h"

#ifdef _TURNTABLENODE_H_
HEX_BEGIN

PanNode::PanNode()
{
	this->type = COMPONENT_PAN;
	this->moveSpeed = 0.0f;
	this->range = glm::vec2(-1.0f, 1.0f);
	this->boundsLeft = glm::vec3(0.0f, 0.0f, 0.0f);
	this->boundsRight = glm::vec3(0.0f, 0.0f, 0.0f);
}
PanNode::~PanNode()
{
}
		
void PanNode::load()
{
}
void PanNode::unload()
{
}
void PanNode::destroy()
{
}
	
void PanNode::onStart()
{
	this->boundsLeft = this->root->transform->position + (this->root->transform->right * -abs(this->moveSpeed) * this->range.x);
	this->boundsRight = this->root->transform->position + (this->root->transform->right * abs(this->moveSpeed) * this->range.y);
}
void PanNode::onFrameUpdate()
{
	if (this->moveSpeed < 0.0f)
	{
		float m = (float)(this->boundsLeft - this->root->transform->position).length();
		if (m < 0.001f)
		{
			this->root->transform->setTranslation(this->boundsLeft.x, this->boundsLeft.y, this->boundsLeft.z);
			this->moveSpeed *= -1.0f;
		}
	}
	else
	{
		float m = (float)(this->boundsRight - this->root->transform->position).length();
		if (m < 0.001f)
		{
			this->root->transform->setTranslation(this->boundsRight.x, this->boundsRight.y, this->boundsRight.z);
			this->moveSpeed *= -1.0f;
		}
	}
	glm::vec3 move = this->root->transform->right * this->moveSpeed * DeltaTime;
	this->root->transform->translate(move.x, move.y, move.z);
}
void PanNode::onFixedUpdate()
{
}

HEX_END
#endif