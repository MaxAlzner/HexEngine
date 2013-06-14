#ifndef _MA_LOG_H_
#define _MA_LOG_H_

#ifndef _INC_STDIO
#include <stdio.h>
#endif

class LOG
{
public:

	static MALIB_API void Initialize();
	static MALIB_API void Unitialize();

	static MALIB_API void Message(const char* str);
	static MALIB_API void Message(const char* prefix, const char* str);
	static MALIB_API void Out1f(const char* prefix, float v0);
	static MALIB_API void Out2f(const char* prefix, float v0, float v1);
	static MALIB_API void Out3f(const char* prefix, float v0, float v1, float v2);
	static MALIB_API void Out4f(const char* prefix, float v0, float v1, float v2, float v3);
	static MALIB_API void Out1i(const char* prefix, int v0);
	static MALIB_API void Out2i(const char* prefix, int v0, int v1);
	static MALIB_API void Out3i(const char* prefix, int v0, int v1, int v2);
	static MALIB_API void Out4i(const char* prefix, int v0, int v1, int v2, int v3);
	static MALIB_API void Out1ptr(const char* prefix, void* v0);
	static MALIB_API void Out2ptr(const char* prefix, void* v0, void* v1);
	static MALIB_API void Out3ptr(const char* prefix, void* v0, void* v1, void* v2);
	static MALIB_API void Out4ptr(const char* prefix, void* v0, void* v1, void* v2, void* v3);
	static MALIB_API void OutBool(const char* prefix, bool v);

	static MALIB_API FILE* file;

private:

	static MALIB_API void Ticks();
};

#endif