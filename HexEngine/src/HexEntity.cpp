#include "..\include\HexMain.h"

#ifdef _HEX_ENTITY_H_
HEX_BEGIN

HexEntity::HexEntity()
{
	this->transform = NULL;
	this->material = NULL;
	this->shape = NULL;
	this->components.resize(8);
}
HexEntity::~HexEntity()
{
	this->components.clear();
}

void HexEntity::start()
{
	for (unsigned i = 0; i < this->components.length(); i++)
	{
		ComponentNode* component = this->components[i];
		if (component != NULL)
		{
			component->onStart();
		}
	}
}
void HexEntity::frameUpdate()
{
	for (unsigned i = 0; i < this->components.length(); i++)
	{
		ComponentNode* component = this->components[i];
		if (component != NULL)
		{
			component->onFrameUpdate();
		}
	}
	if (this->shape != NULL) this->shape->load();
}
void HexEntity::fixedUpdate()
{
	if (this->transform != NULL) this->transform->recalculate();
	for (unsigned i = 0; i < this->components.length(); i++)
	{
		ComponentNode* component = this->components[i];
		if (component != NULL)
		{
			component->onFixedUpdate();
		}
	}
}
void HexEntity::render()
{
	if (this->transform != NULL) this->transform->load();
	if (this->material != NULL) this->material->load();
	for (unsigned i = 0; i < this->components.length(); i++)
	{
		ComponentNode* component = this->components[i];
		if (component != NULL)
		{
			component->load();
		}
	}
	if (this->shape != NULL)
	{
		this->shape->load();
		this->shape->batch();
		this->shape->unload();
	}
	for (unsigned i = 0; i < this->components.length(); i++)
	{
		ComponentNode* component = this->components[i];
		if (component != NULL)
		{
			component->unload();
		}
	}
	if (this->material != NULL) this->material->unload();
	if (this->transform != NULL) this->transform->unload();
}

void HexEntity::setTransform(TransformNode* node)
{
	this->transform = node;
	node->parentTo(this);
}
void HexEntity::setMaterial(MaterialNode* node)
{
	this->material = node;
	node->parentTo(this);
}
void HexEntity::setShape(ShapeNode* node)
{
	this->shape = node;
	node->parentTo(this);
}
void HexEntity::addComponent(ComponentNode* node)
{
	if (this->components.contains(node)) return;
	this->components.add(node);
	node->parentTo(this);
}

HEX_END
#endif