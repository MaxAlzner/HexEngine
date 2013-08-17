#ifndef _HEX_DATA_H_
#define _HEX_DATA_H_
HEX_BEGIN
	
HEX_API typedef enum FILETYPE
{
	FILETYPE_NONE              = 0x00000000, 

	FILETYPE_OBJ               = 0x00000011, 
	FILETYPE_VMP               = 0x00000012, 
	FILETYPE_BMP               = 0x00000101, 
	FILETYPE_TGA               = 0x00000102, 
	
	FILETYPE_SCENE             = 0x00001001, 
};

extern bool AppRunning;
extern bool Paused;
extern bool EnableShadow;
extern bool EnableLuminance;
extern bool EnableAmbientOcclusion;
extern float DeltaTime;
extern float AspectRatio;
extern float Gamma;
extern float AOFilterRadius;
extern float EyeBridgeWidth;
extern uint RandomFilterSize;
extern uint MaxPointLights;
extern MALib::RECT RenderRect;
extern MALib::RECT ScreenRect;
extern MALib::RECT LuminanceRect;
extern MALib::RECT ShadowRect;
extern SDL_Surface* RenderSurface;

extern MALib::ARRAY<HexEntity*> Renderable;
extern MALib::ARRAY<HexEntity*> Casters;
extern MALib::ARRAY<ShapeNode*> Shapes;
extern MALib::ARRAY<MaterialNode*> Materials;
extern MALib::ARRAY<CameraNode*> Cameras;
extern MALib::ARRAY<LightNode*> Lights;
extern MALib::ARRAY<SkyboxNode*> Skyboxes;
extern MALib::ARRAY<ControlNode*> Controllers;
extern CameraNode* MainCamera;
	
extern MALib::ARRAY<Scene*> Scenes;
extern MALib::ARRAY<MALib::VERTEXBUFFER*> Meshes;
extern MALib::ARRAY<MALib::SURFACE*> Textures;
extern MALib::ARRAY<HexEntity*> Entities;
extern MALib::ARRAY<NodeBase*> Nodes;
extern HexEntity* BoundEntity;

HEX_API extern void InitializeData();
HEX_API extern void UninitializeData();
HEX_API extern void ClearData();

HEX_API extern bool IsRunning();
HEX_API extern bool ToggleRunning();

HEX_API extern void RegisterOBJ(uint* mesh, const string filepath);
HEX_API extern void RegisterVMP(uint* mesh, const string filepath);
HEX_API extern void RegisterBMP(uint* texture, const string filepath);
HEX_API extern void RegisterTGA(uint* texture, const string filepath);

HEX_API extern MALib::VERTEXBUFFER* GetMesh(uint mesh);
HEX_API extern MALib::SURFACE* GetTexture(uint texture);

HEX_API extern void GenEntities(uint size, uint* entities);
HEX_API extern void BindEntity(uint entity);
HEX_API extern void TransformEntity(float x, float y, float z, float rx = 0.0f, float ry = 0.0f, float rz = 0.0f);
HEX_API extern void ParentEntity(uint parent, uint child);

HEX_API extern void AddCamera(float fovAngle, float aspectRatio, float nearZ, float farZ);
HEX_API extern void AddController(float lookSensitivity, float moveSpeed);
HEX_API extern void AddSkybox();
HEX_API extern void AddTurnTable(float turnSpeed);

HEX_API extern void AddDirectionalLight(float intensity);
HEX_API extern void AddPointLight(float intensity);

HEX_API extern void AddShape(uint mesh);
HEX_API extern void AddMaterial(uint color, uint normal = 0, uint specular = 0);

extern FILETYPE GetFiletype(const string filepath);

template <typename T> extern T* GetComponent();

template <> extern CameraNode*  GetComponent<>();
template <> extern LightNode*   GetComponent<>();
template <> extern SkyboxNode*  GetComponent<>();
template <> extern ControlNode* GetComponent<>();
	
HEX_END
#endif