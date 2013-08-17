#include "..\include\HexMain.h"

#ifdef _HEX_DATA_H_
HEX_BEGIN

bool AppRunning = true;
bool Paused = false;
bool EnableShadow = false;
bool EnableLuminance = true;
bool EnableAmbientOcclusion = false;
float DeltaTime = 0.0f;
float AspectRatio = 4.0f / 3.0f;
float Gamma = 2.2f;
float AOFilterRadius = 6.4f;
float EyeBridgeWidth = 8.0f;
uint RandomFilterSize = 36;
uint MaxPointLights = 4;
MALib::RECT RenderRect(1280, 720);
MALib::RECT ScreenRect(1280, 720);
MALib::RECT LuminanceRect(128, 128);
MALib::RECT ShadowRect(1024, 1024);
SDL_Surface* RenderSurface = NULL;

MALib::ARRAY<HexEntity*> Renderable;
MALib::ARRAY<HexEntity*> Casters;
MALib::ARRAY<ShapeNode*> Shapes;
MALib::ARRAY<MaterialNode*> Materials;
MALib::ARRAY<CameraNode*> Cameras;
MALib::ARRAY<LightNode*> Lights;
MALib::ARRAY<SkyboxNode*> Skyboxes;
MALib::ARRAY<ControlNode*> Controllers;
CameraNode* MainCamera = NULL;
	
MALib::ARRAY<Scene*> Scenes;
MALib::ARRAY<MALib::VERTEXBUFFER*> Meshes;
MALib::ARRAY<MALib::SURFACE*> Textures;
MALib::ARRAY<HexEntity*> Entities;
MALib::ARRAY<NodeBase*> Nodes;
HexEntity* BoundEntity = NULL;

