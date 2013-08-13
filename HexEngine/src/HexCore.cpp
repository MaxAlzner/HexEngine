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

bool ToggleBlitBrightPass = false;
bool ToggleBlitLuminance = false;
bool ToggleBlitAmbientOcclusion = false;
bool ToggleBlitDeferredNormals = false;
bool ToggleLuminance = true;
bool ToggleAmbientOcclusion = false;
float Gamma = 2.2f;

int EventThread(void* data)
{
	while (AppRunning)
	{
		PollEvents();
	}
	return 0;
}
int FixedUpdateThread(void* data)
{
	Uint32 LastPing = ~0;
	while (AppRunning)
	{
		Uint32 NewPing = SDL_GetTicks();
		if (NewPing - LastPing > 24)
		{
			OnFixedUpdate();
			LastPing = NewPing;
		}
	}
	return 0;
}

HEX_API void OnStart()
{
	MALib::LOG_Message("START SCENE");
	
	StartDrawing();

	for (unsigned i = 0; i < Entities.length(); i++)
	{
		Entities[i]->start();
	}

#if 0
	SDL_Thread* eventThread = SDL_CreateThread(EventThread, 0);
	SDL_Thread* fixedUpdateThread = SDL_CreateThread(FixedUpdateThread, 0);

	while (AppRunning)
	{
		OnFrameUpdate();
		OnFrameDraw();
	}

	SDL_KillThread(eventThread);
	SDL_KillThread(fixedUpdateThread);
#else
	Uint32 FramePing = ~0;
	Uint32 UpdatePing = ~0;
	while (AppRunning)
	{
		PollEvents();
		
		Uint32 NewPing = SDL_GetTicks();
		if (NewPing - FramePing > 16)
		{
			OnFrameUpdate();
			OnFrameDraw();
			FramePing = NewPing;
		}
		if (NewPing - UpdatePing > 24)
		{
			OnFixedUpdate();
			UpdatePing = NewPing;
		}
	}
#endif
}
HEX_API void OnFrameDraw()
{
	if (Cameras.length() < 1) return;
	
	Cameras[0]->load();
#if 0
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
	AmbientOcclusion.load();
	
	SetTextureSlot(UNIFORM_TEXTURE_DEPTH_MAP, MainRender.depthMap);
	SetTextureSlot(UNIFORM_TEXTURE_DEFERRED_POSITIONS, DeferredPositions.colorMap);
	SetTextureSlot(UNIFORM_TEXTURE_DEFERRED_NORMALS, DeferredNormals.colorMap);
	if (ToggleAmbientOcclusion) PostProcess(UNIFORM_FLAG_POSTPROCESS_AMBIENTOCCLUSION);
	
	AmbientOcclusion.unload();
#if 1
	AmbientOcclusionBilateral.load();

	SetTextureSlot(UNIFORM_TEXTURE_COLOR_MAP, AmbientOcclusion.colorMap);
	if (ToggleAmbientOcclusion) PostProcess(UNIFORM_FLAG_POSTPROCESS_BILATERAL_GUASSIAN);

	AmbientOcclusionBilateral.unload();
	SetTextureSlot(UNIFORM_TEXTURE_AMBIENTOCCLUSION_MAP, AmbientOcclusionBilateral.colorMap);
#else
	SetTextureSlot(UNIFORM_TEXTURE_AMBIENTOCCLUSION_MAP, AmbientOcclusion.colorMap);
#endif
#endif
#if 1
	BrightPass.load();
	
	SetTextureSlot(UNIFORM_TEXTURE_COLOR_MAP, MainRender.colorMap);
	if (ToggleLuminance) PostProcess(UNIFORM_FLAG_POSTPROCESS_BRIGHTPASS);

	BrightPass.unload();
	Luminance.load();

	SetTextureSlot(UNIFORM_TEXTURE_COLOR_MAP, BrightPass.colorMap);
	if (ToggleLuminance) PostProcess(UNIFORM_FLAG_POSTPROCESS_GUASSIAN_LARGE);

	Luminance.unload();
#if 1
	BrightPass.load();
	
	SetTextureSlot(UNIFORM_TEXTURE_COLOR_MAP, Luminance.colorMap);
	if (ToggleLuminance) PostProcess(UNIFORM_FLAG_POSTPROCESS_GUASSIAN_LARGE);

	BrightPass.unload();
	Luminance.load();

	SetTextureSlot(UNIFORM_TEXTURE_COLOR_MAP, BrightPass.colorMap);
	if (ToggleLuminance) PostProcess(UNIFORM_FLAG_POSTPROCESS_GUASSIAN_LARGE);

	Luminance.unload();
#endif
	SetTextureSlot(UNIFORM_TEXTURE_LUMINANCE_MAP, Luminance.colorMap);
#endif
#if 1
	SetTextureSlot(UNIFORM_TEXTURE_COLOR_MAP, MainRender.colorMap);
	PostProcess(UNIFORM_FLAG_POSTPROCESS_FINAL_RENDER);
#else
	MainRender.blit();
#endif
	
	if (ToggleBlitBrightPass) BrightPass.blit();
	if (ToggleBlitLuminance) Luminance.blit();
	if (ToggleBlitAmbientOcclusion) AmbientOcclusionBilateral.blit();
	if (ToggleBlitDeferredNormals) DeferredNormals.blit();

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
	
	SetUniform(UNIFORM_SHADOW_MAP_SIZE, 1024.0f);
	SetUniform(UNIFORM_GAMMA, Gamma);
	static float screenSize[2] = {float(ScreenRect.width), float(ScreenRect.height)};
	SetUniform(UNIFORM_SCREEN_SIZE, screenSize);

	UpdateFrameCount();
	UpdateDeltaTime();
}
HEX_API void OnFixedUpdate()
{
	if (Input::GetKey(KEY_1, true))
	{
		ToggleBlitLuminance = false;
		ToggleBlitAmbientOcclusion = false;
		ToggleBlitDeferredNormals = false;
	}
	if (Input::GetKey(KEY_2, true)) ToggleBlitLuminance = !ToggleBlitLuminance;
	if (Input::GetKey(KEY_3, true)) ToggleBlitAmbientOcclusion = !ToggleBlitAmbientOcclusion;
	if (Input::GetKey(KEY_4, true)) ToggleBlitDeferredNormals = !ToggleBlitDeferredNormals;

	if (Input::GetKey(KEY_5, true)) ToggleLuminance = !ToggleLuminance;
	if (Input::GetKey(KEY_6, true)) ToggleAmbientOcclusion = !ToggleAmbientOcclusion;

	if (Input::GetKey(KEY_NUMPAD_7)) Gamma += 0.01f;
	if (Input::GetKey(KEY_NUMPAD_4)) Gamma -= 0.01f;

	if (Input::IsKeyDown(KEY_ESCAPE) || Input::IsButtonDown(XBOX_BACK)) ToggleRunning();
	if (Input::GetKey(KEY_SPACE, true)) Paused = !Paused;
	if (Paused) return;

	for (unsigned i = 0; i < Entities.length(); i++)
	{
		Entities[i]->fixedUpdate();
	}
	
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

	MALib::LOG_Message("START INPUT");
	InitializeInput();
	MALib::LOG_Message("START DATA");
	InitializeData();
	
	if (!InitializeDraw()) 
		return false;
	
	MALib::LOG_Message("END INITIALIZATION");
	return true;
}
HEX_API bool Unitialize()
{
	UninitializeDraw();
	UninitializePostProcess();
	UninitializeData();
	UninitializeInput();
	SDL_Quit();
	MALib::LOG_Unitialize();
	return true;
}

HEX_END
#endif