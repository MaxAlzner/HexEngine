
#include "..\include\MALib.h"

int main()
{
	MALib::LOG_Initialize(true);
	MALib::RANDOM_Initialize();

	MALib::SURFACE* s = new MALib::SURFACE("test image", 512, 512, MALib::PIXELFORMAT_RGBA);
	MALib::SURFACE* b = new MALib::SURFACE("test image", 64, 64, MALib::PIXELFORMAT_RGBA);

	MALib::DrawCircle(s, 128, 128, 48, 0xFF2255FF);
	MALib::DrawBox(s, 156, 32, 256, 160, 0x25BF0288);
	MALib::DrawLine(s, 24, 24, 384, 480, 0x118899AA);
	MALib::ClearBitmap(b, 0xDEADBEEF);
	MALib::DrawCircle(b, 32, 32, 32, 0xBA2357BB);
	MALib::DrawBitmap(s, b, 160, 148);

	MALib::ExportBMPFile("testDraw.bmp", s);
	MALib::ExportTGAFile("testDraw.tga", s);
	MALib::FreeSurface(&s);

	MALib::LOG_Unitialize();
	return 0;
}