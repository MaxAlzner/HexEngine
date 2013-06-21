#ifndef _ENTITY_H_
#define _ENTITY_H_

typedef void (*ONCOLLISION)(Entity* entity, Entity* other);

class Entity
{
public:
	Entity();
	~Entity();

	virtual void initialize();
	virtual void uninitialize();
	virtual void update();
	virtual void remove();

	void translate(float x, float y, float z);
	void rotate(float x, float y, float z);
	void scale(float x, float y, float z);
	void rotateChildren(float x, float y, float z);
	void translate(VECTOR &v);
	void rotate(VECTOR &v);
	void scale(VECTOR &v);
	void rotateChildren(VECTOR &v);
		
	void parentTo(Entity* parent);
	void removeChild(Entity* child);

	void setScene(Scene* scene);
	void setMesh(Mesh* mesh);
	void setPhysics(PhysicsObject* obj);
	void setMaterial(Material* material);
		
	VECTOR translation, rotation, scaled, childRotation;
	vector<Entity*> children;
	Entity* parent;
	string name;
	bool hidden;

	Scene* scene;
	Mesh* mesh;
	Material* material;

	virtual void onCollisionEvent(Entity* other);
};

#endif