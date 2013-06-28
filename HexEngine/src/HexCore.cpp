#include "..\include\HexMain.h"

#ifdef _HEX_CORE_H_
HEX_BEGIN

HEX_API void OnFrameDraw()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (unsigned i = 0; i < Entities.length(); i++)
	{
		Entities[i]->frameUpdate();
		Entities[i]->render();
	}

	SDL_GL_SwapBuffers();
}
HEX_API void OnFrameUpdate()
{
	DeltaTime += 0.001f;
	if (DeltaTime > 1.0f) DeltaTime = 0.0f;

	for (unsigned i = 0; i < Entities.length(); i++) 
		Entities[i]->fixedUpdate();
	
	Entities[2]->transform->rotate(0.0f, 1.0f, 0.0f);
}
HEX_API void OnFixedUpdate()
{
}

HEX_API bool Reshape(unsigned width, unsigned height)
{
	ScreenSurface = SDL_SetVideoMode(width, height, 0, SDL_OPENGL | SDL_RESIZABLE);
	if (ScreenSurface == NULL) 
		return false;
	
	glViewport(0, 0, width, height);

	return true;
}
HEX_API bool Initialize(unsigned argc, char **argv)
{
	MALib::LOG_Initialize(true);
	MALib::RANDOM_Initialize();

	for (unsigned i = 0; i < argc; i++)
	{
		MALib::LOG_Message(argv[i]);
	}

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

	Reshape(800, 600);
	
	GLenum glewStatus = glewInit();
	if (!GLEW_VERSION_3_0)
	{
		MALib::LOG_Message("Requires OpenGL 3.0 or later.");
		return false;
	}

	glEnable(GL_DEPTH_TEST);
	
	MALib::LOG_Message("GL VENDOR                  ", (char*)glGetString(GL_VENDOR));
	MALib::LOG_Message("GL RENDERER                ", (char*)glGetString(GL_RENDERER));
	MALib::LOG_Message("GL VERSION                 ", (char*)glGetString(GL_VERSION));
	MALib::LOG_Message("GL SHADING_LANGUAGE_VERSION", (char*)glGetString(GL_SHADING_LANGUAGE_VERSION));

	if (!BuildProgram("data/gl_shader.vert", "data/gl_shader.frag"))
	{
		MALib::LOG_Message("Could not build shaders.");
		return false;
	}
	InitializeAttributes();
	InitializeUniforms();

	MALib::LOG_Outiv("UNIFORMS  ", Uniforms.pointer(), Uniforms.length());
	MALib::LOG_Outiv("ATTRIBUTES", Attributes.pointer(), Attributes.length());

	InitializeData();

	HexEntity* cam = GenerateEntity(0.0f, 1.0f, -3.0f, 0.0f, 0.0f, 0.0f);
	GenerateCamera(cam, 45.0f, 4.0f / 3.0f, 0.01f, 100.0f);
	
	HexEntity* light = GenerateEntity(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	GenerateLight(light, HEX_LIGHTMODE_DIRECTIONAL, 1.0f, 0.0f, 0.0f, 0.0f);

	HexEntity* obj1 = GenerateEntity(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	GenerateShape(obj1, Meshes[3]);
	MaterialNode* obj1mat = GenerateMaterial(obj1);
	obj1mat->add(Textures[1]);

	HexEntity* obj2 = GenerateEntity(0.0f, -0.2f, 0.0f, -90.0f, 0.0f, 0.0f);
	GenerateShape(obj2, Meshes[2]);
	obj2->transform->scale(4.0f, 4.0f, 4.0f);

	return true;
}
HEX_API bool Unitialize()
{
	//delete shape;

	SDL_Quit();
	MALib::LOG_Unitialize();
	return true;
}

HEX_END
#endif