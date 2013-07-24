#pragma once

#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")

#include <stdlib.h>
#include <stdarg.h>
#include <string>
#include <math.h>
#include <time.h>

#include <Windows.h>

#include <glew.h>
#include <SDL.h>

#include <MALib.h>

#include "..\libraries\glm\ext.hpp"

#include "core\HexDef.h"
#include "core\HexInputDef.h"

#include "nodes\NodeBase.h"
#include "nodes\TransformNode.h"
#include "nodes\MaterialNode.h"
#include "nodes\ComponentNode.h"
#include "nodes\ShapeNode.h"
#include "nodes\CameraNode.h"
#include "nodes\LightNode.h"
#include "nodes\ControlNode.h"
#include "nodes\SkyboxNode.h"

#include "core\HexEntity.h"
#include "core\HexInput.h"
#include "core\HexShader.h"
#include "core\HexRender.h"
#include "core\HexData.h"
#include "core\HexCore.h"