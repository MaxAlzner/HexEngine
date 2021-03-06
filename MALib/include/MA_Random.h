#ifndef _MA_RANDOM_H_
#define _MA_RANDOM_H_
_MALIB_BEGIN

#ifndef _INC_STDLIB
#include <stdlib.h>
#endif
#ifndef _INC_TIME
#include <time.h>
#endif

MALIB_API void RANDOM_Initialize();

MALIB_API uint RANDOM_GetSeed();

MALIB_API int RANDOM_Range(int min, int max);
MALIB_API uint RANDOM_Range(uint min, uint max);
MALIB_API float RANDOM_Range(float min, float max);
MALIB_API double RANDOM_Range(double min, double max);

MALIB_API uint RANDOM_D100();
MALIB_API uint RANDOM_D50();
MALIB_API uint RANDOM_D32();
MALIB_API uint RANDOM_D24();
MALIB_API uint RANDOM_D20();
MALIB_API uint RANDOM_D16();
MALIB_API uint RANDOM_D10();
MALIB_API uint RANDOM_D8();
MALIB_API uint RANDOM_D6();
MALIB_API uint RANDOM_D4();
MALIB_API uint RANDOM_D3();
MALIB_API bool RANDOM_Coin();
MALIB_API float RANDOM_Scalar();

_MALIB_END
#endif