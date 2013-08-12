#include "..\include\HexMain.h"

#ifdef _HEX_ENTITY_H_
HEX_BEGIN

HexEntity::HexEntity()
{
	this->transform = NULL;
	this->material = NULL;
	this->shape = NULL;
	this->components.resize(8);
	this->parent = NULL;
	this->children.resize(8);
	this->isStatic = false;
}
HexEntity::~HexEntity()
{
	this->components.clear();
	this->children.clear();
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
	if (this->transform != NULL) this->transform->recalculate();
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
	//if (this->shape != NULL) this->shape->load();
}
void HexEntity::fixedUpdate()
{
	if (this->transform != NULL && !this->isStatic) this->transform->recalculate();
	for (unsigned i = 0; i < this->components.length(); i++)
	{
		ComponentNode* component = this->components[i];
		if (component != NULL)
		{
			component->onFixedUpdate();
		}
	}
}

void HexEntity::load()
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
	if (this->shape != NULL) this->shape->load();
}
void HexEntity::unload()
{
	if (this->shape != NULL) this->shape->unload();
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
void HexEntity::render()
{
	this->load();
	if (this->shape != NULL) this->shape->batch();
	this->unload();
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

template <typename T> T* HexEntity::getComponent()
{
}

void HexEntity::parentTo(HexEntity* entity)
{
	if (entity == NULL) return;
	if (this == entity) return;
	this->parent = entity;
	entity->children.add(this);
}

HEX_END
#endif