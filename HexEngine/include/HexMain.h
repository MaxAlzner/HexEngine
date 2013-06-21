#pragma once

#pragma comment( lib, "SDL.lib" )
#pragma comment( lib, "SDLmain.lib" )

#include <stdlib.h>
#include <stdarg.h>
#include <string>
#include <math.h>
#include <time.h>

#include <Windows.h>

#include <glew.h>
#include <SDL.h>

#include <MALib.h>

#include "..\libraries\glm\glm.hpp"
#include "..\libraries\glm\gtc\matrix_transform.hpp"
#include "..\libraries\glm\gtc\type_ptr.hpp"
#include "..\libraries\glm\gtc\constants.hpp"

#define HEX_BEGIN namespace HEX\
	{\
	class HexEntity;
#define HEX_END }

#include "nodes\NodeBase.h"
#include "nodes\ShapeNode.h"
#include "nodes\MaterialNode.h"

#include "core\HexTimer.h"
#include "core\HexInput.h"
#include "core\HexShader.h"
#include "core\HexCore.h"