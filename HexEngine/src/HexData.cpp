#include "..\include\HexMain.h"

#ifdef _HEX_DATA_H_
HEX_BEGIN

bool AppRunning = true;
bool Paused = false;
float DeltaTime = 0.0f;
float AspectRatio = 3.0f / 4.0f;
MALib::RECT RenderRect(1024, 768);
MALib::RECT ScreenRect(800, 600);
SDL_Surface* RenderSurface = NULL;

MALib::ARRAY<HexEntity*> Cameras;
MALib::ARRAY<HexEntity*> Lights;
MALib::ARRAY<HexEntity*> Skyboxes;
MALib::ARRAY<HexEntity*> Renderable;
CameraNode* MainCamera = NULL;
	
MALib::ARRAY<MALib::VERTEXBUFFER*> Meshes;
MALib::ARRAY<MALib::SURFACE*> Textures;
MALib::ARRAY<HexEntity*> Entities;
MALib::ARRAY<NodeBase*> Nodes;
HexEntity* BoundEntity = NULL;

HEX_API void InitializeData()
{
	//MALib::LOG_Message("START ASSET LOADING");
	
	Cameras.resize(8);
	Lights.resize(8);
	Skyboxes.resize(8);
	Renderable.resize(32);

	Meshes.resize(24);
	Textures.resize(48);
	Entities.resize(32);
	Nodes.resize(128);

	//MALib::LOG_Message("END ASSET LOADING");
}
HEX_API void UninitializeData()
{
	for (unsigned i = 0; i < Nodes.length(); i++) Nodes[i]->destroy();
	for (unsigned i = 0; i < Meshes.length(); i++) MALib::FreeVertexBuffer(&Meshes[i]);
	for (unsigned i = 0; i < Textures.length(); i++) MALib::FreeSurface(&Textures[i]);
	for (unsigned i = 0; i < Entities.length(); i++) delete Entities[i];
	for (unsigned i = 0; i < Nodes.length(); i++) delete Nodes[i];
	Cameras.clear();
	Lights.clear();
	Skyboxes.clear();
	Renderable.clear();
	Meshes.clear();
	Textures.clear();
	Entities.clear();
	Nodes.clear();
}

HEX_API bool IsRunning()
{
	return AppRunning;
}
HEX_API bool ToggleRunning()
{
	AppRunning = !AppRunning;
	return AppRunning;
}

HEX_API void RegisterOBJ(uint* mesh, const string filepath)
{
	if (mesh == NULL) return;
	MALib::OBJ_MESH* obj = 0;
	if (!MALib::ImportOBJFile(filepath, &obj))
	{
		MALib::LOG_Message("Could not load OBJ file", filepath);
		return;
	}
	MALib::VERTEXBUFFER* baked = 0;
	if (!MALib::BakeOBJ(obj, &baked))
	{
		MALib::LOG_Message("Could not bake OBJ mesh", filepath);
		return;
	}
	Meshes.add(baked);
	MALib::FreeOBJMesh(&obj);
	uint n = Meshes.length();
	*mesh = n;
}
HEX_API void RegisterVMP(uint* mesh, const string filepath)
{
	if (mesh == NULL) return;
	MALib::VERTEXBUFFER* buffer = 0;
	if (!MALib::ImportVMPFile(filepath, &buffer))
	{
		MALib::LOG_Message("Could not load VMP mesh", filepath);
		return;
	}
	Meshes.add(buffer);
	uint n = Meshes.length();
	*mesh = n;
}
HEX_API void RegisterBMP(uint* texture, const string filepath)
{
	if (texture == NULL) return;
	MALib::SURFACE* surface = 0;
	if (!MALib::ImportBMPFile(filepath, &surface))
	{
		MALib::LOG_Message("Could not load BMP image", filepath);
		return;
	}
	Textures.add(surface);
	uint n = Textures.length();
	*texture = n;
}
HEX_API void RegisterTGA(uint* texture, const string filepath)
{
	if (texture == NULL) return;
	MALib::SURFACE* surface = 0;
	if (!MALib::ImportTGAFile(filepath, &surface))
	{
		MALib::LOG_Message("Could not load TGA image", filepath);
		return;
	}
	Textures.add(surface);
	uint n = Textures.length();
	*texture = n;
}

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
	if (entity == 0) return;
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

