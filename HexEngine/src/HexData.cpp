#include "..\include\HexMain.h"

#ifdef _HEX_DATA_H_
HEX_BEGIN

HEX_API bool AppRunning = true;
HEX_API bool Paused = false;
HEX_API float AspectRatio = 3.0f / 4.0f;
HEX_API SDL_Surface* ScreenSurface = NULL;
	
HEX_API MALib::ARRAY<MALib::VERTEXBUFFER*> Meshes;
HEX_API MALib::ARRAY<MALib::SURFACE*> Textures;
HEX_API MALib::ARRAY<HexEntity*> Entities;
HEX_API MALib::ARRAY<NodeBase*> Nodes;
HEX_API CameraNode* MainCamera = NULL;

HEX_API void InitializeData()
{
	Meshes.resize(8);
	Textures.resize(16);
	Entities.resize(8);
	Nodes.resize(16);

	MALib::LOG_Message("START ASSET LOADING");

	RegisterVMP("data/capsule.vmp");
	RegisterVMP("data/cube.vmp");
	RegisterVMP("data/plane.vmp");
	RegisterVMP("data/puzzle.vmp");
	RegisterVMP("data/sphere.vmp");
	RegisterVMP("data/torus.vmp");

	RegisterBMP("data/uv_layout.bmp");
	RegisterBMP("data/brick_n.bmp");
	RegisterBMP("data/grass01_d.bmp");
	RegisterBMP("data/grass01_n.bmp");

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

HEX_API HexEntity* GenerateEntity(float x, float y, float z, float rx, float ry, float rz)
{
	HexEntity* entity = new HexEntity;
	Entities.add(entity);
	TransformNode* node = new TransformNode;
	node->translate(x, y, z);
	node->rotate(rx, ry, rz);
	entity->setTransform(node);
	Nodes.add(node);
	return entity;
}
HEX_API CameraNode* GenerateCamera(HexEntity* root, float fovAngle, float aspectRatio, float nearZ, float farZ)
{
	if (root == NULL) return NULL;
	CameraNode* node = new CameraNode;
	node->fovAngle = fovAngle;
	node->aspectRatio = aspectRatio;
	node->nearZ = nearZ;
	node->farZ = farZ;
	root->addComponent(node);
	Nodes.add(node);
	return node;
}
HEX_API LightNode* GenerateLight(HexEntity* root, HEX_LIGHTMODE mode, float intensity, float rx, float ry, float rz)
{
	if (root == NULL) return NULL;
	LightNode* node = new LightNode;
	node->mode = mode;
	node->intensity = intensity;
	root->transform->rotate(rx, ry, rz);
	root->addComponent(node);
	Nodes.add(node);
	return node;
}
HEX_API ShapeNode* GenerateShape(HexEntity* root, MALib::VERTEXBUFFER* mesh)
{
	if (root == NULL || mesh == NULL) return NULL;
	ShapeNode* node = new ShapeNode;
	node->build(mesh->buffer, mesh->vertices, mesh->stride, mesh->components);
	root->setShape(node);
	Nodes.add(node);
	return node;
}
HEX_API MaterialNode* GenerateMaterial(HexEntity* root)
{
	if (root == NULL) return NULL;
	MaterialNode* node = new MaterialNode;
	root->setMaterial(node);
	Nodes.add(node);
	return node;
}

HEX_END
#endif