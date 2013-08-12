#ifndef _HEX_DRAW_H_
#define _HEX_DRAW_H_
HEX_BEGIN

extern HexRender MainRender;
extern HexRender ShadowMap;
extern HexRender BrightPass;
extern HexRender Luminance;
extern HexRender DeferredPositions;
extern HexRender DeferredNormals;
extern HexRender AmbientOcclusion;
extern HexRender AmbientOcclusionBilateral;
	
HEX_API extern bool InitializeDraw();
HEX_API extern bool UninitializeDraw();

HEX_API extern void StartDrawing();
	
HEX_END
#endif