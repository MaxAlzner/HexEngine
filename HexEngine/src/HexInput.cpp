#include "..\include\HexMain.h"

#ifdef _HEX_INPUT_H_
HEX_BEGIN

SDL_Joystick* GamePad = 0;
	
HEX_API MouseInput Input::mouse;
HEX_API KeyInput Input::key;
HEX_API ControllerInput Input::controller;

HEX_API float Input::GetAxis(uint axis, float deadzone)
{
	if (Input::controller.connected && axis < CONTROLLER_AXIS_BUFFERSIZE)
	{
		float value = Input::controller.axis[axis];
		if (abs(value) < deadzone) value = 0.0f;
		return value;
	}
	return 0.0f;
}
HEX_API float Input::GetTrigger(uint trigger, float deadzone)
{
	if (Input::controller.connected && trigger < CONTROLLER_AXIS_BUFFERSIZE)
	{
		float value = Input::controller.axis[trigger];
		if (value < deadzone) value = 0.0f;
		return value;
	}
	return 0.0f;
}
HEX_API bool Input::GetButton(uint button, bool latch)
{
	if (Input::controller.connected && button < CONTROLLER_BUTTONS_BUFFERSIZE)
	{
		return false;
	}
	return false;
}
HEX_API bool Input::IsButtonDown(uint button)
{
	if (Input::controller.connected && button < CONTROLLER_BUTTONS_BUFFERSIZE)
	{
		return Input::controller.buttons[button];
	}
	return false;
}
HEX_API bool Input::IsButtonUp(uint button)
{
	if (Input::controller.connected && button < CONTROLLER_BUTTONS_BUFFERSIZE)
	{
		return !Input::controller.buttons[button];
	}
	return false;
}
HEX_API bool Input::GetKey(KeyCode code, bool latch)
{
	bool* value = Input::key.pressed + code;
	bool* latched = Input::key.latched + code;
	if (!latch)
	{
		return *value;
	}
	if (*latched)
	{
		if (!(*value))
		{
			*latched = false;
		}
		return false;
	}
	else
	{
		if (*value)
		{
			*latched = true;
			return true;
		}
		else
		{
			*latched = false;
		}
	}
	return false;
}
HEX_API bool Input::GetKey(uchar code, bool latch)
{
	return Input::GetKey((KeyCode)code, latch);
}
HEX_API bool Input::IsKeyDown(KeyCode code)
{
	return Input::key.pressed[code];
}
HEX_API bool Input::IsKeyDown(uchar code)
{
	return Input::IsKeyDown((KeyCode)code);
}
HEX_API bool Input::IsKeyUp(KeyCode code)
{
	return !Input::key.pressed[code];
}
HEX_API bool Input::IsKeyUp(uchar code)
{
	return Input::IsKeyUp((KeyCode)code);
}

HEX_API void InitializeInput()
{
	Input::mouse.active = true;
	for (uint i = 0; i < KEY_BUFFERSIZE; i++) Input::key.pressed[i] = false;
	for (uint i = 0; i < KEY_BUFFERSIZE; i++) Input::key.latched[i] = false;
	for (uint i = 0; i < CONTROLLER_AXIS_BUFFERSIZE; i++) Input::controller.axis[i] = 0.0f;
	for (uint i = 0; i < CONTROLLER_AXIS_BUFFERSIZE; i++) Input::controller.axisRaw[i] = 0;
	for (uint i = 0; i < CONTROLLER_BUTTONS_BUFFERSIZE; i++) Input::controller.buttons[i] = false;
	for (uint i = 0; i < CONTROLLER_DPAD_BUFFERSIZE; i++) Input::controller.dpad[i] = false;
	Input::controller.connected = false;
	
	SDL_JoystickEventState(SDL_ENABLE);
	PollControllers();
}
HEX_API void UninitializeInput()
{
	if (GamePad != NULL) SDL_JoystickClose(GamePad);
}
	
HEX_API void PollEvents()
{
	static SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			OnKeyDown((KeyCode)event.key.keysym.sym);
			break;
		case SDL_KEYUP:
			OnKeyUp((KeyCode)event.key.keysym.sym);
			break;

		case SDL_MOUSEMOTION:
			OnMouseMove(event.motion.x, event.motion.y);
			break;
		case SDL_MOUSEBUTTONDOWN:
			OnMouseButtonDown(event.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			OnMouseButtonUp(event.button.button);
			break;

		case SDL_JOYAXISMOTION:
			OnControllerAxis(event.jaxis.axis, event.jaxis.value);
			break;
		case SDL_JOYBUTTONDOWN:
			OnControllerButtonDown(event.jbutton.button);
			break;
		case SDL_JOYBUTTONUP:
			OnControllerButtonUp(event.jbutton.button);
			break;
			
		case SDL_ACTIVEEVENT:
			Input::mouse.active = bool(event.active.gain != 0);
			break;
		case SDL_QUIT:
			AppRunning = false;
			break;
		case SDL_VIDEORESIZE:
			if ((uint)event.resize.w != ScreenRect.width) 
				Reshape(event.resize.w, unsigned(float(event.resize.w) * pow(AspectRatio, -1)));
			else 
				Reshape(unsigned(float(event.resize.h) * AspectRatio), event.resize.h);
			break;

		default:
			break;
		}
	}
}
HEX_API void PollControllers()
{
	if (SDL_NumJoysticks() > 0)
	{
		if (GamePad != NULL) return;
		GamePad = SDL_JoystickOpen(0);
		Input::controller.connected = true;
	}
	else if (GamePad != NULL)
	{
		SDL_JoystickClose(GamePad);
		GamePad = NULL;
		Input::controller.connected = false;
	}
}

