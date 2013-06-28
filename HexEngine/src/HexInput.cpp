#include "..\include\HexMain.h"

#ifdef _HEX_INPUT_H_
HEX_BEGIN
	
HEX_API void PollEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			OnKeyDown(event.key.keysym.sym);
			break;
		case SDL_KEYUP:
			OnKeyUp(event.key.keysym.sym);
			break;

		case SDL_MOUSEMOTION:
			OnMouseMove(event.motion.x, event.motion.y);
			break;
		case SDL_MOUSEBUTTONDOWN:
			break;
		case SDL_MOUSEBUTTONUP:
			break;

		case SDL_JOYAXISMOTION:
			break;
		case SDL_JOYBUTTONDOWN:
			break;
		case SDL_JOYBUTTONUP:
			break;

		case SDL_QUIT:
			AppRunning = false;
			break;
		case SDL_VIDEORESIZE:
			Reshape(event.resize.w, event.resize.h);
			break;

		default:
			break;
		}
	}
}

HEX_API void OnMouseMove(unsigned x, unsigned y)
{
}
HEX_API void OnKeyDown(char code)
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
HEX_API void OnKeyUp(char code)
{
}
	
HEX_END
#endif