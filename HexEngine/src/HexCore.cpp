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
	//MALib::LOG_Out1f("DELTA TIME", DeltaTime);
}
void UpdateFrameCount()
{
	static uint SecondCount = 0;
	static uint FrameCount = 0;
	FrameCount++;
	uint CurrentTime = (uint)time(0);
	if (SecondCount != CurrentTime)
	{
		SecondCount = CurrentTime;
		//MALib::LOG_Out1i("SECOND COUNT", SecondCount);
		MALib::LOG_Out1i("FRAME COUNT", FrameCount);
		FrameCount = 0;
	}
}

HexRender MainRender;
HexRender ShadowMap;
HexRender BrightPass;
HexRender Luminance;
HexRender DeferredPositions;
HexRender DeferredNormals;
HexRender AmbientOcclusion;

bool Toggle = true;
float Gamma = 2.2f;

HEX_API void OnFrameDraw()
{
	if (Cameras.length() < 1) return;
	
	Cameras[0]->load();
#if 1
	ResetUniforms();
	ShadowMap.load();

	SetUniform(UNIFORM_FLAG_SHADOW_RENDER);

	for (unsigned i = 0; i < Lights.length(); i++) Lights[i]->load();
	for (unsigned i = 0; i < Casters.length(); i++) Casters[i]->render();
	for (unsigned i = 0; i < Lights.length(); i++) Lights[i]->unload();

	ShadowMap.unload();
#endif
	ResetUniforms();
	MainRender.load();

	SetUniform(UNIFORM_FLAG_NORMAL);
	SetTextureSlot(UNIFORM_TEXTURE_SHADOW_MAP, ShadowMap.colorMap);
	SetUniform(UNIFORM_SHADOW_MAP_SIZE, 1024.0f);
	
	for (unsigned i = 0; i < Lights.length(); i++) Lights[i]->load();
	for (unsigned i = 0; i < Skyboxes.length(); i++) Skyboxes[i]->render();
	for (unsigned i = 0; i < Renderable.length(); i++) Renderable[i]->render();
	for (unsigned i = 0; i < Lights.length(); i++) Lights[i]->unload();

	MainRender.unload();
#if 1
	DeferredNormals.load();
	
	SetUniform(UNIFORM_FLAG_DEFER_NORMALS);
	for (unsigned i = 0; i < Renderable.length(); i++) Renderable[i]->render();

	DeferredNormals.unload();
	DeferredPositions.load();
	
	SetUniform(UNIFORM_FLAG_DEFER_POSITIONS);
	for (unsigned i = 0; i < Renderable.length(); i++) Renderable[i]->render();

	DeferredPositions.unload();
	AmbientOcclusion.load();
	
	SetTextureSlot(UNIFORM_TEXTURE_DEPTH_MAP, MainRender.depthMap);
	SetTextureSlot(UNIFORM_TEXTURE_DEFERRED_POSITIONS, DeferredPositions.colorMap);
	SetTextureSlot(UNIFORM_TEXTURE_DEFERRED_NORMALS, DeferredNormals.colorMap);
	PostProcess(UNIFORM_FLAG_POSTPROCESS_AMBIENTOCCLUSION);
	
	AmbientOcclusion.unload();
#endif
#if 0
	BrightPass.load();

	SetTextureSlot(UNIFORM_TEXTURE_COLOR_MAP, MainRender.colorMap);
	SetTextureSlot(UNIFORM_TEXTURE_DEPTH_MAP, MainRender.depthMap);
	SetUniform(UNIFORM_GAMMA, Gamma);
	PostProcess(UNIFORM_FLAG_POSTPROCESS_BRIGHTPASS);

	BrightPass.unload();
	Luminance.load();

	SetTextureSlot(UNIFORM_TEXTURE_COLOR_MAP, BrightPass.colorMap);
	PostProcess(UNIFORM_FLAG_POSTPROCESS_GUASSIAN_LARGE);

	Luminance.unload();

	SetTextureSlot(UNIFORM_TEXTURE_COLOR_MAP, MainRender.colorMap);
	SetTextureSlot(UNIFORM_TEXTURE_LUMINANCE_MAP, Luminance.colorMap);
	SetTextureSlot(UNIFORM_TEXTURE_AMBIENTOCCLUSION_MAP, AmbientOcclusion.colorMap);
	PostProcess(UNIFORM_FLAG_POSTPROCESS_FINAL_RENDER);
#else
	MainRender.blit();
#endif
	
	if (Toggle)
	{
		AmbientOcclusion.blit();
	}
	Cameras[0]->unload();

	SDL_GL_SwapBuffers();
}
HEX_API void OnFrameUpdate()
{
	if (Paused) return;
	
	for (unsigned i = 0; i < Entities.length(); i++)
	{
		Entities[i]->frameUpdate();
	}

	static float screenSize[2] = {float(ScreenRect.width), float(ScreenRect.height)};
	SetUniform(UNIFORM_SCREEN_SIZE, screenSize);

	UpdateFrameCount();
	UpdateDeltaTime();
}
HEX_API void OnFixedUpdate()
{
	if (Input::IsKeyDown(KEY_ESCAPE) || Input::IsButtonDown(XBOX_BACK)) ToggleRunning();
	if (Input::GetKey(KEY_SPACE, true)) Paused = !Paused;
	if (Paused) return;

	for (unsigned i = 0; i < Entities.length(); i++)
	{
		Entities[i]->fixedUpdate();
	}
	
	if (Input::GetKey(KEY_1, true)) Toggle = !Toggle;
	if (Input::GetKey(KEY_NUMPAD_7)) Gamma += 0.01f;
	if (Input::GetKey(KEY_NUMPAD_4)) Gamma -= 0.01f;

	PollControllers();
}

