#include "..\include\HexMain.h"

#ifdef _HEX_DATA_H_
HEX_BEGIN

bool AppRunning = true;
bool Paused = false;
float DeltaTime = 0.0f;
float AspectRatio = 3.0f / 4.0f;
uint ScreenDimensions[2] = {800, 600};
SDL_Surface* ScreenSurface = NULL;
CameraNode* MainCamera = NULL;
	
MALib::ARRAY<MALib::VERTEXBUFFER*> Meshes;
MALib::ARRAY<MALib::SURFACE*> Textures;
MALib::ARRAY<HexEntity*> Entities;
MALib::ARRAY<NodeBase*> Nodes;
HexEntity* BoundEntity = NULL;

HEX_API void InitializeData()
{
	Meshes.resize(8);
	Textures.resize(16);
	Entities.resize(12);
	Nodes.resize(32);

#if 0
	MALib::OBJ_MESH* m = 0;
	MALib::ImportOBJFile("data/skybox.obj", &m);
	MALib::VERTEXBUFFER* v = 0;
	MALib::BakeOBJ(m, &v);
	MALib::ExportVMPFile("data/skybox.vmp", v);
	MALib::FreeOBJMesh(&m);
	MALib::FreeVertexBuffer(&v);
#endif

	MALib::LOG_Message("START ASSET LOADING");

	RegisterVMP("data/capsule.vmp");
	RegisterVMP("data/cube.vmp");
	RegisterVMP("data/plane.vmp");
	RegisterVMP("data/puzzle.vmp");
	RegisterVMP("data/sphere.vmp");
	RegisterVMP("data/torus.vmp");
	RegisterVMP("data/skybox.vmp");

	RegisterBMP("data/tile01_d.bmp");
	RegisterBMP("data/tile01_n.bmp");
	RegisterBMP("data/grass01_d.bmp");
	RegisterBMP("data/grass01_n.bmp");
	RegisterBMP("data/sky.bmp");

	MALib::LOG_Message("END ASSET LOADING");
}
HEX_API void UninitializeData()
{
	for (unsigned i = 0; i < Meshes.length(); i++) MALib::FreeVertexBuffer(&Meshes[i]);
	for (unsigned i = 0; i < Textures.length(); i++) MALib::FreeSurface(&Textures[i]);
	for (unsigned i = 0; i < Entities.length(); i++) delete Entities[i];
	for (unsigned i = 0; i < Nodes.length(); i++) delete Nodes[i];
	Meshes.clear();
	Textures.clear();
	Entities.clear();
	Nodes.clear();
}

HEX_API extern bool IsRunning()
{
	return AppRunning;
}
HEX_API extern bool ToggleRunning()
{
	AppRunning = !AppRunning;
	return AppRunning;
}

HEX_API bool RegisterOBJ(const string filepath)
{
	MALib::OBJ_MESH* mesh = 0;
	if (!MALib::ImportOBJFile(filepath, &mesh))
	{
		MALib::LOG_Message("Could not load OBJ file", filepath);
		return false;
	}
	MALib::VERTEXBUFFER* baked = 0;
	if (!MALib::BakeOBJ(mesh, &baked))
	{
		MALib::LOG_Message("Could not bake OBJ mesh", filepath);
		return false;
	}
	Meshes.add(baked);
	MALib::FreeOBJMesh(&mesh);
	return true;
}
HEX_API bool RegisterVMP(const string filepath)
{
	MALib::VERTEXBUFFER* buffer = 0;
	if (!MALib::ImportVMPFile(filepath, &buffer))
	{
		MALib::LOG_Message("Could not load VMP mesh", filepath);
		return false;
	}
	Meshes.add(buffer);
	return true;
}
HEX_API bool RegisterBMP(const string filepath)
{
	MALib::SURFACE* surface = 0;
	if (!MALib::ImportBMPFile(filepath, &surface))
	{
		MALib::LOG_Message("Could not load BMP image", filepath);
		return false;
	}
	Textures.add(surface);
	return true;
}
HEX_API bool RegisterTGA(const string filepath)
{
	MALib::SURFACE* surface = 0;
	if (!MALib::ImportTGAFile(filepath, &surface))
	{
		MALib::LOG_Message("Could not load TGA image", filepath);
		return false;
	}
	Textures.add(surface);
	return true;
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
	MainCamera = node;
}
HEX_API void AddLight(HEX_LIGHTMODE mode, float intensity, float rx, float ry, float rz)
{
	if (BoundEntity == NULL) return;
	LightNode* node = new LightNode;
	node->mode = mode;
	node->intensity = intensity;
	BoundEntity->transform->rotate(rx, ry, rz);
	BoundEntity->addComponent(node);
	Nodes.add(node);
}
HEX_API void AddController()
{
	if (BoundEntity == NULL) return;
	ControlNode* node = new ControlNode;
	BoundEntity->addComponent(node);
	Nodes.add(node);
}
HEX_API void AddSkybox()
{
	if (BoundEntity == NULL) return;
	SkyboxNode* node = new SkyboxNode;
	BoundEntity->addComponent(node);
	Nodes.add(node);
}

HEX_API void AddShape(MALib::VERTEXBUFFER* mesh)
{
	if (BoundEntity == NULL || mesh == NULL) return;
	ShapeNode* node = new ShapeNode;
	node->build(mesh->buffer, mesh->vertices, mesh->stride, mesh->components);
	BoundEntity->setShape(node);
	Nodes.add(node);
}
HEX_API void AddMaterial(MALib::SURFACE* colorMap, MALib::SURFACE* normalMap)
{
	if (BoundEntity == NULL) return;
	MaterialNode* node = new MaterialNode;
	node->setColorMap(colorMap);
	node->setNormalMap(normalMap);
	BoundEntity->setMaterial(node);
	Nodes.add(node);
}

HEX_END
#endif