HEX_API void InitializeData()
{
	UninitializeData();

	Casters.resize(32);
	Renderable.resize(32);
	Shapes.resize(32);
	Materials.resize(32);
	Cameras.resize(8);
	Lights.resize(8);
	Skyboxes.resize(8);
	Controllers.resize(8);

	Scenes.resize(8);
	Meshes.resize(24);
	Textures.resize(48);
	Entities.resize(32);
	Nodes.resize(128);
}
HEX_API void UninitializeData()
{
	ClearData();

	Casters.clear();
	Renderable.clear();
	Shapes.clear();
	Materials.clear();
	Cameras.clear();
	Lights.clear();
	Skyboxes.clear();
	Controllers.clear();

	Scenes.clear();
	Meshes.clear();
	Textures.clear();
	Entities.clear();
	Nodes.clear();
}
HEX_API void ClearData()
{
	for (unsigned i = 0; i < Nodes.length(); i++) Nodes[i]->destroy();
	for (unsigned i = 0; i < Scenes.length(); i++) delete Scenes[i];
	for (unsigned i = 0; i < Meshes.length(); i++) MALib::FreeVertexBuffer(&Meshes[i]);
	for (unsigned i = 0; i < Textures.length(); i++) MALib::FreeSurface(&Textures[i]);
	for (unsigned i = 0; i < Entities.length(); i++) delete Entities[i];
	for (unsigned i = 0; i < Nodes.length(); i++) delete Nodes[i];

	Casters.zero();
	Renderable.zero();
	Shapes.zero();
	Materials.zero();
	Cameras.zero();
	Lights.zero();
	Skyboxes.zero();
	Controllers.zero();

	Scenes.zero();
	Meshes.zero();
	Textures.zero();
	Entities.zero();
	Nodes.zero();
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

HEX_API MALib::VERTEXBUFFER* GetMesh(uint mesh)
{
	if (mesh == 0 || mesh > Meshes.length()) return 0;
	return Meshes[mesh - 1];
}
HEX_API MALib::SURFACE* GetTexture(uint texture)
{
	if (texture == 0 || texture > Textures.length()) return 0;
	return Textures[texture - 1];
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
	Cameras.add(node);
	MainCamera = node;
}
HEX_API void AddController(float lookSensitivity, float moveSpeed)
{
	if (BoundEntity == NULL) return;
	ControlNode* node = new ControlNode;
	node->sensitivity = glm::vec2(lookSensitivity);
	node->moveSpeed = glm::vec2(moveSpeed);
	BoundEntity->addComponent(node);
	Nodes.add(node);
	Controllers.add(node);
}
HEX_API void AddSkybox(/*uint skyMesh, uint skyMap*/)
{
	if (BoundEntity == NULL) return;
	//if (skyMesh == 0 || skyMap == 0) return;
	SkyboxNode* node = new SkyboxNode;
	BoundEntity->addComponent(node);
	Nodes.add(node);
	/*
	ShapeNode* box = new ShapeNode;
	box->setMesh(skyMesh);
	BoundEntity->setShape(box);
	Nodes.add(box);
	Shapes.add(box);

	MaterialNode* mat = new MaterialNode;
	mat->setColorMap(skyMap);
	BoundEntity->setMaterial(mat);
	Nodes.add(mat);
	Materials.add(mat);
	*/
	Skyboxes.add(node);
}
HEX_API void AddTurnTable(float turnSpeed)
{
	if (BoundEntity == NULL) return;
	TurnTableNode* node = new TurnTableNode;
	node->turnSpeed = turnSpeed;
	BoundEntity->addComponent(node);
	Nodes.add(node);
}

HEX_API void AddDirectionalLight(float intensity)
{
	if (BoundEntity == NULL) return;
	LightNode* node = new LightNode;
	node->mode = LIGHTMODE_DIRECTIONAL;
	node->intensity = intensity;
	node->color.a = intensity;
	BoundEntity->addComponent(node);
	Nodes.add(node);
	Lights.add(node);
}
HEX_API void AddPointLight(float intensity)
{
	if (BoundEntity == NULL) return;
	LightNode* node = new LightNode;
	node->mode = LIGHTMODE_POINT;
	node->intensity = intensity;
	node->color.a = intensity;
	BoundEntity->addComponent(node);
	Nodes.add(node);
	Lights.add(node);
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

FILETYPE GetFiletype(const string filepath)
{
	if (filepath == 0) return FILETYPE_NONE;
	size_t l = strlen(filepath);

	if (l > 4)
	{
		if      (filepath[l - 3] == 'o' && filepath[l - 2] == 'b' && filepath[l - 1] == 'j') return FILETYPE_OBJ;
		else if (filepath[l - 3] == 'v' && filepath[l - 2] == 'm' && filepath[l - 1] == 'p') return FILETYPE_VMP;
		else if (filepath[l - 3] == 'b' && filepath[l - 2] == 'm' && filepath[l - 1] == 'p') return FILETYPE_BMP;
		else if (filepath[l - 3] == 't' && filepath[l - 2] == 'g' && filepath[l - 1] == 'a') return FILETYPE_TGA;
	}
	if (l > 6)
	{
		if (filepath[l - 5] == 's' && filepath[l - 4] == 'c' && filepath[l - 3] == 'e' && filepath[l - 2] == 'n' && filepath[l - 1] == 'e') return FILETYPE_SCENE;
	}
	return FILETYPE_NONE;
}

template <typename T> T* GetComponent()
{
	return 0;
}

template <> CameraNode* GetComponent<>()
{
	if (BoundEntity == 0) return 0;
	HexEntity* entity = BoundEntity;
	for (uint i = 0; i < Cameras.length(); i++)
	{
		CameraNode* node = Cameras[i];
		if (node == 0) continue;
		if (node->root == entity) return node;
	}
	return 0;
}
template <> LightNode* GetComponent<>()
{
	if (BoundEntity == 0) return 0;
	HexEntity* entity = BoundEntity;
	for (uint i = 0; i < Lights.length(); i++)
	{
		LightNode* node = Lights[i];
		if (node == 0) continue;
		if (node->root == entity) return node;
	}
	return 0;
}
template <> SkyboxNode* GetComponent<>()
{
	if (BoundEntity == 0) return 0;
	HexEntity* entity = BoundEntity;
	for (uint i = 0; i < Skyboxes.length(); i++)
	{
		SkyboxNode* node = Skyboxes[i];
		if (node == 0) continue;
		if (node->root == entity) return node;
	}
	return 0;
}
template <> ControlNode* GetComponent<>()
{
	if (BoundEntity == 0) return 0;
	HexEntity* entity = BoundEntity;
	for (uint i = 0; i < Controllers.length(); i++)
	{
		ControlNode* node = Controllers[i];
		if (node == 0) continue;
		if (node->root == entity) return node;
	}
	return 0;
}

HEX_END
#endif