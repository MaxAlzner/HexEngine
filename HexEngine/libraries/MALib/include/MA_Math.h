#ifndef _MA_MATH_H_
#define _MA_MATH_H_
_MALIB_BEGIN

#ifndef NULL
#define NULL 0
#endif

extern MALIB_API const float PI;
	
MALIB_API int Clamp(int x, int min = 0, int max = 1);
MALIB_API unsigned Clamp(unsigned x, unsigned min = 0, unsigned max = 1);
MALIB_API float Clamp(float x, float min = 0.0f, float max = 1.0f);
MALIB_API double Clamp(double x, double min = 0.0, double max = 1.0);

MALIB_API float Module(float x, float denominator = 1.0f);
MALIB_API double Module(double x, double denominator = 1.0);

MALIB_API void Swap(int& x, int& y);
MALIB_API void Swap(unsigned& x, unsigned& y);
MALIB_API void Swap(float& x, float& y);
MALIB_API void Swap(double& x, double& y);

MALIB_API int Interp(float percent, int min, int max);
MALIB_API unsigned Interp(float percent, unsigned min, unsigned max);
MALIB_API float Interp(float percent, float min, float max);
MALIB_API double Interp(float percent, double min, double max);

MALIB_API void Clip(int& x, int& y, int x0, int y0, int x1, int y1);
MALIB_API void Clip(unsigned& x, unsigned& y, unsigned x0, unsigned y0, unsigned x1, unsigned y1);
MALIB_API void Clip(float& x, float& y, float x0, float y0, float x1, float y1);
MALIB_API void Clip(double& x, double& y, double x0, double y0, double x1, double y1);

MALIB_API int Sign(int x);
MALIB_API int Sign(float x);
MALIB_API int Sign(double x);

MALIB_API float ToRadians(float angle);
MALIB_API float ToDegrees(float angle);

MALIB_API int Max(int x, int y);
MALIB_API int Max(int x, int y, int z);
MALIB_API unsigned Max(unsigned x, unsigned y);
MALIB_API unsigned Max(unsigned x, unsigned y, unsigned z);
MALIB_API float Max(float x, float y);
MALIB_API float Max(float x, float y, float z);
MALIB_API double Max(double x, double y);
MALIB_API double Max(double x, double y, double z);

MALIB_API int Min(int x, int y);
MALIB_API int Min(int x, int y, int z);
MALIB_API unsigned Min(unsigned x, unsigned y);
MALIB_API unsigned Min(unsigned x, unsigned y, unsigned z);
MALIB_API float Min(float x, float y);
MALIB_API float Min(float x, float y, float z);
MALIB_API double Min(double x, double y);
MALIB_API double Min(double x, double y, double z);

_MALIB_END
#endif