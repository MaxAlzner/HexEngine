#include "..\include\HexMain.h"

#ifdef _TRANSFORMNODE_H_
HEX_BEGIN

TransformNode::TransformNode()
{
	this->zero();
}
TransformNode::~TransformNode()
{
}
	
void TransformNode::load()
{
}
void TransformNode::unload()
{
}
void TransformNode::destroy()
{
}

void TransformNode::setTranslationX(float v)
{
	this->translation.x = v;
}
void TransformNode::setTranslationY(float v)
{
	this->translation.y = v;
}
void TransformNode::setTranslationZ(float v)
{
	this->translation.z = v;
}
void TransformNode::setRotationX(float v)
{
	this->rotation.x = v;
}
void TransformNode::setRotationY(float v)
{
	this->rotation.y = v;
}
void TransformNode::setRotationZ(float v)
{
	this->rotation.z = v;
}
void TransformNode::setScaleX(float v)
{
	this->scaled.x = v;
}
void TransformNode::setScaleY(float v)
{
	this->scaled.y = v;
}
void TransformNode::setScaleZ(float v)
{
	this->scaled.z = v;
}
void TransformNode::setTranslation(float x, float y, float z)
{
	this->translation.x = x;
	this->translation.y = y;
	this->translation.z = z;
}
void TransformNode::setRotation(float x, float y, float z)
{
	this->rotation.x = x;
	this->rotation.y = y;
	this->rotation.z = z;

	glm::mod(this->rotation, 360.0f);
}
void TransformNode::setScale(float x, float y, float z)
{
	this->scaled.x = x;
	this->scaled.y = y;
	this->scaled.z = z;
}

void TransformNode::translate(float x, float y, float z)
{
	if (x == 0.0f && y == 0.0f && z == 0.0f) return;
	
	this->translation.x += x;
	this->translation.y += y;
	this->translation.z += z;
}
void TransformNode::rotate(float x, float y, float z)
{
	if (x == 0.0f && y == 0.0f && z == 0.0f) return;

	this->rotation.x += x;
	this->rotation.y += y;
	this->rotation.z += z;

	glm::mod(this->rotation, 360.0f);
}
void TransformNode::scale(float x, float y, float z)
{
	if (x == 1.0f && y == 1.0f && z == 1.0f) return;
	
	this->scaled.x *= x;
	this->scaled.y *= y;
	this->scaled.z *= z;
}
void TransformNode::zero()
{
	this->translation = glm::vec3(0.0f, 0.0f, 0.0f);
	this->rotation =    glm::vec3(0.0f, 0.0f, 0.0f);
	this->scaled =      glm::vec3(1.0f, 1.0f, 1.0f);
	this->right =       glm::vec3(1.0f, 0.0f, 0.0f);
	this->up =          glm::vec3(0.0f, 1.0f, 0.0f);
	this->forward =     glm::vec3(0.0f, 0.0f, 1.0f);
	this->space =       glm::mat4(1.0f);
	this->spaceNormal = glm::mat3(1.0f);
}

void TransformNode::recalculate()
{
	this->space = glm::mat4(1.0f);
	if (this->root->parent != NULL)
	{
		this->space *= glm::rotate(this->root->parent->transform->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		this->space *= glm::rotate(this->root->parent->transform->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		this->space *= glm::rotate(this->root->parent->transform->rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	}
	this->space *= glm::rotate(this->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	this->space *= glm::rotate(this->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	this->space *= glm::rotate(this->rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	this->spaceNormal = glm::mat3(this->space);

	this->position = this->translation;
	if (this->root->parent != NULL)
	{
		this->position += this->root->parent->transform->translation;
	}
	
	this->right =   glm::normalize(glm::mul(glm::vec3(1.0f, 0.0f, 0.0f), this->spaceNormal));
	this->up =      glm::normalize(glm::mul(glm::vec3(0.0f, 1.0f, 0.0f), this->spaceNormal));
	this->forward = glm::normalize(glm::mul(glm::vec3(0.0f, 0.0f, 1.0f), this->spaceNormal));

	this->transformation = glm::mat4(1.0f);
	if (this->root->parent != NULL)
	{
		this->transformation *= glm::translate(this->root->parent->transform->translation);
		this->transformation *= glm::rotate(this->root->parent->transform->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		this->transformation *= glm::rotate(this->root->parent->transform->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		this->transformation *= glm::rotate(this->root->parent->transform->rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	}
	this->transformation *= glm::translate(this->translation);
	this->transformation *= glm::rotate(this->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	this->transformation *= glm::rotate(this->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	this->transformation *= glm::rotate(this->rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	this->transformation *= glm::scale(this->scaled);
}

HEX_END
#endif