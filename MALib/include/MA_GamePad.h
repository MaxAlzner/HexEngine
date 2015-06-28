#ifndef _MA_GAMEPAD_H_
#define _MA_GAMEPAD_H_
_MALIB_BEGIN

#define GAMEPAD_AXIS_MIN -32767
#define GAMEPAD_AXIS_MAX 32767
#define GAMEPAD_AXIS_RANGE(x) (float(x) / float(GAMEPAD_AXIS_MAX))

#define GAMEPAD_AXIS_BUFFERSIZE    6
#define GAMEPAD_BUTTONS_BUFFERSIZE 10
#define GAMEPAD_DPAD_BUFFERSIZE    9

typedef enum MALIB_API ButtonCode
{
	BUTTON_A                   = 0, 
	BUTTON_B                   = 1, 
	BUTTON_X                   = 2, 
	BUTTON_Y                   = 3, 
	BUTTON_L_BUMPER            = 4, 
	BUTTON_R_BUMPER            = 5, 
	BUTTON_BACK                = 6, 
	BUTTON_START               = 7, 
	BUTTON_L_STICK             = 8, 
	BUTTON_R_STICK             = 9, 
} ButtonCode;
typedef enum MALIB_API AxisCode
{
	AXIS_L_STICK_X             = 0, 
	AXIS_L_STICK_Y             = 1, 
	AXIS_L_TRIGGER             = 2, 
	AXIS_R_STICK_X             = 3, 
	AXIS_R_STICK_Y             = 4, 
	AXIS_R_TRIGGER             = 5, 
} AxisCode;

typedef struct MALIB_API GamepadInput
{
	GamepadInput();

	union
	{
		struct
		{
			float leftStickX;
			float leftStickY;
			float leftTrigger;
			float rightStickX;
			float rightStickY;
			float rightTrigger;
		} axis;
		float axisBuffer[GAMEPAD_AXIS_BUFFERSIZE];
	};
	union
	{
		struct
		{
			long leftStickX;
			long leftStickY;
			long leftTrigger;
			long rightStickX;
			long rightStickY;
			long rightTrigger;
		} axisRaw;
		long axisRawBuffer[GAMEPAD_AXIS_BUFFERSIZE];
	};
	union
	{
		struct
		{
			bool a;
			bool b;
			bool x;
			bool y;
			bool leftBumper;
			bool rightBumper;
			bool back;
			bool start;
			bool leftStick;
			bool rightStick;
		} buttons;
		bool buttonsBuffer[GAMEPAD_BUTTONS_BUFFERSIZE];
	};
	union
	{
		struct
		{
			bool a;
			bool b;
			bool x;
			bool y;
			bool leftBumper;
			bool rightBumper;
			bool back;
			bool start;
			bool leftStick;
			bool rightStick;
		} buttonsLatch;
		bool buttonsLatchBuffer[GAMEPAD_BUTTONS_BUFFERSIZE];
	};
	union
	{
		struct
		{
			bool topLeft;
			bool top;
			bool topRight;
			bool left;
			bool center;
			bool right;
			bool bottomLeft;
			bool bottom;
			bool bottomRight;
		} dpad;
		bool dpadBuffer[GAMEPAD_DPAD_BUFFERSIZE];
	};
	bool connected;
} GamepadInput;

_MALIB_END
#endif