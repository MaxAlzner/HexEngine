#ifndef _HEX_DATA_H_
#define _HEX_DATA_H_
HEX_BEGIN

HEX_API extern bool AppRunning;
HEX_API extern bool Paused;
HEX_API extern float AspectRatio;
HEX_API extern SDL_Surface* ScreenSurface;
	
HEX_API extern MALib::ARRAY<MALib::VERTEXBUFFER*> Meshes;
HEX_API extern MALib::ARRAY<MALib::SURFACE*> Textures;
HEX_API extern MALib::ARRAY<HexEntity*> Entities;
HEX_API extern MALib::ARRAY<NodeBase*> Nodes;
HEX_API extern CameraNode* MainCamera;

HEX_API extern void InitializeData();
HEX_API extern void UninitializeData();

HEX_API extern bool IsRunning();
HEX_API extern bool ToggleRunning();

HEX_API extern bool RegisterOBJ(const string filepath);
HEX_API extern bool RegisterVMP(const string filepath);
HEX_API extern bool RegisterBMP(const string filepath);
HEX_API extern bool RegisterTGA(const string filepath);

HEX_API extern HexEntity*      GenerateEntity(float x, float y, float z, float rx, float ry, float rz);
HEX_API extern CameraNode*     GenerateCamera(HexEntity* root, float fovAngle, float aspectRatio, float nearZ, float farZ);
HEX_API extern LightNode*      GenerateLight(HexEntity* root, HEX_LIGHTMODE mode, float intensity, float rx, float ry, float rz);
HEX_API extern ShapeNode*      GenerateShape(HexEntity* root, MALib::VERTEXBUFFER* mesh);
HEX_API extern MaterialNode*   GenerateMaterial(HexEntity* root);
	
HEX_END
#endif