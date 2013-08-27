
#include "..\include\HexMain.h"

int main(int argc, char **argv)
{
	if (!HEX::Initialize(argc, argv)) 
		HEX::ToggleRunning();

	HEX::AddGUIText(MALib::RECT(80, 8, 320, 240), "TEST");

	HEX::OnStart();

	HEX::Uninitialize();
	return 0;
}