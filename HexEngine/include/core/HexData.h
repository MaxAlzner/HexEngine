#ifndef _HEX_DATA_H_
#define _HEX_DATA_H_
HEX_BEGIN

extern bool AppRunning;
extern bool Paused;
extern float DeltaTime;
extern float AspectRatio;
extern MALib::RECT RenderRect;
extern MALib::RECT ScreenRect;
extern SDL_Surface* RenderSurface;

extern MALib::ARRAY<HexEntity*> Cameras;
extern MALib::ARRAY<HexEntity*> Lights;
extern MALib::ARRAY<HexEntity*> Skyboxes;
extern MALib::ARRAY<HexEntity*> Renderable;
extern CameraNode* MainCamera;
	
extern MALib::ARRAY<MALib::VERTEXBUFFER*> Meshes;
extern MALib::ARRAY<MALib::SURFACE*> Textures;
extern MALib::ARRAY<HexEntity*> Entities;
extern MALib::ARRAY<NodeBase*> Nodes;
extern HexEntity* BoundEntity;

HEX_API extern void InitializeData();
HEX_API extern void UninitializeData();

HEX_API extern bool IsRunning();
HEX_API extern bool ToggleRunning();

HEX_API extern bool RegisterOBJ(const string filepath);
HEX_API extern bool RegisterVMP(const string filepath);
HEX_API extern bool RegisterBMP(const string filepath);
HEX_API extern bool RegisterTGA(const string filepath);

HEX_API extern void GenEntities(uint size, uint* entities);
HEX_API extern void BindEntity(uint entity);
HEX_API extern void TransformEntity(float x, float y, float z, float rx = 0.0f, float ry = 0.0f, float rz = 0.0f);
HEX_API extern void ParentEntity(uint parent, uint child);

HEX_API extern void AddCamera(float fovAngle, float aspectRatio, float nearZ, float farZ);
HEX_API extern void AddLight(HEX_LIGHTMODE mode, float intensity, float rx = 0.0f, float ry = 0.0f, float rz = 0.0f);
HEX_API extern void AddController();
HEX_API extern void AddSkybox();

HEX_API extern void AddShape(MALib::VERTEXBUFFER* mesh);
HEX_API extern void AddMaterial(MALib::SURFACE* colorMap, MALib::SURFACE* normalMap = NULL);
	
HEX_END
#endif