
#include "..\include\HexMain.h"

int main(int argc, char **argv)
{
	if (!HEX::Initialize(argc, argv)) 
		HEX::ToggleRunning();

	HEX::OnStart();

	HEX::Uninitialize();
	return 0;
}