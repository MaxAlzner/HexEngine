
#include "..\include\HexMain.h"

void Listen(SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		HEX::OnKeyDown(event.key.keysym.sym);
		break;
	case SDL_KEYUP:
		HEX::OnKeyUp(event.key.keysym.sym);
		break;
	case SDL_MOUSEMOTION:
		HEX::OnMouseMove(event.motion.x, event.motion.y);
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
		HEX::AppRunning = false;
		break;
	case SDL_VIDEORESIZE:
		HEX::Reshape(event.resize.w, event.resize.h);
		break;
	default:
		break;
	}
}
int main(int argc, char **argv)
{
	if (!HEX::Initialize(argc, argv))
	{
		MALib::LOG_Message("Initialization failed.");
		HEX::AppRunning = false;
	}
	
	Uint32 LastPing = SDL_GetTicks();
	while(HEX::AppRunning)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event)) 
			Listen(event);
		
		Uint32 NewPing = SDL_GetTicks();
		Uint32 delta = NewPing - LastPing;
		if (delta > 24)
		{
			HEX::OnFrameUpdate();
			HEX::OnFrameDraw();
			LastPing = NewPing;
		}
	}

	if (!HEX::Unitialize())
	{
		MALib::LOG_Message("Uninitialization failed.");
	}

	return 0;
}