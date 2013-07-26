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
HexRender ShadowMap;
HexRender BrightPass;
HexRender Luminance;

bool Toggle3D = false;
bool ToggleLuminance = true;
uint LuminanceCounter = 0;
float gamma = 2.2f;

HEX_API void OnFrameDraw()
{
	if (Paused) return;
	if (Cameras.length() < 1) return;
	
	ResetUniforms();
#if 1
	ShadowMap.load();

	SetUniform(UNIFORM_FLAG_SHADOW_RENDER);
	for (unsigned i = 0; i < Lights.length(); i++) Lights[i]->render();
	for (unsigned i = 0; i < Renderable.length(); i++) Renderable[i]->render();

	ShadowMap.unload();
#endif
	ResetUniforms();
	MainRender.load();

	SetUniform(UNIFORM_FLAG_NORMAL);
	SetTextureSlot(UNIFORM_TEXTURE_SHADOW_MAP, ShadowMap.colorMap);
	SetUniform(UNIFORM_SHADOW_MAP_SIZE, 1024.0f);
	
	Cameras[0]->render();
	for (unsigned i = 0; i < Lights.length(); i++) Lights[i]->render();
	for (unsigned i = 0; i < Skyboxes.length(); i++) Skyboxes[i]->render();
	for (unsigned i = 0; i < Renderable.length(); i++) Renderable[i]->render();

	MainRender.unload();
	LuminanceCounter++;
	if (true)//LuminanceCounter >= 30)
	{
		BrightPass.load();

		SetTextureSlot(UNIFORM_TEXTURE_COLOR_MAP, MainRender.colorMap);
		SetTextureSlot(UNIFORM_TEXTURE_DEPTH_MAP, MainRender.depthMap);
		SetUniform(UNIFORM_GAMMA, gamma);
		PostProcess(UNIFORM_FLAG_POSTPROCESS_BRIGHTPASS);

		BrightPass.unload();
		Luminance.load();

		SetTextureSlot(UNIFORM_TEXTURE_COLOR_MAP, BrightPass.colorMap);
		PostProcess(UNIFORM_FLAG_POSTPROCESS_GUASSIAN_LARGE);

		Luminance.unload();
		LuminanceCounter = 0;
	}

	SetTextureSlot(UNIFORM_TEXTURE_COLOR_MAP, MainRender.colorMap);
	SetTextureSlot(UNIFORM_TEXTURE_LUMINANCE_MAP, Luminance.colorMap);
	PostProcess(UNIFORM_FLAG_POSTPROCESS_FINAL_RENDER);
	
#if 0
	BrightPass.blit();
#elif 0
	Luminance.blit();
#endif

	if (!ToggleLuminance) MainRender.blit();

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
	
	//torus->transform->rotate(0.0f, 24.0f * DeltaTime, 0.0f);
	if (Input::GetKey(KEY_NUMPAD_1, true)) Toggle3D = !Toggle3D;
	if (Input::GetKey(KEY_SPACE, true)) ToggleLuminance = !ToggleLuminance;
	if (Input::GetKey(KEY_NUMPAD_7)) gamma += 0.01f;
	if (Input::GetKey(KEY_NUMPAD_4)) gamma -= 0.01f;

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

	MainRender.build(ScreenRect.width, ScreenRect.height, true, true);
	ShadowMap.build(1024, 1024, true, false);
	BrightPass.build(128, 128, true, false);
	Luminance.build(128, 128, true, false);
	
	MALib::LOG_Message("START SCENE");
	//BuildScene();
	//OnFixedUpdate();
	
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