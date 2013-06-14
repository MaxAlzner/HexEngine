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

#include "MA_Log.h"
#include "MA_Color.h"
#include "MA_Vertex.h"
#include "MA_Matrix.h"

#include "MA_OBJ.h"
