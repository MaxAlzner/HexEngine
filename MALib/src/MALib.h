#pragma once

#include <Windows.h>

/*#ifdef MALIB_EXPORTS
#define MALIB_API __declspec(dllexport)
#else
#define MALIB_API __declspec(dllimport)
#endif*/
#define MALIB_API __declspec(dllexport)

#include "Array.h"
#include "List.h"
#include "HashTable.h"

//#include "Fuzzy.h"
