#include "..\include\HexMain.h"

#ifdef _HEX_NODE_H_
HEX_BEGIN

HEX_API void GenEntities(uint size, uint* entities)
{
	for (uint i = 0; i < size; i++)
	{
		HexEntity* entity = new HexEntity;
		Entities.add(entity);
		TransformNode* node = new TransformNode;
		entity->setTransform(node);
		Nodes.add(node);
		uint n = Entities.length();
		entities[i] = n;
	}
}
HEX_API void BindEntity(uint entity)
{
	if (entity == 0 || entity > Entities.length()) return;
	BoundEntity = Entities[entity - 1];
}
HEX_API void TransformEntity(float x, float y, float z, float rx, float ry, float rz)
{
	if (BoundEntity == NULL) return;
	BoundEntity->transform->translate(x, y, z);
	BoundEntity->transform->rotate(rx, ry, rz);
}
HEX_API void ParentEntity(uint parent, uint child)
{
	if (parent == 0 || child == 0) return;
	HexEntity* p = Entities[parent - 1];
	HexEntity* c = Entities[child - 1];
	c->parentTo(p);
}

HEX_API void AddShape(uint mesh)
{
	if (BoundEntity == NULL || mesh == 0) return;
	ShapeNode* node = new ShapeNode;
	node->setMesh(mesh);
	BoundEntity->setShape(node);
	Nodes.add(node);
	Shapes.add(node);
	Renderable.add(BoundEntity);
}
HEX_API void AddMaterial(uint colorMap, uint normalMap, uint specularMap)
{
	if (BoundEntity == NULL) return;
	if (colorMap == 0) return;
	MaterialNode* node = new MaterialNode;
	node->setColorMap(colorMap);
	node->setNormalMap(normalMap);
	node->setSpecularMap(specularMap);
	BoundEntity->setMaterial(node);
	Nodes.add(node);
	Materials.add(node);
}

HEX_API void AddCamera(float fovAngle, float nearZ, float farZ)
{
	CameraNode* node = AddComponent<CameraNode>();
	if (node == NULL) return;
	node->fovAngle = fovAngle;
	node->nearZ = nearZ;
	node->farZ = farZ;
}
HEX_API void AddDirectionalLight(float intensity)
{
	LightNode* node = AddComponent<LightNode>();
	if (node == NULL) return;
	node->mode = LIGHTMODE_DIRECTIONAL;
	node->intensity = intensity;
	node->color.a = intensity;
}
HEX_API void AddPointLight(float intensity)
{
	LightNode* node = AddComponent<LightNode>();
	if (node == NULL) return;
	node->mode = LIGHTMODE_POINT;
	node->intensity = intensity;
	node->color.a = intensity;
}

template <typename T> T* AddComponent()
{
	return 0;
}
template <typename T> T* GetComponent()
{
	return 0;
}

template <> CameraNode* AddComponent<>()
{
	if (BoundEntity == NULL) return NULL;
	CameraNode* node = new CameraNode;
	BoundEntity->addComponent(node);
	Nodes.add(node);
	Cameras.add(node);
	MainCamera = node;
	return node;
}
template <> LightNode* AddComponent<>()
{
	if (BoundEntity == NULL) return NULL;
	LightNode* node = new LightNode;
	BoundEntity->addComponent(node);
	Nodes.add(node);
	Lights.add(node);
	return node;
}
template <> SkyboxNode* AddComponent<>()
{
	if (BoundEntity == NULL) return NULL;
	SkyboxNode* node = new SkyboxNode;
	BoundEntity->addComponent(node);
	Nodes.add(node);
	Renderable.remove(BoundEntity);
	MainSkybox = node;
	return node;
}
template <> FirstPersonNode* AddComponent<>()
{
	if (BoundEntity == NULL) return NULL;
	FirstPersonNode* node = new FirstPersonNode;
	BoundEntity->addComponent(node);
	Nodes.add(node);
	return node;
}
template <> ThirdPersonNode* AddComponent<>()
{
	if (BoundEntity == NULL) return NULL;
	ThirdPersonNode* node = new ThirdPersonNode;
	BoundEntity->addComponent(node);
	Nodes.add(node);
	return node;
}
template <> TurnTableNode* AddComponent<>()
{
	if (BoundEntity == NULL) return NULL;
	TurnTableNode* node = new TurnTableNode;
	BoundEntity->addComponent(node);
	Nodes.add(node);
	return node;
}

template <> CameraNode* GetComponent<>()
{
	if (BoundEntity == 0) return 0;
	for (uint i = 0; i < Cameras.length(); i++)
	{
		CameraNode* node = Cameras[i];
		if (node == 0) continue;
		if (node->root == BoundEntity) return node;
	}
	return 0;
}
template <> LightNode* GetComponent<>()
{
	if (BoundEntity == 0) return 0;
	for (uint i = 0; i < Lights.length(); i++)
	{
		LightNode* node = Lights[i];
		if (node == 0) continue;
		if (node->root == BoundEntity) return node;
	}
	return 0;
}
template <> SkyboxNode* GetComponent<>()
{
	if (BoundEntity == 0) return 0;
	for (uint i = 0; i < Nodes.length(); i++)
	{
		NodeBase* node = Nodes[i];
		if (node == 0) continue;
		if (node->root == BoundEntity && node->type == COMPONENT_SKYBOX) return (SkyboxNode*)node;
	}
	return 0;
}
template <> FirstPersonNode* GetComponent<>()
{
	if (BoundEntity == 0) return 0;
	for (uint i = 0; i < Nodes.length(); i++)
	{
		NodeBase* node = Nodes[i];
		if (node == 0) continue;
		if (node->root == BoundEntity && node->type == COMPONENT_FIRSTPERSON) return (FirstPersonNode*)node;
	}
	return 0;
}
template <> ThirdPersonNode* GetComponent<>()
{
	if (BoundEntity == 0) return 0;
	for (uint i = 0; i < Nodes.length(); i++)
	{
		NodeBase* node = Nodes[i];
		if (node == 0) continue;
		if (node->root == BoundEntity && node->type == COMPONENT_THIRDPERSON) return (ThirdPersonNode*)node;
	}
	return 0;
}
template <> TurnTableNode* GetComponent<>()
{
	if (BoundEntity == 0) return 0;
	for (uint i = 0; i < Nodes.length(); i++)
	{
		NodeBase* node = Nodes[i];
		if (node == 0) continue;
		if (node->root == BoundEntity && node->type == COMPONENT_TURNTABLE) return (TurnTableNode*)node;
	}
	return 0;
}

HEX_END
#endif