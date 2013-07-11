#include "..\include\HexMain.h"

#ifdef _HEX_CORE_H_
HEX_BEGIN

void UpdateDeltaTime()
{
	static uint Ping = 0;
	uint NewPing = SDL_GetTicks();
	if (Ping == 0) Ping = NewPing;
	DeltaTime = float((NewPing - Ping) % 1000) / 1000.0f;
	Ping = NewPing;
}

HexRender MainRender;
HexRender ShadowRender;
HexRender LeftEyeRender;
HexRender RightEyeRender;

HexEntity* torus = 0;
bool toggle = false;

void BuildScene()
{
	uint entities[12];
	uint i = 0;
	GenEntities(9, entities);

	BindEntity(entities[i]);i++;
	AddMaterial(Textures[4]);
	AddSkybox();
	
	BindEntity(entities[i]);i++;
	TransformEntity(0.0f, 1.0f, -4.0f, 0.0f, 0.0f, 0.0f);
	AddController();

	BindEntity(entities[i]);i++;
	TransformEntity(-0.1f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	AddCamera(45.0f, 4.0f / 3.0f, 0.01f, 100.0f);
	ParentEntity(i - 1, i);
	BindEntity(entities[i]);i++;
	TransformEntity(0.1f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	AddCamera(45.0f, 4.0f / 3.0f, 0.01f, 100.0f);
	ParentEntity(i - 2, i);
	
	BindEntity(entities[i]);i++;
	TransformEntity(0.0f, 1.0f, 0.0f, -50.0f, 60.0f, 0.0f);
	AddLight(LIGHTMODE_DIRECTIONAL, 1.0f, 0.0f, 0.0f, 0.0f);
	
	BindEntity(entities[i]);i++;
	TransformEntity(2.0f, 2.0f, -3.0f, 0.0f, 0.0f, 0.0f);
	AddLight(LIGHTMODE_POINT, 1.0f);
	
	BindEntity(entities[i]);i++;
	TransformEntity(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 60.0f);
	AddShape(Meshes[5]);
	AddMaterial(Textures[0], Textures[1]);
	BoundEntity->material->uvRepeat *= MALib::VEC2(8.0f, 4.0f);
	torus = BoundEntity;
	
	BindEntity(entities[i]);i++;
	TransformEntity(0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f);
	AddShape(Meshes[0]);
	AddMaterial(Textures[0], Textures[1]);
	ParentEntity(i - 1, i);
	
	BindEntity(entities[i]);i++;
	TransformEntity(0.0f, 0.0f, 0.0f, -90.0f, 0.0f, 0.0f);
	AddShape(Meshes[2]);
	AddMaterial(Textures[2], Textures[3]);
	BoundEntity->material->uvRepeat *= MALib::VEC2(4.0f, 4.0f);
	BoundEntity->transform->scale(8.0f, 8.0f, 8.0f);
}

HEX_API void OnFrameDraw()
{
	if (Paused) return;
	
	ResetUniforms();
#if 0
	ShadowRender.load();

	SetUniform(UNIFORM_FLAG_SHADOW_RENDER);
	for (unsigned i = 0; i < Lights.length(); i++) Lights[i]->render();
	for (unsigned i = 0; i < Renderable.length(); i++) Renderable[i]->render();

	ShadowRender.unload();
#endif
	float ShadowMapSize = 1024.0f;
	SetTextureSlot(UNIFORM_TEXTURE_SHADOW_MAP, ShadowRender.depthMap);
	SetUniform(UNIFORM_SHADOW_MAP_SIZE, &ShadowMapSize);
#if 0
	MainRender.load();

	SetUniform(UNIFORM_FLAG_NORMAL);
	float ShadowMapSize = 1024.0f;
	SetTextureSlot(UNIFORM_TEXTURE_SHADOW_MAP, ShadowRender.depthMap);
	SetUniform(UNIFORM_SHADOW_MAP_SIZE, &ShadowMapSize);

	uint rendering = Renderable.length();

	for (unsigned i = 0; i < Skyboxes.length(); i++) Skyboxes[i]->render();
	Cameras[0]->render();
	for (unsigned i = 0; i < Lights.length(); i++) Lights[i]->render();
	for (unsigned i = 0; i < Renderable.length(); i++) Renderable[i]->render();

	MainRender.unload();
#endif
	LeftEyeRender.load();

	SetUniform(UNIFORM_FLAG_NORMAL);
	
	Cameras[0]->render();
	//for (unsigned i = 0; i < Skyboxes.length(); i++) Skyboxes[i]->render();
	for (unsigned i = 0; i < Lights.length(); i++) Lights[i]->render();
	for (unsigned i = 0; i < Renderable.length(); i++) Renderable[i]->render();

	LeftEyeRender.unload();
	RightEyeRender.load();

	SetUniform(UNIFORM_FLAG_NORMAL);

	Cameras[1]->render();
	//for (unsigned i = 0; i < Skyboxes.length(); i++) Skyboxes[i]->render();
	for (unsigned i = 0; i < Lights.length(); i++) Lights[i]->render();
	for (unsigned i = 0; i < Renderable.length(); i++) Renderable[i]->render();

	RightEyeRender.unload();
	
	/*if (toggle)
	{*/
		SetTextureSlot(UNIFORM_TEXTURE_LEFT_EYE_MAP, LeftEyeRender.colorMap);
		SetTextureSlot(UNIFORM_TEXTURE_RIGHT_EYE_MAP, RightEyeRender.colorMap);

		float eyeBridge = 8.0f;
		float gamma = 2.2f;
		float leftEye[] = {1.0f, 0.0f, 0.0f, 1.0f};
		float rightEye[] = {0.0f, 1.0f, 1.0f, 1.0f};
		SetUniform(UNIFORM_EYE_BRIDGE, &eyeBridge);
		SetUniform(UNIFORM_GAMMA, &gamma);
		SetUniform(UNIFORM_LEFT_EYE_COLOR, &leftEye);
		SetUniform(UNIFORM_RIGHT_EYE_COLOR, &rightEye);
		
		PostProcess(UNIFORM_FLAG_POSTPROCESS_ANAGLYPHIC_3D);
	/*}
	else
	{
		MainRender.blit();
	}*/

	SDL_GL_SwapBuffers();
}
HEX_API void OnFrameUpdate()
{
	if (Paused) return;
	
	for (unsigned i = 0; i < Entities.length(); i++)
	{
		Entities[i]->frameUpdate();
	}

	UpdateDeltaTime();
}
HEX_API void OnFixedUpdate()
{
	if (Paused) return;
	if (Input::IsKeyDown(KEY_ESCAPE) || Input::IsButtonDown(XBOX_BACK)) ToggleRunning();

	for (unsigned i = 0; i < Entities.length(); i++)
	{
		Entities[i]->fixedUpdate();
	}
	
	torus->transform->rotate(0.0f, 24.0f * DeltaTime, 0.0f);
	if (Input::GetKey(KEY_SPACE, true)) toggle = !toggle;

	PollControllers();
}

HEX_API bool Reshape(uint width, uint height)
{
	ScreenSurface = SDL_SetVideoMode(width, height, 0, SDL_OPENGL | SDL_DOUBLEBUF | SDL_RESIZABLE);
	if (ScreenSurface == NULL) 
		return false;
	
	SDL_Surface* icon = SDL_LoadBMP("data/icon.bmp");
	Uint8 iconKey = SDL_MapRGB(icon->format, 255, 255, 255);
	SDL_SetColorKey(icon, SDL_SRCCOLORKEY, iconKey);
	SDL_WM_SetIcon(icon, 0);
	SDL_FreeSurface(icon);
	
	//glViewport(0, 0, width, height);
	ScreenDimensions[0] = width;
	ScreenDimensions[1] = height;
	OnMouseMove(width / 2, height / 2);

	return true;
}
HEX_API bool Initialize(uint argc, string* argv)
{
	MALib::LOG_Initialize(true);
	MALib::RANDOM_Initialize();

	for (unsigned i = 0; i < argc; i++)
	{
		MALib::LOG_Message(argv[i]);
	}
	MALib::LOG_Message("START INTIALIZING");
	
	MALib::LOG_Message("START SDL");
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		MALib::LOG_Message("Unable to initialize SDL.");
		MALib::LOG_Message(SDL_GetError());
		return false;
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_WM_SetCaption("HexDemo", "HexDemo");
	
	/*MALib::LOG_Message("START TTF");
	if (TTF_Init() < 0)
	{
		MALib::LOG_Message("Unable to initialize SDL_TTF.");
		return false;
	}*/
	
	MALib::LOG_Message("START RESHAPE");
	Reshape(ScreenDimensions[0], ScreenDimensions[1]);
	
	MALib::LOG_Message("START GLEW");
	GLenum glewStatus = glewInit();
	if (!GLEW_VERSION_3_0)
	{
		MALib::LOG_Message("Requires OpenGL 3.0 or later.");
		return false;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
	MALib::LOG_Message("GL VENDOR                  ", (char*)glGetString(GL_VENDOR));
	MALib::LOG_Message("GL RENDERER                ", (char*)glGetString(GL_RENDERER));
	MALib::LOG_Message("GL VERSION                 ", (char*)glGetString(GL_VERSION));
	MALib::LOG_Message("GL SHADING_LANGUAGE_VERSION", (char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
	
	MALib::LOG_Message("START SHADER");
	if (!BuildProgram("data/gl_shader.vert", "data/gl_shader.frag"))
	{
		MALib::LOG_Message("Could not build shaders.");
		return false;
	}
	InitializeAttributes();
	InitializeUniforms();

	MALib::LOG_Outiv("UNIFORMS", (int*)&Uniforms, 19);
	//MALib::LOG_Outiv("ATTRIBUTES", Attributes.pointer(), Attributes.length());
	
	MALib::LOG_Message("START INPUT");
	InitializeInput();
	MALib::LOG_Message("START DATA");
	InitializeData();
	/*MALib::LOG_Message("START FONT");
	InitializeFont();*/
	
	MALib::LOG_Message("START FRAMEBUFFERS");
	InitializePostProcess();
	MainRender.build(ScreenDimensions[0], ScreenDimensions[1], true, true);
	ShadowRender.build(1024, 1024, false, true);
	LeftEyeRender.build(ScreenDimensions[0], ScreenDimensions[1], true, true);
	RightEyeRender.build(ScreenDimensions[0], ScreenDimensions[1], true, true);
	
	MALib::LOG_Message("START SCENE");
	BuildScene();
	
	MALib::LOG_Message("END INITIALIZATION");
	return true;
}
HEX_API bool Unitialize()
{
	UninitializePostProcess();
	//UninitializeFont();
	UninitializeData();
	UninitializeInput();
	SDL_Quit();
	MALib::LOG_Unitialize();
	return true;
}

HEX_END
#endif