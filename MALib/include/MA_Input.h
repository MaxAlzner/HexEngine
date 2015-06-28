#ifndef _MA_INPUT_H_
#define _MA_INPUT_H_
_MALIB_BEGIN

namespace INPUT
{
	MALIB_API extern MouseInput MOUSE;
	MALIB_API extern KeyInput KEY;
	MALIB_API extern GamepadInput GAMEPAD;

	MALIB_API extern float GetAxis(AxisCode axis, float deadzone = 0.4f);
	MALIB_API extern float GetTrigger(AxisCode trigger, float deadzone = 0.4f);
	MALIB_API extern bool GetButton(ButtonCode button, bool latch = false);
	MALIB_API extern bool IsButtonDown(ButtonCode button);
	MALIB_API extern bool IsButtonUp(ButtonCode button);
	MALIB_API extern bool GetKey(KeyCode code, bool latch = false);
	MALIB_API extern bool GetKey(uchar code, bool latch = false);
	MALIB_API extern bool IsKeyDown(KeyCode code);
	MALIB_API extern bool IsKeyDown(uchar code);
	MALIB_API extern bool IsKeyUp(KeyCode code);
	MALIB_API extern bool IsKeyUp(uchar code);
	
	MALIB_API extern void OnMouseMove(uint width, uint height, uint x, uint y);
	MALIB_API extern void OnMouseActive(bool state);
	MALIB_API extern void OnMouseButtonDown(MouseButton button);
	MALIB_API extern void OnMouseButtonUp(MouseButton button);
	MALIB_API extern void OnMouseButton(MouseButton button, bool state);
	MALIB_API extern void OnKeyDown(KeyCode code);
	MALIB_API extern void OnKeyDown(uchar code);
	MALIB_API extern void OnKeyUp(KeyCode code);
	MALIB_API extern void OnKeyUp(uchar code);
	MALIB_API extern void OnKey(KeyCode code, bool state);
	MALIB_API extern void OnKey(uchar code, bool state);
	MALIB_API extern void OnControllerAxis(AxisCode axis, long value);
	MALIB_API extern void OnControllerButtonDown(ButtonCode button);
	MALIB_API extern void OnControllerButtonUp(ButtonCode button);
	MALIB_API extern void OnControllerButton(ButtonCode button, bool state);
}

_MALIB_END
#endif