
#include "..\include\HexMain.h"

int main(int argc, char **argv)
{
	if (!HEX::Initialize(argc, argv)) 
		HEX::ToggleRunning();
	
	Uint32 LastPing = SDL_GetTicks();
	while (HEX::IsRunning())
	{
		HEX::PollEvents();
		
		Uint32 NewPing = SDL_GetTicks();
		Uint32 Delta = NewPing - LastPing;
		if (Delta > 24)
		{
			HEX::OnFrameUpdate();
			HEX::OnFrameDraw();
			LastPing = NewPing;
		}
	}

	
	HEX::Unitialize();
	return 0;
}