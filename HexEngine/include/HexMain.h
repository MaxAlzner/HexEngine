#pragma once

#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")

#include <stdlib.h>
#include <stdarg.h>
#include <string>
#include <math.h>
#include <time.h>

#include <Windows.h>

/*#include <ft2build.h>
#include <freetype.h>
#include <ftglyph.h>
#include <ftoutln.h>
#include <fttrigon.h>*/

#include <glew.h>
#include <SDL.h>
#include <SDL_ttf.h>

#include <MALib.h>

#include "..\libraries\glm\ext.hpp"

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ulonglong;
typedef char* string;

#define HEX_API __declspec(dllexport)
#define USING_GLM_API 

#define HEX_BEGIN namespace HEX\
	{\
		class HexEntity;
#define HEX_END }

#include "nodes\NodeBase.h"
#include "nodes\TransformNode.h"
#include "nodes\MaterialNode.h"
#include "nodes\ComponentNode.h"
#include "nodes\ShapeNode.h"
#include "nodes\CameraNode.h"
#include "nodes\LightNode.h"

#include "core\HexEntity.h"
#include "core\HexTimer.h"
#include "core\HexInput.h"
#include "core\HexShader.h"
#include "core\HexData.h"
#include "core\HexText.h"
#include "core\HexCore.h"