HEX_API bool Reshape(uint width, uint height)
{
	RenderSurface = SDL_SetVideoMode(width, height, 0, SDL_OPENGL | SDL_DOUBLEBUF | SDL_RESIZABLE);
	if (RenderSurface == NULL) 
		return false;
	
	SDL_Surface* icon = SDL_LoadBMP("data/icon.bmp");
	Uint8 iconKey = SDL_MapRGB(icon->format, 255, 255, 255);
	SDL_SetColorKey(icon, SDL_SRCCOLORKEY, iconKey);
	SDL_WM_SetIcon(icon, 0);
	SDL_FreeSurface(icon);
	
	ScreenRect = MALib::RECT(width, height);
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
	
	MALib::LOG_Message("START RESHAPE");
	Reshape(ScreenRect.width, ScreenRect.height);
	
	MALib::LOG_Message("START GLEW");
	GLenum glewStatus = glewInit();
	if (!GLEW_VERSION_3_0)
	{
		MALib::LOG_Message("Requires OpenGL 3.0 or later.");
		return false;
	}

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	
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

	MALib::LOG_Out1i("NUM OF UNIFORMS", NumOfUniforms);
	MALib::LOG_Outvi("UNIFORMS", (int*)&Uniforms, NumOfUniforms);
	MALib::LOG_Outvi("ATTRIBUTES", Attributes.pointer(), Attributes.length());
	
	MALib::LOG_Message("START INPUT");
	InitializeInput();
	MALib::LOG_Message("START DATA");
	InitializeData();
	
	MALib::LOG_Message("START FRAMEBUFFERS");
	InitializePostProcess();

	MainRender.build(RenderRect.width, RenderRect.height, true, true);
	ShadowMap.build(1024, 1024, true, false);
	BrightPass.build(128, 128, true, false);
	Luminance.build(128, 128, true, false);
	DeferredPositions.build(RenderRect.width, RenderRect.height, true, true);
	DeferredPositions.clear = MALib::COLOR(0.0f, 0.0f, 0.0f);
	DeferredNormals.build(RenderRect.width, RenderRect.height, true, true);
	DeferredNormals.clear = MALib::COLOR(0.0f, 0.0f, 0.0f);
	AmbientOcclusion.build(RenderRect.width, RenderRect.height, true, false);
	AmbientOcclusion.clear = MALib::COLOR(0.0f, 0.0f, 0.0f);
	
	MALib::LOG_Message("START SCENE");
	
	MALib::LOG_Message("END INITIALIZATION");
	return true;
}
HEX_API bool Unitialize()
{
	UninitializePostProcess();
	UninitializeData();
	UninitializeInput();
	SDL_Quit();
	MALib::LOG_Unitialize();
	return true;
}

HEX_END
#endif