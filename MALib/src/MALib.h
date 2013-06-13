#pragma once

#include <Windows.h>

//#define DllI __declspec(dllimport)
//#define DllE __declspec(dllexport)

#ifdef MALIB_EXPORTS
#define MALIB_API __declspec(dllexport)
#else
#define MALIB_API __declspec(dllimport)
#endif

MALIB_API void test();
