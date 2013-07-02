#ifndef _HEX_INPUT_H_
#define _HEX_INPUT_H_
HEX_BEGIN

typedef struct MouseInput
{
	uint x;
	uint y;
	int deltaX;
	int deltaY;
	float scalarX;
	float scalarY;

	bool left;
	bool right;
	bool middle;
} MouseInput;
typedef struct KeyInput
{
	bool pressed[256];
	bool latched[256];
} KeyInput;
typedef struct ControllerInput
{
	float axis[8];
	bool buttons[16];
	bool dpad[16];
} ControllerInput;

namespace Input
{
	HEX_API extern MouseInput mouse;
	HEX_API extern KeyInput key;
	HEX_API extern ControllerInput controller;

	HEX_API extern float GetAxis(const string axis);
	HEX_API extern float GetTrigger(const string trigger);
	HEX_API extern bool GetButton(const string button);
	HEX_API extern bool IsButtonDown(const string button);
	HEX_API extern bool IsButtonUp(const string button);
	HEX_API extern bool GetKey(uchar code);
	HEX_API extern bool IsKeyDown(uchar button);
	HEX_API extern bool IsKeyUp(uchar button);
}

HEX_API extern SDL_Joystick* GamePad;

HEX_API extern void InitializeInput();
HEX_API extern void UninitializeInput();
	
HEX_API extern void PollEvents();

HEX_API extern void OnMouseMove(uint x, uint y);
HEX_API extern void OnButtonDown(uchar button);
HEX_API extern void OnButtonUp(uchar button);
HEX_API extern void OnKeyDown(uchar code);
HEX_API extern void OnKeyUp(uchar code);
HEX_API extern void OnAxis(uchar axis, long value);
	
HEX_END
#endif