HEX_API void AddCamera(float fovAngle, float aspectRatio, float nearZ, float farZ)
{
	if (BoundEntity == NULL) return;
	CameraNode* node = new CameraNode;
	node->fovAngle = fovAngle;
	node->aspectRatio = aspectRatio;
	node->nearZ = nearZ;
	node->farZ = farZ;
	BoundEntity->addComponent(node);
	Nodes.add(node);
	Cameras.add(BoundEntity);
	MainCamera = node;
}
HEX_API void AddController()
{
	if (BoundEntity == NULL) return;
	ControlNode* node = new ControlNode;
	BoundEntity->addComponent(node);
	Nodes.add(node);
}
HEX_API void AddSkybox(uint skyMesh, uint skyMap)
{
	if (BoundEntity == NULL) return;
	if (skyMesh == 0 || skyMap == 0) return;
	SkyboxNode* node = new SkyboxNode;
	BoundEntity->addComponent(node);
	Nodes.add(node);

	MALib::VERTEXBUFFER* mesh = Meshes[skyMesh - 1];
	MALib::SURFACE* texture = Textures[skyMap - 1];

	ShapeNode* box = new ShapeNode;
	box->build(mesh->buffer, mesh->vertices, mesh->stride, mesh->components);
	BoundEntity->setShape(box);
	Nodes.add(box);

	MaterialNode* mat = new MaterialNode;
	mat->setColorMap(texture);
	BoundEntity->setMaterial(mat);
	Nodes.add(mat);

	Skyboxes.add(BoundEntity);
}

HEX_API void AddDirectionalLight(float intensity, MALib::COLOR& color)
{
	if (BoundEntity == NULL) return;
	LightNode* node = new LightNode;
	node->mode = LIGHTMODE_DIRECTIONAL;
	node->intensity = intensity;
	node->color = color;
	node->color.a = intensity;
	BoundEntity->addComponent(node);
	Nodes.add(node);
	Lights.add(BoundEntity);
}
HEX_API void AddPointLight(float intensity, MALib::COLOR& color, float constantFalloff, float linearFalloff, float quadFalloff)
{
	if (BoundEntity == NULL) return;
	LightNode* node = new LightNode;
	node->mode = LIGHTMODE_POINT;
	node->intensity = intensity;
	node->color = color;
	node->color.a = intensity;
	node->falloff.x = constantFalloff;
	node->falloff.y = linearFalloff;
	node->falloff.z = quadFalloff;
	BoundEntity->addComponent(node);
	Nodes.add(node);
	Lights.add(BoundEntity);
}

HEX_API void AddShape(uint mesh)
{
	if (BoundEntity == NULL || mesh == 0) return;
	ShapeNode* node = new ShapeNode;
	MALib::VERTEXBUFFER* buffer = Meshes[mesh - 1];
	node->build(buffer->buffer, buffer->vertices, buffer->stride, buffer->components);
	BoundEntity->setShape(node);
	Nodes.add(node);
	Renderable.add(BoundEntity);
}
HEX_API void AddMaterial(uint colorMap, uint normalMap, uint specularMap)
{
	if (BoundEntity == NULL) return;
	if (colorMap == 0) return;
	MaterialNode* node = new MaterialNode;
	node->setColorMap(Textures[colorMap - 1]);
	if (normalMap != 0) node->setNormalMap(Textures[normalMap - 1]);
	if (specularMap != 0) node->setSpecularMap(Textures[specularMap - 1]);
	BoundEntity->setMaterial(node);
	Nodes.add(node);
}

HEX_END
#endif