#ifndef _HEX_DRAW_H_
#define _HEX_DRAW_H_
HEX_BEGIN

extern HexRender MainRender;
extern HexRender BrightPass;
extern HexRender Luminance;
extern HexRender DeferredPositions;
extern HexRender DeferredNormals;
extern HexRender AmbientOcclusion;
extern HexRender AmbientOcclusionBilateral;
extern HexRender LeftEye;
extern HexRender RightEye;
extern HexRender GUILayer;
	
HEX_API extern bool InitializeDraw();
HEX_API extern bool UninitializeDraw();

HEX_API extern bool StartDrawing();

extern void RenderMain();
extern void RenderShadowMap();
extern void RenderLuminance();
extern void RenderDeferredPositions();
extern void RenderDeferredNormals();
extern void RenderAmbientOcclusion();
extern void RenderGUILayer();

extern void FinalRender();
	
HEX_END
#endif