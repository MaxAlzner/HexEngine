#include "..\include\HexMain.h"

#ifdef _HEX_TIMER_H_
HEX_BEGIN

#define HEX_FRAMERATE 60

float DeltaTime = 0.0f;
unsigned CurrentFrame = 1;

static Uint32 LastPing = 0;

Uint32 Timer_FrameUpdate(Uint32 interval, void *param)
{
	CurrentFrame++;
	if (CurrentFrame >= 60) CurrentFrame = 1;

	Uint32 NewPing = SDL_GetTicks();
	DeltaTime = float(NewPing - LastPing) / 1000.0f;
	LastPing = NewPing;

	return interval;
}
Uint32 Timer_FixedUpdate(Uint32 interval, void *param)
{
	return interval;
}
	
HEX_END
#endif