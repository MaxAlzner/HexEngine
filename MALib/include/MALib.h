#pragma once

#include <Windows.h>

/*#ifdef MALIB_EXPORTS
#define MALIB_API __declspec(dllexport)
#else
#define MALIB_API __declspec(dllimport)
#endif*/
#define MALIB_API __declspec(dllexport)

#include "MA_Array.h"
#include "MA_List.h"
#include "MA_HashTable.h"
