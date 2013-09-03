#include "..\include\HexMain.h"

#ifdef _HEX_CORE_H_
HEX_BEGIN

void UpdateDeltaTime()
{
	static uint Ping = 0;
	uint NewPing = SDL_GetTicks();
	if (Ping == 0) Ping = NewPing;
	DeltaTime = float((NewPing - Ping) % 1000) / 1000.0f;
	//MALib::LOG_Out1f("DELTA TIME", DeltaTime);
	Ping = NewPing;
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
		MALib::LOG_Out1i("FRAME RATE", FrameCount);
		FrameCount = 0;
	}
}

bool ToggleBlitBrightPass = false;
bool ToggleBlitLuminance = false;
bool ToggleBlitAmbientOcclusion = false;
bool ToggleBlitDeferredNormals = false;
bool ToggleBlitShadow = false;

SDL_mutex* Lock = 0;

int FixedUpdateThread(void* data)
{
	Uint32 LastPing = ~0;
	while (AppRunning)
	{
		Uint32 NewPing = SDL_GetTicks();
		if (NewPing - LastPing >= 24)
		{
			SDL_LockMutex(Lock);
			OnFixedUpdate();
			SDL_UnlockMutex(Lock);
			LastPing = NewPing;
			UpdateDeltaTime();
		}
	}
	return 0;
}
int FrameUpdateThread(void* data)
{
	//Uint32 StartFrame = ~0;
	while (AppRunning)
	{
		PollEvents();

	//	Uint32 Current = SDL_GetTicks();
	//	if (Current - StartFrame >= 16)
	//	{
	//		StartFrame = SDL_GetTicks();
			SDL_LockMutex(Lock);
			OnFrameUpdate();
			OnFrameDraw();
			SDL_UnlockMutex(Lock);
			UpdateFrameCount();
	//	}
	}
	return 0;
}

HEX_API void OnStart()
{
	if (!AppRunning) return;
	MALib::LOG_Message("START SCENE");

	if (!StartDrawing())
	{
		ToggleRunning();
		return;
	}
	if (Entities.length() < 1)
	{
		ToggleRunning();
		return;
	}

	for (unsigned i = 0; i < Entities.length(); i++) Entities[i]->start();

	Lock = SDL_CreateMutex();
	SDL_Thread* fixedUpdateThread = SDL_CreateThread(FixedUpdateThread, 0);

	FrameUpdateThread(0);
	
	SDL_KillThread(fixedUpdateThread);
	SDL_UnlockMutex(Lock);
}
HEX_API void OnFrameDraw()
{
	if (Cameras.length() < 1) return;
	
	Cameras[0]->load();
	
	RenderShadowMap();
	RenderMain();
	RenderLuminance();
	if (EnableAmbientOcclusion) RenderDeferredNormals();
	RenderAmbientOcclusion();
	RenderGUILayer();
	
	FinalRender();
	
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
	
	SetUniform(UNIFORM_SHADOW_MAP_SIZE, float(ShadowRect.width));
	SetUniform(UNIFORM_GAMMA, Gamma);
	static float screenSize[2] = {float(ScreenRect.width), float(ScreenRect.height)};
	SetUniform(UNIFORM_SCREEN_SIZE, screenSize);
}
HEX_API void OnFixedUpdate()
{
	if (Input::GetKey(KEY_1, true))
	{
		ToggleBlitLuminance = false;
		ToggleBlitAmbientOcclusion = false;
		ToggleBlitDeferredNormals = false;
		ToggleBlitShadow = false;
	}
	if (Input::GetKey(KEY_2, true)) ToggleBlitLuminance = !ToggleBlitLuminance;
	if (Input::GetKey(KEY_3, true)) ToggleBlitAmbientOcclusion = !ToggleBlitAmbientOcclusion;
	if (Input::GetKey(KEY_4, true)) ToggleBlitDeferredNormals = !ToggleBlitDeferredNormals;

	if (Input::GetKey(KEY_5, true)) EnableLuminance = !EnableLuminance;
	if (Input::GetKey(KEY_6, true)) EnableAmbientOcclusion = !EnableAmbientOcclusion;
	
	if (Input::GetKey(KEY_7, true)) ToggleBlitShadow = !ToggleBlitShadow;

	if (Input::GetKey(KEY_NUMPAD_7)) Gamma += 0.01f;
	if (Input::GetKey(KEY_NUMPAD_4)) Gamma -= 0.01f;

	if (Input::IsKeyDown(KEY_ESCAPE) || Input::IsButtonDown(XBOX_BACK)) ToggleRunning();
	if (Input::GetKey(KEY_SPACE, true)) Paused = !Paused;
	if (Paused) return;

	for (unsigned i = 0; i < Entities.length(); i++)
	{
		Entities[i]->fixedUpdate();
	}
}

HEX_API bool Reshape(uint width, uint height)
{
	RenderSurface = SDL_SetVideoMode(width, height, 0, SDL_OPENGL | SDL_DOUBLEBUF | SDL_RESIZABLE);
	if (RenderSurface == NULL) 
		return false;
	
#if 0
	SDL_Surface* icon = SDL_LoadBMP("data/icon.bmp");
	Uint8 iconKey = SDL_MapRGB(icon->format, 255, 255, 255);
	SDL_SetColorKey(icon, SDL_SRCCOLORKEY, iconKey);
	SDL_WM_SetIcon(icon, 0);
	SDL_FreeSurface(icon);
#endif
	
	ScreenRect = MALib::RECT(width, height);
	OnMouseMove(width / 2, height / 2);

	return true;
}
HEX_API bool Initialize(uint argc, string* argv)
{
	MALib::LOG_Initialize(true);
	MALib::RANDOM_Initialize();

	MALib::LOG_Message("START INTIALIZING");
	for (unsigned i = 0; i < argc; i++)
	{
		MALib::LOG_Message(argv[i]);
	}

	MALib::LOG_Message("START INPUT");
	InitializeInput();
	MALib::LOG_Message("START DATA");
	InitializeData();

	MALib::LOG_Message("START PREFERENCES");
	if (!InitializePreferences()) 
		return false;
	MALib::LOG_Message("START LOAD ORDER");
	if (!InitializeLoadOrder()) 
		return false;

	MALib::LOG_Message("START DRAW INITIALIZING");
	if (!InitializeDraw()) 
		return false;
	MALib::LOG_Message("END DRAW INITIALIZATION");
	
	MALib::LOG_Message("END INITIALIZATION");
	return true;
}
HEX_API bool Uninitialize()
{
	UninitializeDraw();
	UninitializeLoadOrder();
	UninitializePreferences();
	UninitializeData();
	UninitializeInput();
	MALib::LOG_Unitialize();
	return true;
}

HEX_END
#endif