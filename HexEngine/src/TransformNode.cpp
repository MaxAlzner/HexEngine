#include "..\include\HexMain.h"

#ifdef _TRANSFORMNODE_H_
HEX_BEGIN

HEX_API TransformNode::TransformNode()
{
	this->zero();
}
HEX_API TransformNode::~TransformNode()
{
}
	
HEX_API void TransformNode::load()
{
}
HEX_API void TransformNode::destroy()
{
}

HEX_API void TransformNode::translate(float x, float y, float z)
{
	if (x == 0.0f && y == 0.0f && z == 0.0f) return;
	
	this->translation.x += x;
	this->translation.y += y;
	this->translation.z += z;
}
HEX_API void TransformNode::rotate(float x, float y, float z)
{
	if (x == 0.0f && y == 0.0f && z == 0.0f) return;

	this->rotation.x += x;
	this->rotation.y += y;
	this->rotation.z += z;

	glm::mod(this->rotation, 360.0f);
}
HEX_API void TransformNode::scale(float x, float y, float z)
{
	if (x == 1.0f && y == 1.0f && z == 1.0f) return;
	
	this->scaled.x *= x;
	this->scaled.y *= y;
	this->scaled.z *= z;
}

HEX_API void TransformNode::zero()
{
	this->translation = glm::vec3(0.0f, 0.0f, 0.0f);
	this->rotation =    glm::vec3(0.0f, 0.0f, 0.0f);
	this->scaled =      glm::vec3(1.0f, 1.0f, 1.0f);
	this->right =       glm::vec3(1.0f, 0.0f, 0.0f);
	this->up =          glm::vec3(0.0f, 1.0f, 0.0f);
	this->forward =     glm::vec3(0.0f, 0.0f, 1.0f);
}

HEX_END
#endif