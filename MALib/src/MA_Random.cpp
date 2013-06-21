#include "..\include\MALib.h"

#ifdef _MA_RANDOM_H_
_MALIB_BEGIN

MALIB_API unsigned RANDOM_SEED = 0;

MALIB_API void RANDOM_Initialize()
{
	RANDOM_SEED = (unsigned)time(NULL);
	srand(RANDOM_SEED);
}

MALIB_API int RANDOM_Range(int min, int max)
{
	return Interp(RANDOM_Scalar(), min, max);
}
MALIB_API unsigned RANDOM_Range(unsigned min, unsigned max)
{
	return Interp(RANDOM_Scalar(), min, max);
}
MALIB_API float RANDOM_Range(float min, float max)
{
	return Interp(RANDOM_Scalar(), min, max);
}
MALIB_API double RANDOM_Range(double min, double max)
{
	return Interp(RANDOM_Scalar(), min, max);
}

MALIB_API unsigned RANDOM_D100()
{
	return (rand() % 100) + 1;
}
MALIB_API unsigned RANDOM_D50()
{
	return (rand() % 50) + 1;
}
MALIB_API unsigned RANDOM_D32()
{
	return (rand() % 32) + 1;
}
MALIB_API unsigned RANDOM_D24()
{
	return (rand() % 24) + 1;
}
MALIB_API unsigned RANDOM_D20()
{
	return (rand() % 20) + 1;
}
MALIB_API unsigned RANDOM_D16()
{
	return (rand() % 16) + 1;
}
MALIB_API unsigned RANDOM_D10()
{
	return (rand() % 10) + 1;
}
MALIB_API unsigned RANDOM_D8()
{
	return (rand() % 8) + 1;
}
MALIB_API unsigned RANDOM_D6()
{
	return (rand() % 6) + 1;
}
MALIB_API unsigned RANDOM_D4()
{
	return (rand() % 4) + 1;
}
MALIB_API unsigned RANDOM_D3()
{
	return (rand() % 3) + 1;
}
MALIB_API bool RANDOM_Coin()
{
	if (rand() % 2 == 0) return true;
	return false;
}
MALIB_API float RANDOM_Scalar()
{
	return float(rand() % 10000) / 10000.0f;
}

_MALIB_END
#endif