#include "..\include\MALib.h"

#ifdef _MA_INPUT_H_
_MALIB_BEGIN

#ifdef _MA_MOUSE_H_
MALIB_API MouseInput::MouseInput()
{
	memset(this, 0, sizeof(MouseInput));
}
#endif
#ifdef _MA_KEY_H_
MALIB_API KeyInput::KeyInput()
{
	memset(this->pressed, 0, sizeof(bool) * KEY_BUFFERSIZE);
	memset(this->latched, 0, sizeof(bool) * KEY_BUFFERSIZE);
}
#endif
#ifdef _MA_GAMEPAD_H_
MALIB_API GamepadInput::GamepadInput()
{
	memset(this, 0, sizeof(GamepadInput));
}
#endif

MALIB_API MouseInput INPUT::MOUSE;
MALIB_API KeyInput INPUT::KEY;
MALIB_API GamepadInput INPUT::GAMEPAD;

MALIB_API float INPUT::GetAxis(AxisCode axis, float deadzone)
{
	if (INPUT::GAMEPAD.connected && axis < GAMEPAD_AXIS_BUFFERSIZE)
	{
		float value = INPUT::GAMEPAD.axisBuffer[axis];
		if (abs(value) < deadzone) value = 0.0f;
		return value;
	}
	return 0.0f;
}
MALIB_API float INPUT::GetTrigger(AxisCode trigger, float deadzone)
{
	if (INPUT::GAMEPAD.connected && (trigger == AXIS_L_TRIGGER || trigger == AXIS_R_TRIGGER))
	{
		float value = INPUT::GAMEPAD.axisBuffer[trigger];
		if (value < deadzone) value = 0.0f;
		return value;
	}
	return 0.0f;
}
MALIB_API bool INPUT::GetButton(ButtonCode button, bool latch)
{
	if (INPUT::GAMEPAD.connected && button < GAMEPAD_BUTTONS_BUFFERSIZE)
	{
		bool* value = INPUT::GAMEPAD.buttonsBuffer + button;
		bool* latched = INPUT::GAMEPAD.buttonsLatchBuffer + button;
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
	return false;
}
MALIB_API bool INPUT::IsButtonDown(ButtonCode button)
{
	if (INPUT::GAMEPAD.connected && button < GAMEPAD_BUTTONS_BUFFERSIZE)
	{
		return INPUT::GAMEPAD.buttonsBuffer[button];
	}
	return false;
}
MALIB_API bool INPUT::IsButtonUp(ButtonCode button)
{
	if (INPUT::GAMEPAD.connected && button < GAMEPAD_BUTTONS_BUFFERSIZE)
	{
		return !INPUT::GAMEPAD.buttonsBuffer[button];
	}
	return false;
}
MALIB_API bool INPUT::GetKey(KeyCode code, bool latch)
{
	bool* value = INPUT::KEY.pressed + code;
	bool* latched = INPUT::KEY.latched + code;
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
MALIB_API bool INPUT::GetKey(uchar code, bool latch)
{
	return INPUT::GetKey((KeyCode)code, latch);
}
MALIB_API bool INPUT::IsKeyDown(KeyCode code)
{
	return INPUT::KEY.pressed[code];
}
MALIB_API bool INPUT::IsKeyDown(uchar code)
{
	return INPUT::IsKeyDown((KeyCode)code);
}
MALIB_API bool INPUT::IsKeyUp(KeyCode code)
{
	return !INPUT::KEY.pressed[code];
}
MALIB_API bool INPUT::IsKeyUp(uchar code)
{
	return INPUT::IsKeyUp((KeyCode)code);
}

MALIB_API void INPUT::OnMouseMove(uint width, uint height, uint x, uint y)
{
	INPUT::MOUSE.delta.x = INPUT::MOUSE.position.x - x;
	INPUT::MOUSE.delta.y = INPUT::MOUSE.position.y - y;
	INPUT::MOUSE.position.x = x;
	INPUT::MOUSE.position.y = y;
	INPUT::MOUSE.scalar.x = float(INPUT::MOUSE.position.x) / float(width);
	INPUT::MOUSE.scalar.y = float(INPUT::MOUSE.position.y) / float(height);
}
MALIB_API void INPUT::OnMouseActive(bool state)
{
	INPUT::MOUSE.active = state;
}
MALIB_API void INPUT::OnMouseButtonDown(MouseButton button)
{
	switch (button)
	{
	case BUTTON_LEFT:
		INPUT::MOUSE.left = true;
		break;
	case BUTTON_MIDDLE:
		INPUT::MOUSE.middle = true;
		break;
	case BUTTON_RIGHT:
		INPUT::MOUSE.right = true;
		break;

	default:
		break;
	}
}
MALIB_API void INPUT::OnMouseButtonUp(MouseButton button)
{
	switch (button)
	{
	case BUTTON_LEFT:
		INPUT::MOUSE.left = false;
		break;
	case BUTTON_MIDDLE:
		INPUT::MOUSE.middle = false;
		break;
	case BUTTON_RIGHT:
		INPUT::MOUSE.right = false;
		break;

	default:
		break;
	}
}
MALIB_API void INPUT::OnMouseButton(MouseButton button, bool state)
{
	switch (button)
	{
	case BUTTON_LEFT:
		INPUT::MOUSE.left = state;
		break;
	case BUTTON_MIDDLE:
		INPUT::MOUSE.middle = state;
		break;
	case BUTTON_RIGHT:
		INPUT::MOUSE.right = state;
		break;

	default:
		break;
	}
}
MALIB_API void INPUT::OnKeyDown(KeyCode code)
{
	INPUT::KEY.pressed[code] = true;
}
MALIB_API void INPUT::OnKeyDown(uchar code)
{
	INPUT::OnKeyDown((KeyCode)code);
}
MALIB_API void INPUT::OnKeyUp(KeyCode code)
{
	INPUT::KEY.pressed[code] = false;
}
MALIB_API void INPUT::OnKeyUp(uchar code)
{
	INPUT::OnKeyUp((KeyCode)code);
}
MALIB_API void INPUT::OnKey(KeyCode code, bool state)
{
	INPUT::KEY.pressed[code] = state;
}
MALIB_API void INPUT::OnKey(uchar code, bool state)
{
	INPUT::OnKey((KeyCode)code, state);
}
MALIB_API void INPUT::OnControllerAxis(AxisCode axis, long value)
{
	INPUT::GAMEPAD.axisBuffer[axis] = GAMEPAD_AXIS_RANGE(value);
	INPUT::GAMEPAD.axisRawBuffer[axis] = value;
}
MALIB_API void INPUT::OnControllerButtonDown(ButtonCode button)
{
	INPUT::GAMEPAD.buttonsBuffer[button] = true;
}
MALIB_API void INPUT::OnControllerButtonUp(ButtonCode button)
{
	INPUT::GAMEPAD.buttonsBuffer[button] = false;
}
MALIB_API void INPUT::OnControllerButton(ButtonCode button, bool state)
{
	INPUT::GAMEPAD.buttonsBuffer[button] = state;
}

_MALIB_END
#endif