#ifndef _HEX_INPUT_H_
#define _HEX_INPUT_H_
HEX_BEGIN

#ifndef _HEX_INPUTDEF_H_
#include "HexInputDef.h"
#endif

extern SDL_Joystick* GamePad;

namespace Input
{
	HEX_API extern MouseInput mouse;
	HEX_API extern KeyInput key;
	HEX_API extern ControllerInput controller;

	HEX_API extern float GetAxis(uint axis, float deadzone = 0.4f);
	HEX_API extern float GetTrigger(uint trigger, float deadzone = 0.4f);
	HEX_API extern bool GetButton(uint button, bool latch = false);
	HEX_API extern bool IsButtonDown(uint button);
	HEX_API extern bool IsButtonUp(uint button);
	HEX_API extern bool GetKey(KeyCode code, bool latch = false);
	HEX_API extern bool GetKey(uchar code, bool latch = false);
	HEX_API extern bool IsKeyDown(KeyCode code);
	HEX_API extern bool IsKeyDown(uchar code);
	HEX_API extern bool IsKeyUp(KeyCode code);
	HEX_API extern bool IsKeyUp(uchar code);
}

HEX_API extern void InitializeInput();
HEX_API extern void UninitializeInput();
	
HEX_API extern void PollEvents();
HEX_API extern void PollControllers();

HEX_API extern void OnMouseMove(uint x, uint y);
HEX_API extern void OnMouseButtonDown(uchar button);
HEX_API extern void OnMouseButtonUp(uchar button);
HEX_API extern void OnKeyDown(KeyCode code);
HEX_API extern void OnKeyUp(KeyCode code);
HEX_API extern void OnControllerAxis(uchar axis, long value);
HEX_API extern void OnControllerButtonDown(uchar button);
HEX_API extern void OnControllerButtonUp(uchar button);
	
HEX_END
#endif