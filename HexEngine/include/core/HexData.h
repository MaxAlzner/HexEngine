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

HEX_API extern void RegisterOBJ(uint* mesh, const string filepath);
HEX_API extern void RegisterVMP(uint* mesh, const string filepath);
HEX_API extern void RegisterBMP(uint* texture, const string filepath);
HEX_API extern void RegisterTGA(uint* texture, const string filepath);

HEX_API extern void GenEntities(uint size, uint* entities);
HEX_API extern void BindEntity(uint entity);
HEX_API extern void TransformEntity(float x, float y, float z, float rx = 0.0f, float ry = 0.0f, float rz = 0.0f);
HEX_API extern void ParentEntity(uint parent, uint child);

HEX_API extern void AddCamera(float fovAngle, float aspectRatio, float nearZ, float farZ);
HEX_API extern void AddController();
HEX_API extern void AddSkybox(uint skyMesh, uint skyMap);

HEX_API extern void AddDirectionalLight(float intensity, MALib::COLOR& color);
HEX_API extern void AddPointLight(float intensity, MALib::COLOR& color, float constantFalloff = 0.0f, float linearFalloff = 0.0f, float quadFalloff = 0.0f);

HEX_API extern void AddShape(uint mesh);
HEX_API extern void AddMaterial(uint colorMap, uint normalMap = 0, uint specularMap = 0);
	
HEX_END
#endif