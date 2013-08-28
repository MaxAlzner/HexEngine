
#include "..\include\HexMain.h"

int main(int argc, char **argv)
{
	if (!HEX::Initialize(argc, argv)) 
		HEX::ToggleRunning();

	HEX::SetFontSheet("data/fontsheet.bmp", 16, 16);
	HEX::AddGUIText(MALib::RECT(80, 8, 480, 240), "TEST");

	HEX::OnStart();

	HEX::Uninitialize();
	return 0;
}