
#include "..\include\HexMain.h"

int main(int argc, char **argv)
{
	if (!HEX::Initialize(argc, argv)) 
		HEX::ToggleRunning();
	
	Uint32 FramePing = SDL_GetTicks();
	Uint32 UpdatePing = SDL_GetTicks();
	while (HEX::IsRunning())
	{
		HEX::PollEvents();
		
		Uint32 NewPing = SDL_GetTicks();
		if (NewPing - FramePing > 16)
		{
			HEX::OnFrameUpdate();
			HEX::OnFrameDraw();
			FramePing = NewPing;
		}
		if (NewPing - UpdatePing > 24)
		{
			HEX::OnFixedUpdate();
			UpdatePing = NewPing;
		}
	}
	
	HEX::Unitialize();
	return 0;
}