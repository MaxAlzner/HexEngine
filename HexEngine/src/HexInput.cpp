#include "..\include\HexMain.h"

#ifdef _HEX_INPUT_H_
HEX_BEGIN
	
void OnMouseMove(unsigned x, unsigned y)
{
}
void OnKeyDown(char code)
{
	switch (code)
	{
	case SDLK_ESCAPE:
		AppRunning = false;
		break;
	default:
		break;
	}
}
void OnKeyUp(char code)
{
}
	
HEX_END
#endif