#include "..\include\HexMain.h"

#ifdef _HEX_ENTITY_H_
HEX_BEGIN

HEX_API HexEntity::HexEntity()
{
	this->transform = NULL;
	this->material = NULL;
	this->shape = NULL;
	this->components.resize(8);
}
HEX_API HexEntity::~HexEntity()
{
	this->components.clear();
}

HEX_API void HexEntity::frameUpdate()
{
	if (this->transform != NULL) this->transform->load();
	if (this->material != NULL) this->material->load();
	for (unsigned i = 0; i < this->components.length(); i++)
	{
		ComponentNode* component = this->components[i];
		if (component != NULL)
		{
			component->load();
			component->onFrameUpdate();
		}
	}
	if (this->shape != NULL) this->shape->load();
}
HEX_API void HexEntity::fixedUpdate()
{
	for (unsigned i = 0; i < this->components.length(); i++)
	{
		ComponentNode* component = this->components[i];
		if (component != NULL)
		{
			component->onFixedUpdate();
		}
	}
}
HEX_API void HexEntity::render()
{
	if (this->shape != NULL) this->shape->batch();
}

HEX_API void HexEntity::setTransform(TransformNode* node)
{
	this->transform = node;
	node->parentTo(this);
}
HEX_API void HexEntity::setMaterial(MaterialNode* node)
{
	this->material = node;
	node->parentTo(this);
}
HEX_API void HexEntity::setShape(ShapeNode* node)
{
	this->shape = node;
	node->parentTo(this);
}
HEX_API void HexEntity::addComponent(ComponentNode* node)
{
	if (this->components.contains(node)) return;
	this->components.add(node);
	node->parentTo(this);
}

HEX_END
#endif