#include "..\include\HexMain.h"

#ifdef _HEX_DRAW_H_
HEX_BEGIN

HexRender MainRender;
HexRender ShadowMap;
HexRender BrightPass;
HexRender Luminance;
HexRender DeferredPositions;
HexRender DeferredNormals;
HexRender AmbientOcclusion;
HexRender AmbientOcclusionBilateral;
	
HEX_API bool InitializeDraw()
{
	MALib::LOG_Message("START DRAW INITIALIZING");

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
	if (!Reshape(ScreenRect.width, ScreenRect.height))
	{
		MALib::LOG_Message("Could not build window.");
		return false;
	}
	
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

#if 0
	MALib::LOG_Message("GL VENDOR                  ", (char*)glGetString(GL_VENDOR));
	MALib::LOG_Message("GL RENDERER                ", (char*)glGetString(GL_RENDERER));
	MALib::LOG_Message("GL VERSION                 ", (char*)glGetString(GL_VERSION));
	MALib::LOG_Message("GL SHADING_LANGUAGE_VERSION", (char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
	MALib::LOG_Out1i("NUM OF UNIFORMS", NumOfUniforms);
	MALib::LOG_Outvi("UNIFORMS", (int*)&Uniforms, NumOfUniforms);
	MALib::LOG_Outvi("ATTRIBUTES", Attributes.pointer(), Attributes.length());
#endif
	
	MALib::LOG_Message("START SHADER");
	if (!BuildProgram("data/gl_shader.vert", "data/gl_shader.frag"))
	{
		MALib::LOG_Message("Could not build shaders.");
		return false;
	}
	
	MALib::LOG_Message("START ATTRIBUTES");
	InitializeAttributes();
	MALib::LOG_Message("START UNIFORMS");
	InitializeUniforms();

	MALib::LOG_Message("START FRAMEBUFFERS");
	InitializePostProcess();
	
	MainRender.build(RenderRect.width, RenderRect.height, true, true);
	MainRender.setClearColor(0.3f, 0.3f, 0.3f);
	ShadowMap.build(1024, 1024, true, false);
	ShadowMap.setClearColor(1.0f, 1.0f, 1.0f);
	BrightPass.build(128, 128, true, false);
	BrightPass.setClearColor(0.0f, 0.0f, 0.0f);
	Luminance.build(128, 128, true, false);
	Luminance.setClearColor(0.0f, 0.0f, 0.0f);
	DeferredNormals.build(RenderRect.width, RenderRect.height, true, true);
	DeferredNormals.setClearColor(0.5f, 0.5f, 1.0f);
	AmbientOcclusion.build(RenderRect.width, RenderRect.height, true, false);
	AmbientOcclusion.setClearColor(1.0f, 1.0f, 1.0f);
	AmbientOcclusionBilateral.build(RenderRect.width, RenderRect.height, true, false);
	AmbientOcclusionBilateral.setClearColor(1.0f, 1.0f, 1.0f);

	MALib::LOG_Message("END DRAW INITIALIZATION");
	return true;
}
HEX_API bool UninitializeDraw()
{
	return true;
}
HEX_API void StartDrawing()
{
	MALib::LOG_Message("START BUILDING SHAPES");
	MALib::LOG_Out1i("NUM OF SHAPES", Shapes.length());
	for (uint i = 0; i < Shapes.length(); i++) Shapes[i]->build();
	MALib::LOG_Message("START BUILDING MATERIALS");
	MALib::LOG_Out1i("NUM OF MATERIALS", Materials.length());
	for (uint i = 0; i < Materials.length(); i++) Materials[i]->build();
}

HEX_END
#endif