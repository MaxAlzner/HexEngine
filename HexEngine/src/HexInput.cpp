#include "..\include\HexMain.h"

#ifdef _HEX_INPUT_H_
HEX_BEGIN
	
HEX_API MouseInput Input::mouse;
HEX_API KeyInput Input::key;
HEX_API ControllerInput Input::controller;

HEX_API float Input::GetAxis(const string axis)
{
	return 0.0f;
}
HEX_API float Input::GetTrigger(const string trigger)
{
	return 0.0f;
}
HEX_API bool Input::GetButton(const string button)
{
	return false;
}
HEX_API bool Input::IsButtonDown(const string button)
{
	return false;
}
HEX_API bool Input::IsButtonUp(const string button)
{
	return false;
}
HEX_API bool Input::GetKey(uchar code)
{
	return false;
}
HEX_API bool Input::IsKeyDown(uchar button)
{
	return false;
}
HEX_API bool Input::IsKeyUp(uchar button)
{
	return false;
}

HEX_API SDL_Joystick* GamePad = 0;

HEX_API void InitializeInput()
{
	SDL_JoystickEventState(SDL_ENABLE);
	GamePad = SDL_JoystickOpen(0);
}
HEX_API void UninitializeInput()
{
}
	
HEX_API void PollEvents()
{
	int controllers = SDL_NumJoysticks();
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			OnKeyDown(event.key.keysym.sym);
			break;
		case SDL_KEYUP:
			OnKeyUp(event.key.keysym.sym);
			break;

		case SDL_MOUSEMOTION:
			OnMouseMove(event.motion.x, event.motion.y);
			break;
		case SDL_MOUSEBUTTONDOWN:
			OnButtonDown(event.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			OnButtonUp(event.button.button);
			break;

		case SDL_JOYAXISMOTION:
			OnAxis(event.jaxis.axis, event.jaxis.value);
			break;
		case SDL_JOYBUTTONDOWN:
			OnButtonDown(event.jbutton.button);
			break;
		case SDL_JOYBUTTONUP:
			OnButtonUp(event.jbutton.button);
			break;
			
		case SDL_ACTIVEEVENT:
			Paused = !bool(event.active.gain);
			break;
		case SDL_QUIT:
			AppRunning = false;
			break;
		case SDL_VIDEORESIZE:
			Reshape(event.resize.w, unsigned(float(event.resize.w) * AspectRatio));
			break;

		default:
			break;
		}
	}
}

HEX_API void OnMouseMove(uint x, uint y)
{
}
HEX_API void OnButtonDown(uchar button)
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
HEX_API void OnButtonUp(uchar button)
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
HEX_API void OnKeyDown(uchar code)
{
	switch (code)
	{
	case SDLK_ESCAPE:
		AppRunning = false;
		break;

	default:
		break;
	}
}
HEX_API void OnKeyUp(uchar code)
{
}
HEX_API void OnAxis(uchar axis, long value)
{
	if (axis == 0)
	{
	}
	else if (axis == 1)
	{
	}
}
	
HEX_END
#endif