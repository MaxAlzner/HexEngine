#ifndef _HEX_INPUT_H_
#define _HEX_INPUT_H_
HEX_BEGIN
	
HEX_API extern void PollEvents();

HEX_API extern void OnMouseMove(unsigned x, unsigned y);
HEX_API extern void OnKeyDown(char code);
HEX_API extern void OnKeyUp(char code);
	
HEX_END
#endif