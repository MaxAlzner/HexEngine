#ifndef _HEX_RENDER_H_
#define _HEX_RENDER_H_
HEX_BEGIN

class HexRender
{
public:

	HexRender();
	~HexRender();

	void build(uint width, uint height, bool attachColor = true, bool attachDepth = true);
	void load();
	void unload();
	void destroy();

	void blit(HexRender* dest = NULL);

	MALib::RECT dimensions;
	MALib::RECT view;
	uint framebuffer;
	uint colorMap;
	uint depthMap;
	MALib::COLOR clear;
};

extern uint ScreenVAO;
extern uint ScreenBuffer;

extern void InitializePostProcess();
extern void UninitializePostProcess();

extern void PostProcess(UNIFORM flag);

HEX_END
#endif