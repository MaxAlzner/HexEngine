#ifndef _HEX_DATA_H_
#define _HEX_DATA_H_
HEX_BEGIN

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
extern LightNode* ShadowCaster;
extern CameraNode* MainCamera;
extern SkyboxNode* MainSkybox;
	
extern MALib::ARRAY<Scene*> Scenes;
extern MALib::ARRAY<GUI*> ActiveGUI;
extern MALib::ARRAY<MALib::VERTEXBUFFER*> Meshes;
extern MALib::ARRAY<MALib::SURFACE*> Textures;
extern MALib::ARRAY<HexEntity*> Entities;
extern MALib::ARRAY<NodeBase*> Nodes;
extern HexEntity* BoundEntity;

extern MALib::TEXTFILE* VertexShader;
extern MALib::TEXTFILE* FragmentShader;
extern string VertexShaderSource;
extern string FragmentShaderSource;

extern UNIFORM LastFlag;
extern UNIFORM CurrentFlag;

extern MALib::ARRAY<int> Attributes;
extern uint NumOfUniforms;
extern uint ShaderProgram;

extern uint ScreenVAO;
extern uint ScreenBuffer;
extern uint GUIVAO;
extern uint GUIBuffer;

HEX_API extern void InitializeData();
HEX_API extern void UninitializeData();

HEX_API extern void ClearGame();

HEX_API extern bool IsRunning();
HEX_API extern bool ToggleRunning();

HEX_API extern void RegisterOBJ(uint* mesh, const string filepath);
HEX_API extern void RegisterVMP(uint* mesh, const string filepath);
HEX_API extern void RegisterBMP(uint* texture, const string filepath);
HEX_API extern void RegisterTGA(uint* texture, const string filepath);

HEX_API extern MALib::VERTEXBUFFER* GetMesh(uint mesh);
HEX_API extern MALib::SURFACE* GetTexture(uint texture);

extern FILETYPE GetFiletype(const string filepath);
	
HEX_END
#endif