HEX_API void OnMouseMove(uint x, uint y)
{
	Input::mouse.deltaX = Input::mouse.x - x;
	Input::mouse.deltaY = Input::mouse.y - y;
	Input::mouse.x = x;
	Input::mouse.y = y;
	Input::mouse.scalarX = float(Input::mouse.x) / float(ScreenRect.width);
	Input::mouse.scalarY = float(Input::mouse.y) / float(ScreenRect.height);
	Input::mouse.scalarDeltaX = float(Input::mouse.deltaX) / float(ScreenRect.width);
	Input::mouse.scalarDeltaY = float(Input::mouse.deltaY) / float(ScreenRect.height);
}
HEX_API void OnMouseButtonDown(uchar button)
{
	switch (button)
	{
	case SDL_BUTTON_LEFT:
		Input::mouse.left = true;
		break;
	case SDL_BUTTON_MIDDLE:
		Input::mouse.middle = true;
		break;
	case SDL_BUTTON_RIGHT:
		Input::mouse.right = true;
		break;

	default:
		break;
	}
}
HEX_API void OnMouseButtonUp(uchar button)
{
	switch (button)
	{
	case SDL_BUTTON_LEFT:
		Input::mouse.left = false;
		break;
	case SDL_BUTTON_MIDDLE:
		Input::mouse.middle = false;
		break;
	case SDL_BUTTON_RIGHT:
		Input::mouse.right = false;
		break;

	default:
		break;
	}
}
HEX_API void OnKeyDown(KeyCode code)
{
	Input::key.pressed[code] = true;
}
HEX_API void OnKeyUp(KeyCode code)
{
	Input::key.pressed[code] = false;
}
HEX_API void OnControllerAxis(uchar axis, long value)
{
	switch (axis)
	{
	case XBOX_L_STICK_X:
		Input::controller.xboxAxis.leftStickX = XBOX_AXIS_RANGE(value);
		Input::controller.xboxAxisRaw.leftStickX = value;
		break;
	case XBOX_L_STICK_Y:
		Input::controller.xboxAxis.leftStickY = XBOX_AXIS_RANGE(value);
		Input::controller.xboxAxisRaw.leftStickY = value;
		break;
	case XBOX_L_TRIGGER:
		Input::controller.xboxAxis.leftTrigger = XBOX_AXIS_RANGE(value);
		Input::controller.xboxAxisRaw.leftTrigger = value;
		break;
	case XBOX_R_STICK_X:
		Input::controller.xboxAxis.rightStickX = XBOX_AXIS_RANGE(value);
		Input::controller.xboxAxisRaw.rightStickX = value;
		break;
	case XBOX_R_STICK_Y:
		Input::controller.xboxAxis.rightStickY = XBOX_AXIS_RANGE(value);
		Input::controller.xboxAxisRaw.rightStickY = value;
		break;
	case XBOX_R_TRIGGER:
		Input::controller.xboxAxis.rightTrigger = XBOX_AXIS_RANGE(value);
		Input::controller.xboxAxisRaw.rightTrigger = value;
		break;

	default:
		break;
	}
}
HEX_API void OnControllerButtonDown(uchar button)
{
	switch (button)
	{
	case XBOX_A_BUTTON:
		Input::controller.xboxButtons.a = true;
		break;
	case XBOX_B_BUTTON:
		Input::controller.xboxButtons.b = true;
		break;
	case XBOX_X_BUTTON:
		Input::controller.xboxButtons.x = true;
		break;
	case XBOX_Y_BUTTON:
		Input::controller.xboxButtons.y = true;
		break;
	case XBOX_L_BUMPER:
		Input::controller.xboxButtons.leftBumper = true;
		break;
	case XBOX_R_BUMPER:
		Input::controller.xboxButtons.rightBumper = true;
		break;
	case XBOX_BACK:
		Input::controller.xboxButtons.back = true;
		break;
	case XBOX_START:
		Input::controller.xboxButtons.start = true;
		break;
	case XBOX_L_STICK:
		Input::controller.xboxButtons.leftStick = true;
		break;
	case XBOX_R_STICK:
		Input::controller.xboxButtons.rightStick = true;
		break;

	default:
		break;
	}
}
HEX_API void OnControllerButtonUp(uchar button)
{
	switch (button)
	{
	case XBOX_A_BUTTON:
		Input::controller.xboxButtons.a = false;
		break;
	case XBOX_B_BUTTON:
		Input::controller.xboxButtons.b = false;
		break;
	case XBOX_X_BUTTON:
		Input::controller.xboxButtons.x = false;
		break;
	case XBOX_Y_BUTTON:
		Input::controller.xboxButtons.y = false;
		break;
	case XBOX_L_BUMPER:
		Input::controller.xboxButtons.leftBumper = false;
		break;
	case XBOX_R_BUMPER:
		Input::controller.xboxButtons.rightBumper = false;
		break;
	case XBOX_BACK:
		Input::controller.xboxButtons.back = false;
		break;
	case XBOX_START:
		Input::controller.xboxButtons.start = false;
		break;
	case XBOX_L_STICK:
		Input::controller.xboxButtons.leftStick = false;
		break;
	case XBOX_R_STICK:
		Input::controller.xboxButtons.rightStick = false;
		break;

	default:
		break;
	}
}
	
HEX_END
#endif