#pragma once

#include <Windows.h>

#define MALIB_EXPORTS

#if _WIN32
#ifdef MALIB_EXPORTS
#define MALIB_API __declspec(dllexport)
#else
#define MALIB_API __declspec(dllimport)
#endif
#else
#define MALIB_API 
#endif

#define _MALIB_BEGIN namespace MALib {
#define _MALIB_END }

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ulonglong;
typedef char* string;

#include "MA_Array.h"
#include "MA_List.h"
#include "MA_HashTable.h"

#include "MA_Math.h"
#include "MA_Rect.h"
#include "MA_Random.h"
#include "MA_Drawing.h"

#include "MA_File.h"
#include "MA_Log.h"
#include "MA_Counter.h"
#include "MA_Color.h"
#include "MA_Vertex.h"
#include "MA_Matrix.h"

#include "MA_Surface.h"
#include "MA_VertexBuffer.h"
#include "MA_OBJ.h"
