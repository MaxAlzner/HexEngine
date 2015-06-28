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

MALIB_API void LOG_Message(const string str);
MALIB_API void LOG_Message(const string prefix, const string str);
MALIB_API void LOG_Out1f(const string prefix, float v0);
MALIB_API void LOG_Out2f(const string prefix, float v0, float v1);
MALIB_API void LOG_Out3f(const string prefix, float v0, float v1, float v2);
MALIB_API void LOG_Out4f(const string prefix, float v0, float v1, float v2, float v3);
MALIB_API void LOG_Outvf(const string prefix, float* v, uint size);
MALIB_API void LOG_Out1i(const string prefix, int v0);
MALIB_API void LOG_Out2i(const string prefix, int v0, int v1);
MALIB_API void LOG_Out3i(const string prefix, int v0, int v1, int v2);
MALIB_API void LOG_Out4i(const string prefix, int v0, int v1, int v2, int v3);
MALIB_API void LOG_Outvi(const string prefix, int* v, uint size);
MALIB_API void LOG_Out1ch(const string prefix, char v0);
MALIB_API void LOG_Out2ch(const string prefix, char v0, char v1);
MALIB_API void LOG_Out3ch(const string prefix, char v0, char v1, char v2);
MALIB_API void LOG_Out4ch(const string prefix, char v0, char v1, char v2, char v3);
MALIB_API void LOG_Outvch(const string prefix, string v, uint size);
MALIB_API void LOG_Out1ptr(const string prefix, void* v0);
MALIB_API void LOG_Out2ptr(const string prefix, void* v0, void* v1);
MALIB_API void LOG_Out3ptr(const string prefix, void* v0, void* v1, void* v2);
MALIB_API void LOG_Out4ptr(const string prefix, void* v0, void* v1, void* v2, void* v3);
MALIB_API void LOG_Outvptr(const string prefix, void** v, uint size);
MALIB_API void LOG_Out1Bool(const string prefix, bool v0);
MALIB_API void LOG_Out2Bool(const string prefix, bool v0, bool v1);
MALIB_API void LOG_Out3Bool(const string prefix, bool v0, bool v1, bool v2);
MALIB_API void LOG_Out4Bool(const string prefix, bool v0, bool v1, bool v2, bool v3);
MALIB_API void LOG_OutvBool(const string prefix, bool* v, uint size);

MALIB_API void LOG_File(TEXTFILE* file);

_MALIB_END
#endif