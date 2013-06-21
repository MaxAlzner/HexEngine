#ifndef _HEX_TIMER_H_
#define _HEX_TIMER_H_
HEX_BEGIN

extern float DeltaTime;
extern unsigned CurrentFrame;

extern Uint32 Timer_FrameUpdate(Uint32 interval, void *param);
extern Uint32 Timer_FixedUpdate(Uint32 interval, void *param);
	
HEX_END
#endif