#ifndef _MA_LOG_H_
#define _MA_LOG_H_
_MALIB_BEGIN

#ifndef _INC_STDIO
#include <stdio.h>
#endif
#ifndef _INC_TIME
#include <time.h>
#endif

MALIB_API void LOG_Initialize(bool cleanFile = false);
MALIB_API void LOG_Unitialize();

MALIB_API void LOG_Message(const char* str);
MALIB_API void LOG_Message(const char* prefix, const char* str);
MALIB_API void LOG_Out1f(const char* prefix, float v0);
MALIB_API void LOG_Out2f(const char* prefix, float v0, float v1);
MALIB_API void LOG_Out3f(const char* prefix, float v0, float v1, float v2);
MALIB_API void LOG_Out4f(const char* prefix, float v0, float v1, float v2, float v3);
MALIB_API void LOG_Outvf(const char* prefix, float* v, unsigned size);
MALIB_API void LOG_Out1i(const char* prefix, int v0);
MALIB_API void LOG_Out2i(const char* prefix, int v0, int v1);
MALIB_API void LOG_Out3i(const char* prefix, int v0, int v1, int v2);
MALIB_API void LOG_Out4i(const char* prefix, int v0, int v1, int v2, int v3);
MALIB_API void LOG_Outvi(const char* prefix, int* v, unsigned size);
MALIB_API void LOG_Out1ch(const char* prefix, char v0);
MALIB_API void LOG_Out2ch(const char* prefix, char v0, char v1);
MALIB_API void LOG_Out3ch(const char* prefix, char v0, char v1, char v2);
MALIB_API void LOG_Out4ch(const char* prefix, char v0, char v1, char v2, char v3);
MALIB_API void LOG_Outvch(const char* prefix, char* v, unsigned size);
MALIB_API void LOG_Out1ptr(const char* prefix, void* v0);
MALIB_API void LOG_Out2ptr(const char* prefix, void* v0, void* v1);
MALIB_API void LOG_Out3ptr(const char* prefix, void* v0, void* v1, void* v2);
MALIB_API void LOG_Out4ptr(const char* prefix, void* v0, void* v1, void* v2, void* v3);
MALIB_API void LOG_Outvptr(const char* prefix, void** v, unsigned size);
MALIB_API void LOG_Out1Bool(const char* prefix, bool v0);
MALIB_API void LOG_Out2Bool(const char* prefix, bool v0, bool v1);
MALIB_API void LOG_Out3Bool(const char* prefix, bool v0, bool v1, bool v2);
MALIB_API void LOG_Out4Bool(const char* prefix, bool v0, bool v1, bool v2, bool v3);
MALIB_API void LOG_OutvBool(const char* prefix, bool* v, unsigned size);

extern MALIB_API FILE* LOG_FILE;

_MALIB_END
#endif