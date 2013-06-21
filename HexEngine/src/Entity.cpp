#include "../MainCore.h"

CORE::Entity::Entity()
{
	this->translation = VECTOR(0, 0, 0);
	this->rotation = VECTOR(0, 0, 0);
	this->scaled = VECTOR(1, 1, 1);
	this->childRotation = VECTOR(0, 0, 0);
	this->parent = NULL;
	this->name = "";
	this->hidden = false;
	this->scene = NULL;
	this->mesh = NULL;
	this->physics = NULL;
	this->material = NULL;
}
CORE::Entity::~Entity()
{
}

void CORE::Entity::initialize()
{
	if (this->mesh != NULL) this->mesh->initialize();
	if (this->material != NULL) this->material->initialize();
}
void CORE::Entity::uninitialize()
{
	if (this->mesh != NULL) this->mesh->uninitialize();
	if (this->material != NULL) this->material->uninitialize();
	this->remove();
}
void CORE::Entity::update()
{
	if (this->physics != NULL) this->physics->move();
}
void CORE::Entity::remove()
{
	if (this->mesh != NULL) 
		this->mesh->remove();
	if (this->material != NULL) 
		this->material->remove();
	if (this->scene != NULL) 
		this->scene->remove(this);
	DataCore::RemoveEntity(this);
}

void CORE::Entity::translate(float x, float y, float z)
{
	if (x == 0.0f && y == 0.0f && z == 0.0f) return;
	
	this->translation.x += x;
	this->translation.y += y;
	this->translation.z += z;
}
void CORE::Entity::rotate(float x, float y, float z)
{
	if (x == 0.0f && y == 0.0f && z == 0.0f) return;

	this->rotation.x += x;
	this->rotation.y += y;
	this->rotation.z += z;

	Module(this->rotation, PI * 2.0f);
}
void CORE::Entity::scale(float x, float y, float z)
{
	if (x == 1.0f && y == 1.0f && z == 1.0f) return;
	
	this->scaled.x *= x;
	this->scaled.y *= y;
	this->scaled.z *= z;
}
void CORE::Entity::rotateChildren(float x, float y, float z)
{
	if (x == 0.0f && y == 0.0f && z == 0.0f) return;

	this->childRotation.x += x;
	this->childRotation.y += y;
	this->childRotation.z += z;

	Module(this->childRotation, PI * 2.0f);
}
void CORE::Entity::translate(VECTOR &v)
{
	this->translate(v.x, v.y, v.z);
}
void CORE::Entity::rotate(VECTOR &v)
{
	this->rotate(v.x, v.y, v.z);
}
void CORE::Entity::scale(VECTOR &v)
{
	this->scale(v.x, v.y, v.z);
}
void CORE::Entity::rotateChildren(VECTOR &v)
{
	this->rotateChildren(v.x, v.y, v.z);
}

void CORE::Entity::parentTo(Entity* parent)
{
	if (parent == NULL) return;
	this->parent = parent;
	parent->children.push_back(this);
}
void CORE::Entity::removeChild(Entity* child)
{
	for (unsigned i = 0; i < this->children.size(); i++)
	{
		Entity* entity = this->children[i];
		if (entity == child)
		{
			this->children.erase(this->children.begin() + i);
			return;
		}
	}
}

void CORE::Entity::setScene(Scene* scene)
{
	this->scene = scene;
}
void CORE::Entity::setMesh(Mesh* mesh)
{
	this->mesh = mesh;
	if (this->mesh == NULL) return;
	this->mesh->root = this;
}
void CORE::Entity::setPhysics(PhysicsObject* obj)
{
	this->physics = obj;
	if (this->physics == NULL) return;
	this->physics->root = this;
}
void CORE::Entity::setMaterial(Material* material)
{
	this->material = material;
	if (this->material == NULL) return;
	this->material->root = this;
}

void CORE::Entity::onCollisionEvent(Entity* other)
{
}