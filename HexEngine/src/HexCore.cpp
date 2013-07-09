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

float ScreenPlane[24] = 
{
	1.0f, 1.0f, 0.0f, 1.0f, 
	0.0f, 1.0f, 0.0f, 1.0f, 
	1.0f, 0.0f, 0.0f, 1.0f, 
	0.0f, 1.0f, 0.0f, 1.0f, 
	0.0f, 0.0f, 0.0f, 1.0f, 
	1.0f, 0.0f, 0.0f, 1.0f, 
};
uint ScreenPlaneVAO = 0;
uint ScreenPlaneBO = 0;

uint ShadowMap = 0;
uint RenderTex = 0;
uint RenderDepth = 0;
uint RenderWidth = 800;
uint RenderHeight = 600;

uint ShadowFBO = 0;
uint RenderFBO = 0;

HexEntity* torus = 0;
bool toggle = false;

HEX_API void OnFrameDraw()
{
	if (Paused) return;
	
	glBindFramebuffer(GL_FRAMEBUFFER, ShadowFBO);
	glViewport(0, 0, 1024, 1024);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetUniform(UNIFORM_FLAG_SHADOW_RENDER);
	for (unsigned i = 0; i < Entities.length(); i++)
	{
		Entities[i]->render();
	}

	glBindFramebuffer(GL_FRAMEBUFFER, RenderFBO);
	glViewport(0, 0, RenderWidth, RenderHeight);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ResetUniforms();
	SetTextureSlot(UNIFORM_TEXTURE_SHADOW_MAP, ShadowMap);
	float ShadowMapSize[2] = {1024.0f, 1024.0f};
	SetUniform(UNIFORM_SHADOW_MAP_SIZE, ShadowMapSize);
	for (unsigned i = 0; i < Entities.length(); i++)
	{
		Entities[i]->render();
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	glBindFramebuffer(GL_READ_FRAMEBUFFER, RenderFBO);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBlitFramebuffer(0, 0, RenderWidth, RenderHeight, 0, 0, RenderWidth, RenderHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	
#if 1
	if (toggle)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		SetUniform(UNIFORM_FLAG_POSTPROCESS_GUASSIAN);
		SetTextureSlot(UNIFORM_TEXTURE_COLOR_MAP, RenderTex);
		SetTextureSlot(UNIFORM_TEXTURE_DEPTH_MAP, RenderDepth);
		glBindVertexArray(ScreenPlaneVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}
#endif

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
	
	glViewport(0, 0, width, height);
	ScreenDimensions[0] = width;
	ScreenDimensions[1] = height;

#if 0
	if (RenderTex != 0) glDeleteTextures(1, &RenderTex);
	if (RenderDepth != 0) glDeleteTextures(1, &RenderDepth);
	if (RenderFBO != 0) glDeleteFramebuffers(1, &RenderFBO);
#endif

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

	MALib::LOG_Outiv("UNIFORMS", (int*)&Uniforms, 17);
	//MALib::LOG_Outiv("ATTRIBUTES", Attributes.pointer(), Attributes.length());
	
	MALib::LOG_Message("START INPUT");
	InitializeInput();
	MALib::LOG_Message("START DATA");
	InitializeData();
	/*MALib::LOG_Message("START FONT");
	InitializeFont();*/
	
	MALib::LOG_Message("START FRAMEBUFFERS");
	glGenTextures(1, &ShadowMap);
	glBindTexture(GL_TEXTURE_2D, ShadowMap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	//glTexParameteri( GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);
	//MALib::LOG_Out1i("ShadowMap", ShadowMap);

	glGenTextures(1, &RenderTex);
	glBindTexture(GL_TEXTURE_2D, RenderTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, RenderWidth, RenderHeight, 0, GL_RGBA, GL_UNSIGNED_INT, NULL);
	glGenerateMipmap(GL_TEXTURE_2D);
	//MALib::LOG_Out1i("RenderTex", RenderTex);

	glGenTextures(1, &RenderDepth);
	glBindTexture(GL_TEXTURE_2D, RenderDepth);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, RenderWidth, RenderHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);
	//MALib::LOG_Out1i("RenderDepth", RenderDepth);

	glGenFramebuffers(1, &ShadowFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, ShadowFBO);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, ShadowMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		MALib::LOG_Message("Shadow map framebuffer not complete.");
		return false;
	}
	//MALib::LOG_Out1i("ShadowFBO", ShadowFBO);
	
	glGenFramebuffers(1, &RenderFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, RenderFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, RenderTex, 0);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, RenderDepth, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		MALib::LOG_Message("Render framebuffer not complete.");
		return false;
	}
	//MALib::LOG_Out1i("RenderFBO", RenderFBO);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glGenVertexArrays(1, &ScreenPlaneVAO);
	glBindVertexArray(ScreenPlaneVAO);
	glGenBuffers(1, &ScreenPlaneBO);
	glBindBuffer(GL_ARRAY_BUFFER, ScreenPlaneBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ScreenPlaneBO);

	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), ScreenPlane, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	
	MALib::LOG_Message("START SCENE");
	uint entities[8];
	uint i = 0;
	GenEntities(7, entities);

	BindEntity(entities[i]);i++;
	AddShape(Meshes[6]);
	AddMaterial(Textures[4]);
	AddSkybox();
	
	BindEntity(entities[i]);i++;
	TransformEntity(0.0f, 1.0f, -4.0f, 0.0f, 0.0f, 0.0f);
	AddCamera(45.0f, 4.0f / 3.0f, 0.01f, 100.0f);
	AddController();
	
	BindEntity(entities[i]);i++;
	TransformEntity(0.0f, 1.0f, 0.0f, -50.0f, 60.0f, 0.0f);
	AddLight(HEX_LIGHTMODE_DIRECTIONAL, 1.0f, 0.0f, 0.0f, 0.0f);
	
	BindEntity(entities[i]);i++;
	TransformEntity(2.0f, 2.0f, -3.0f, 0.0f, 0.0f, 0.0f);
	AddLight(HEX_LIGHTMODE_POINT, 1.0f);
	
	BindEntity(entities[i]);i++;
	TransformEntity(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 60.0f);
	AddShape(Meshes[5]);
	AddMaterial(Textures[0], Textures[1]);
	BoundEntity->material->uvRepeat *= MALib::VEC2(8.0f, 4.0f);
	torus = BoundEntity;
	
	BindEntity(entities[i]);i++;
	TransformEntity(2.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	AddShape(Meshes[4]);
	AddMaterial(Textures[0], Textures[1]);
	
	BindEntity(entities[i]);i++;
	TransformEntity(0.0f, 0.0f, 0.0f, -90.0f, 0.0f, 0.0f);
	AddShape(Meshes[2]);
	AddMaterial(Textures[2], Textures[3]);
	BoundEntity->material->uvRepeat *= MALib::VEC2(4.0f, 4.0f);
	BoundEntity->transform->scale(8.0f, 8.0f, 8.0f);
	
	MALib::LOG_Message("END INITIALIZATION");
	return true;
}
HEX_API bool Unitialize()
{
	if (RenderTex != 0) glDeleteTextures(1, &RenderTex);
	if (RenderDepth != 0) glDeleteTextures(1, &RenderDepth);
	if (RenderFBO != 0) glDeleteFramebuffers(1, &RenderFBO);
	if (ShadowMap != 0) glDeleteTextures(1, &ShadowMap);
	if (ShadowFBO != 0) glDeleteFramebuffers(1, &ShadowFBO);

	UninitializeFont();
	UninitializeData();
	UninitializeInput();
	SDL_Quit();
	MALib::LOG_Unitialize();
	return true;
}

HEX_END
#endif