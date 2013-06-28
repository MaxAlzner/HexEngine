#ifndef _HEX_CORE_H_
#define _HEX_CORE_H_
HEX_BEGIN

HEX_API extern void OnFrameDraw();
HEX_API extern void OnFrameUpdate();
HEX_API extern void OnFixedUpdate();

HEX_API extern bool Reshape(unsigned width, unsigned height);
HEX_API extern bool Initialize(unsigned argc, char **argv);
HEX_API extern bool Unitialize();

HEX_END
#endif