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
float AOFilterRadius = 24.0f;
float EyeBridgeWidth = 8.0f;
uint RandomFilterSize = 64;
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
LightNode* ShadowCaster = NULL;
CameraNode* MainCamera = NULL;
SkyboxNode* MainSkybox = NULL;
	
MALib::ARRAY<Scene*> Scenes;
MALib::ARRAY<GUI*> ActiveGUI;
MALib::ARRAY<MALib::VERTEXBUFFER*> Meshes;
MALib::ARRAY<MALib::SURFACE*> Textures;
MALib::ARRAY<HexEntity*> Entities;
MALib::ARRAY<NodeBase*> Nodes;
HexEntity* BoundEntity = NULL;

MALib::TEXTFILE* VertexShader = NULL;
MALib::TEXTFILE* FragmentShader = NULL;
string VertexShaderSource = NULL;
string FragmentShaderSource = NULL;

UNIFORM LastFlag = UNIFORM_FLAG_NORMAL;
UNIFORM CurrentFlag = UNIFORM_FLAG_NORMAL;

MALib::ARRAY<int> Attributes;
uint NumOfUniforms = 0;
uint ShaderProgram = 0;

uint ScreenVAO = 0;
uint ScreenBuffer = 0;

uint GUIVAO = 0;
uint GUIBuffer = 0;
uint FontTexture = 0;

HEX_API void InitializeData()
{
	UninitializeData();

	Casters.resize(32);
	Renderable.resize(32);
	Shapes.resize(32);
	Materials.resize(32);
	Cameras.resize(8);
	Lights.resize(8);

	Scenes.resize(8);
	ActiveGUI.resize(24);
	Meshes.resize(24);
	Textures.resize(48);
	Entities.resize(32);
	Nodes.resize(128);
	
	if (!MALib::ImportTextFile(HEX_VERTEXSHADER_FILEPATH, &VertexShader))
	{
		MALib::LOG_Message("Could not find vertex shader file.", HEX_VERTEXSHADER_FILEPATH);
	}
	if (!MALib::ImportTextFile(HEX_FRAGMENTSHADER_FILEPATH, &FragmentShader))
	{
		MALib::LOG_Message("Could not find fragment shader file.", HEX_FRAGMENTSHADER_FILEPATH);
	}
}
HEX_API void UninitializeData()
{
	ClearGame();

	Casters.clear();
	Renderable.clear();
	Shapes.clear();
	Materials.clear();
	Cameras.clear();
	Lights.clear();

	Scenes.clear();
	ActiveGUI.clear();
	Meshes.clear();
	Textures.clear();
	Entities.clear();
	Nodes.clear();
	
	MALib::FreeTextFile(&VertexShader);
	MALib::FreeTextFile(&FragmentShader);
	if (VertexShaderSource != NULL) delete [] VertexShaderSource;
	if (FragmentShaderSource != NULL) delete [] FragmentShaderSource;
}

HEX_API void ClearGame()
{
	for (unsigned i = 0; i < Nodes.length(); i++) Nodes[i]->destroy();
	for (unsigned i = 0; i < ActiveGUI.length(); i++) DestroyGUI(&ActiveGUI[i]);
	for (unsigned i = 0; i < Scenes.length(); i++) DestroyScene(&Scenes[i]);
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

HEX_END
#endif