#include "..\include\HexMain.h"

#ifdef _HEX_DRAW_H_
HEX_BEGIN

HexRender MainRender;
HexRender BrightPass;
HexRender Luminance;
HexRender DeferredPositions;
HexRender DeferredNormals;
HexRender AmbientOcclusion;
HexRender AmbientOcclusionBilateral;
HexRender LeftEye;
HexRender RightEye;
HexRender GUILayer;
	
HEX_API bool InitializeDraw()
{
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
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
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
	glEnable(GL_MULTISAMPLE);
	glDisable(GL_BLEND);
	
	MALib::LOG_Message("START SHADER");
	if (!BuildProgram())
	{
		MALib::LOG_Message("Could not build shaders.");
		return false;
	}
	
	MALib::LOG_Message("START ATTRIBUTES");
	InitializeAttributes();
	MALib::LOG_Message("START UNIFORMS");
	InitializeUniforms();

#if 1
	MALib::LOG_Message("GL VENDOR                  ", (char*)glGetString(GL_VENDOR));
	MALib::LOG_Message("GL RENDERER                ", (char*)glGetString(GL_RENDERER));
	MALib::LOG_Message("GL VERSION                 ", (char*)glGetString(GL_VERSION));
	MALib::LOG_Message("GL SHADING_LANGUAGE_VERSION", (char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
	MALib::LOG_Out1i("NUM OF UNIFORMS", NumOfUniforms);
	MALib::LOG_Outvi("UNIFORMS", (int*)&Uniforms, NumOfUniforms);
	MALib::LOG_Outvi("ATTRIBUTES", Attributes.pointer(), Attributes.length());
#endif

	MALib::LOG_Message("START FRAMEBUFFERS");
	InitializePostProcess();
	MALib::LOG_Message("START GUI");
	InitializeGUI();
	
	MainRender.build(RenderRect.width, RenderRect.height, true, true);
	MainRender.setClearColor(0.3f, 0.3f, 0.3f);
	BrightPass.build(LuminanceRect.width, LuminanceRect.height, true, false);
	BrightPass.setClearColor(0.0f, 0.0f, 0.0f);
	Luminance.build(LuminanceRect.width, LuminanceRect.height, true, false);
	Luminance.setClearColor(0.0f, 0.0f, 0.0f);
	DeferredPositions.build(RenderRect.width, RenderRect.height, true, true);
	DeferredPositions.setClearColor(0.5f, 0.5f, 0.5f);
	DeferredNormals.build(RenderRect.width, RenderRect.height, true, true);
	DeferredNormals.setClearColor(0.5f, 0.5f, 1.0f);
	AmbientOcclusion.build(RenderRect.width, RenderRect.height, true, false);
	AmbientOcclusion.setClearColor(1.0f, 1.0f, 1.0f);
	AmbientOcclusionBilateral.build(RenderRect.width, RenderRect.height, true, false);
	AmbientOcclusionBilateral.setClearColor(1.0f, 1.0f, 1.0f);
#if 0
	LeftEye.build(RenderRect.width, RenderRect.height, true, true);
	LeftEye.setClearColor(0.3f, 0.3f, 0.3f);
	RightEye.build(RenderRect.width, RenderRect.height, true, true);
	RightEye.setClearColor(0.3f, 0.3f, 0.3f);
#endif
	GUILayer.build(RenderRect.width, RenderRect.height, true, false);
	GUILayer.setClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	return true;
}
HEX_API bool UninitializeDraw()
{
	MainRender.destroy();
	BrightPass.destroy();
	Luminance.destroy();
	DeferredPositions.destroy();
	DeferredNormals.destroy();
	AmbientOcclusion.destroy();
	AmbientOcclusionBilateral.destroy();
	LeftEye.destroy();
	RightEye.destroy();
	
	UninitializeUniforms();
	UninitializeAttributes();
	UninitializePostProcess();
	UninitializeGUI();
	SDL_Quit();
	return true;
}

HEX_API bool StartDrawing()
{
	if (Shapes.length() < 1 || Materials.length() < 1)
	{
		MALib::LOG_Message("COULD NOT FIND ANY MATERIALS OR SHAPES");
		return false;
	}

	MALib::LOG_Message("START BUILDING SHAPES");
	MALib::LOG_Out1i("NUM OF SHAPES", Shapes.length());
	for (uint i = 0; i < Shapes.length(); i++) Shapes[i]->build();

	MALib::LOG_Message("START BUILDING MATERIALS");
	MALib::LOG_Out1i("NUM OF MATERIALS", Materials.length());
	for (uint i = 0; i < Materials.length(); i++) Materials[i]->build();
	
	MALib::LOG_Message("START BUILDING GUI");
	StartGUI();

	return true;
}

void RenderMain()
{
	ResetUniforms();
	MainRender.load();

	SetUniform(UNIFORM_FLAG_NORMAL);
	SetTextureSlot(UNIFORM_TEXTURE_SHADOW_MAP, ShadowCaster->shadowMap);
	
	for (unsigned i = 0; i < Lights.length(); i++) Lights[i]->load();
	if (MainSkybox != NULL) MainSkybox->root->render();
	for (unsigned i = 0; i < Renderable.length(); i++) Renderable[i]->render();
	for (unsigned i = 0; i < Lights.length(); i++) Lights[i]->unload();

	MainRender.unload();
}
void RenderShadowMap()
{
	if (!EnableShadow)
	{
		return;
	}
	ResetUniforms();
	
	float mapSize[2] = {float(ShadowRect.width), float(ShadowRect.height)};
	SetUniform(UNIFORM_MAP_SIZE, mapSize);
	SetUniform(UNIFORM_FLAG_SHADOW_RENDER);

	if (ShadowCaster != NULL) ShadowCaster->load();
#if 1
	if (EnableShadow) for (unsigned i = 0; i < Casters.length(); i++) Casters[i]->render();
#else
	if (EnableShadow) for (unsigned i = 0; i < Renderable.length(); i++) Renderable[i]->render();
#endif
	if (ShadowCaster != NULL) ShadowCaster->unload();
}
void RenderLuminance()
{
	if (!EnableLuminance)
	{
		BrightPass.load();
		BrightPass.unload();
		Luminance.load();
		Luminance.unload();
		return;
	}
	ResetUniforms();
	BrightPass.load();
	
	float mapSize[2] = {float(LuminanceRect.width), float(LuminanceRect.height)};
	SetUniform(UNIFORM_MAP_SIZE, mapSize);
	SetUniform(UNIFORM_FILTER_RADIUS, MALib::Interp((sin(Theta) * 0.5f) + 0.5f, 0.5f, 1.0f) * BloomFilterRadius);
	SetTextureSlot(UNIFORM_TEXTURE_COLOR_MAP, MainRender.colorMap);
	PostProcess(UNIFORM_FLAG_POSTPROCESS_BRIGHTPASS);

	BrightPass.unload();
	Luminance.load();

	SetTextureSlot(UNIFORM_TEXTURE_COLOR_MAP, BrightPass.colorMap);
	PostProcess(UNIFORM_FLAG_POSTPROCESS_RANDOM_GUASSIAN);

	Luminance.unload();
#if 1
	BrightPass.load();
	
	SetTextureSlot(UNIFORM_TEXTURE_COLOR_MAP, Luminance.colorMap);
	PostProcess(UNIFORM_FLAG_POSTPROCESS_RANDOM_GUASSIAN);

	BrightPass.unload();
	Luminance.load();

	SetTextureSlot(UNIFORM_TEXTURE_COLOR_MAP, BrightPass.colorMap);
	PostProcess(UNIFORM_FLAG_POSTPROCESS_RANDOM_GUASSIAN);

	Luminance.unload();
#endif
}
void RenderDeferredPositions()
{
	DeferredPositions.load();
	
	SetUniform(UNIFORM_FLAG_DEFER_POSITIONS);
	for (unsigned i = 0; i < Renderable.length(); i++) Renderable[i]->render();

	DeferredPositions.unload();
}
void RenderDeferredNormals()
{
	DeferredNormals.load();
	
	SetUniform(UNIFORM_FLAG_DEFER_NORMALS);
	for (unsigned i = 0; i < Renderable.length(); i++) Renderable[i]->render();

	DeferredNormals.unload();
}
void RenderAmbientOcclusion()
{
	if (!EnableAmbientOcclusion)
	{
		AmbientOcclusion.load();
		AmbientOcclusion.unload();
		AmbientOcclusionBilateral.load();
		AmbientOcclusionBilateral.unload();
		return;
	}
	ResetUniforms();

	AmbientOcclusion.load();
	
	SetUniform(UNIFORM_FILTER_RADIUS, AOFilterRadius);
	SetTextureSlot(UNIFORM_TEXTURE_DEPTH_MAP, MainRender.depthMap);
	//SetTextureSlot(UNIFORM_TEXTURE_DEFERRED_POSITIONS, DeferredPositions.colorMap);
	SetTextureSlot(UNIFORM_TEXTURE_DEFERRED_NORMALS, DeferredNormals.colorMap);
	PostProcess(UNIFORM_FLAG_POSTPROCESS_AMBIENTOCCLUSION);
	
	AmbientOcclusion.unload();
#if 1
	AmbientOcclusionBilateral.load();

	SetTextureSlot(UNIFORM_TEXTURE_COLOR_MAP, AmbientOcclusion.colorMap);
	PostProcess(UNIFORM_FLAG_POSTPROCESS_BILATERAL_GUASSIAN);

	AmbientOcclusionBilateral.unload();
#endif
}
void RenderGUILayer()
{
	ResetUniforms();
	GUILayer.load();
	
	SetUniform(UNIFORM_FLAG_BLIT_RENDER);
	
	for (uint i = 0; i < ActiveGUI.length(); i++) DrawGUI(ActiveGUI[i]);

	GUILayer.unload();
}

void FinalRender()
{
	ResetUniforms();
#if 1
	SetTextureSlot(UNIFORM_TEXTURE_LUMINANCE_MAP, Luminance.colorMap);
	SetTextureSlot(UNIFORM_TEXTURE_AMBIENTOCCLUSION_MAP, AmbientOcclusionBilateral.colorMap);
	SetTextureSlot(UNIFORM_TEXTURE_GUI_LAYER_MAP, GUILayer.colorMap);
	SetTextureSlot(UNIFORM_TEXTURE_COLOR_MAP, MainRender.colorMap);
	PostProcess(UNIFORM_FLAG_POSTPROCESS_FINAL_RENDER);
#else
	MainRender.blit();
#endif
}

HEX_END
#endif