
#include <stdio.h>
#include "..\include\MALib.h"

int main()
{
	MALib::LOG_Initialize(true);
	MALib::RANDOM_Initialize();

	MALib::RECT r1(24, 24, 320, 320);
	MALib::RECT r2(1, 4, 32, 21);
	MALib::RECT r3(280, 150, 340, 180);
	MALib::RECT r4(48, 60, 300, 280);

	MALib::LOG_Out1Bool("RECT TEST SHOULD BE FALSE",  MALib::Clipping(r1, r2));
	MALib::LOG_Out1Bool("RECT TEST SHOULD BE TRUE ",  MALib::Clipping(r1, r3));
	MALib::LOG_Out1Bool("RECT TEST SHOULD BE TRUE ",  MALib::Clipping(r1, r4));
	
	MALib::LOG_Out1Bool("RECT TEST SHOULD BE FALSE",  MALib::InsideRect(r1, MALib::POINT(1, 23)));
	MALib::LOG_Out1Bool("RECT TEST SHOULD BE TRUE ",  MALib::InsideRect(r1, MALib::POINT(190, 320)));

	MALib::POINT p1 = MALib::Displacement(r1, MALib::RECT(480, 24, 560, 380));
	MALib::POINT p2 = MALib::Displacement(r1, MALib::RECT(-128, 2, 80, -240));
	MALib::LOG_Out2i("DISLPACEMENT TEXT", p1.x, p1.y);
	MALib::LOG_Out2i("DISLPACEMENT TEXT", p2.x, p2.y);

	r1.resize(120, 120);

	bool t1 = MALib::INPUT::MOUSE.left;

	MALib::SURFACE* s = 0;
	MALib::CreateSurface(&s, "", 10200, 6600, MALib::PIXELFORMAT_BGR, 0);
	//MALib::ExportBMPFile("test_big.bmp", s);
	MALib::FreeSurface(&s);
	
	MALib::LOG_Out1i("2 POW 2", MALib::Pow(2u, 2u));
	MALib::LOG_Out1i("3 POW 4", MALib::Pow(3u, 4u));
	MALib::LOG_Out1i("9 POW 0", MALib::Pow(9, 0u));
	MALib::LOG_Out1i("-4 POW 3", MALib::Pow(-4, 3u));
	MALib::LOG_Out1f("2, 2 MAGNITUDE", MALib::Magnitude(MALib::POINT(2, 2)));
	MALib::LOG_Out1f("0, -4 MAGNITUDE", MALib::Magnitude(MALib::POINT(0, -4)));
	MALib::LOG_Out1f("(2, 2) (7, 4) DISTANCE", MALib::Distance(MALib::POINT(2, 2), MALib::POINT(7, 4)));
	MALib::LOG_Out1f("(-3, 2) (-6, 0) DISTANCE", MALib::Distance(MALib::POINT(-3, 2), MALib::POINT(-6, 0)));

	MALib::LOG_Unitialize();
	return 0;
}