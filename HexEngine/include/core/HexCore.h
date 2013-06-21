#ifndef _HEX_CORE_H_
#define _HEX_CORE_H_
HEX_BEGIN

extern bool AppRunning;

extern void OnFrameDraw();
extern void OnFrameUpdate();
extern void OnFixedUpdate();

extern bool Reshape(unsigned width, unsigned height);
extern bool Initialize(unsigned argc, char **argv);
extern bool Unitialize();

HEX_END
#endif