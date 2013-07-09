#ifndef _HEX_INPUTDEF_H_
#define _HEX_INPUTDEF_H_
HEX_BEGIN

#define XBOX_A_BUTTON  0
#define XBOX_B_BUTTON  1
#define XBOX_X_BUTTON  2
#define XBOX_Y_BUTTON  3
#define XBOX_L_BUMPER  4
#define XBOX_R_BUMPER  5
#define XBOX_BACK      6
#define XBOX_START     7
#define XBOX_L_STICK   8
#define XBOX_R_STICK   9

#define XBOX_L_STICK_X 0
#define XBOX_L_STICK_Y 1
#define XBOX_L_TRIGGER 2
#define XBOX_R_STICK_X 3
#define XBOX_R_STICK_Y 4
#define XBOX_R_TRIGGER 5
	
#define XBOX_AXIS_MIN -32767
#define XBOX_AXIS_MAX 32767
#define XBOX_AXIS_RANGE(x) (float(x) / float(XBOX_AXIS_MAX))

typedef enum KeyCode
{
	KEY_UNKNOWN                = 0,
	KEY_BACKSPACE              = 8,
	KEY_TAB                    = 9,
	KEY_CLEAR                  = 12,
	KEY_RETURN                 = 13,
	KEY_ESCAPE                 = 27,
	KEY_SPACE                  = 32,
	KEY_EXCLAIM                = 33,
	KEY_QUOTEDBL               = 34,
	KEY_HASH                   = 35,
	KEY_DOLLAR                 = 36,
	KEY_AMPERSAND              = 38,
	KEY_QUOTE                  = 39,
	KEY_LEFTPAREN              = 40,
	KEY_RIGHTPAREN             = 41,
	KEY_ASTERISK               = 42,
	KEY_PLUS                   = 43,
	KEY_COMMA                  = 44,
	KEY_MINUS                  = 45,
	KEY_PERIOD                 = 46,
	KEY_SLASH                  = 47,
	KEY_0                      = 48,
	KEY_1                      = 49,
	KEY_2                      = 50,
	KEY_3                      = 51,
	KEY_4                      = 52,
	KEY_5                      = 53,
	KEY_6                      = 54,
	KEY_7                      = 55,
	KEY_8                      = 56,
	KEY_9                      = 57,
	KEY_COLON                  = 58,
	KEY_SEMICOLON              = 59,
	KEY_LESS                   = 60,
	KEY_EQUALS                 = 61,
	KEY_GREATER                = 62,
	KEY_QUESTION               = 63,
	KEY_AT                     = 64,
	/* upper case */
	KEY_LEFTBRACKET	           = 91,
	KEY_BACKSLASH              = 92,
	KEY_RIGHTBRACKET           = 93,
	KEY_CARET                  = 94,
	KEY_UNDERSCORE             = 95,
	KEY_BACKQUOTE              = 96,
	KEY_A                      = 97,
	KEY_B                      = 98,
	KEY_C                      = 99,
	KEY_D                      = 100,
	KEY_E                      = 101,
	KEY_F                      = 102,
	KEY_G                      = 103,
	KEY_H                      = 104,
	KEY_I                      = 105,
	KEY_J                      = 106,
	KEY_K                      = 107,
	KEY_L                      = 108,
	KEY_M                      = 109,
	KEY_N                      = 110,
	KEY_O                      = 111,
	KEY_P                      = 112,
	KEY_Q                      = 113,
	KEY_R                      = 114,
	KEY_S                      = 115,
	KEY_T                      = 116,
	KEY_U                      = 117,
	KEY_V                      = 118,
	KEY_W                      = 119,
	KEY_X                      = 120,
	KEY_Y                      = 121,
	KEY_Z                      = 122,
	KEY_DELETE                 = 127,

	KEY_NUMPAD_0               = 256,
	KEY_NUMPAD_1               = 257,
	KEY_NUMPAD_2               = 258,
	KEY_NUMPAD_3               = 259,
	KEY_NUMPAD_4               = 260,
	KEY_NUMPAD_5               = 261,
	KEY_NUMPAD_6               = 262,
	KEY_NUMPAD_7               = 263,
	KEY_NUMPAD_8               = 264,
	KEY_NUMPAD_9               = 265,
	KEY_NUMPAD_PERIOD          = 266,
	KEY_NUMPAD_DIVIDE          = 267,
	KEY_NUMPAD_MULTIPLY        = 268,
	KEY_NUMPAD_MINUS           = 269,
	KEY_NUMPAD_PLUS            = 270,
	KEY_NUMPAD_ENTER           = 271,
	KEY_NUMPAD_EQUALS          = 272,

	KEY_UP                     = 273,
	KEY_DOWN                   = 274,
	KEY_RIGHT                  = 275,
	KEY_LEFT                   = 276,
	KEY_INSERT                 = 277,
	KEY_HOME                   = 278,
	KEY_END                    = 279,
	KEY_PAGEUP                 = 280,
	KEY_PAGEDOWN               = 281,

	KEY_F1                     = 282,
	KEY_F2                     = 283,
	KEY_F3                     = 284,
	KEY_F4                     = 285,
	KEY_F5                     = 286,
	KEY_F6                     = 287,
	KEY_F7                     = 288,
	KEY_F8                     = 289,
	KEY_F9                     = 290,
	KEY_F10                    = 291,
	KEY_F11                    = 292,
	KEY_F12                    = 293,
	KEY_F13                    = 294,
	KEY_F14                    = 295,
	KEY_F15                    = 296,

	KEY_NUMLOCK                = 300,
	KEY_CAPSLOCK               = 301,
	KEY_SCROLLOCK              = 302,
	KEY_RSHIFT                 = 303,
	KEY_LSHIFT                 = 304,
	KEY_RCTRL                  = 305,
	KEY_LCTRL                  = 306,
	KEY_RALT                   = 307,
	KEY_LALT                   = 308,
	KEY_LWINDOWS               = 311,
	KEY_RWINDOWS               = 312,
	KEY_MODE                   = 313,
	KEY_COMPOSE                = 314,

	KEY_HELP                   = 315,
	KEY_PRINT                  = 316,
	KEY_SYSREQ                 = 317,
	KEY_BREAK                  = 318,
	KEY_MENU                   = 319,
} KeyCode;

#define KEY_BUFFERSIZE                320
#define CONTROLLER_AXIS_BUFFERSIZE    6
#define CONTROLLER_BUTTONS_BUFFERSIZE 10
#define CONTROLLER_DPAD_BUFFERSIZE    9

typedef struct MouseInput
{
	uint x;
	uint y;
	int deltaX;
	int deltaY;
	float scalarX;
	float scalarY;
	float scalarDeltaX;
	float scalarDeltaY;

	bool left;
	bool right;
	bool middle;
} MouseInput;

typedef struct KeyInput
{
	bool pressed[KEY_BUFFERSIZE];
	bool latched[KEY_BUFFERSIZE];
} KeyInput;

typedef struct ControllerInput
{
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
		} xboxAxis;
		float axis[CONTROLLER_AXIS_BUFFERSIZE];
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
		} xboxAxisRaw;
		long axisRaw[CONTROLLER_AXIS_BUFFERSIZE];
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
		} xboxButtons;
		bool buttons[CONTROLLER_BUTTONS_BUFFERSIZE];
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
		} xboxDpad;
		bool dpad[CONTROLLER_DPAD_BUFFERSIZE];
	};
	bool connected;
} ControllerInput;

HEX_END
#endif