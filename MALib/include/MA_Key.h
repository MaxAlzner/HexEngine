#ifndef _MA_KEY_H_
#define _MA_KEY_H_
_MALIB_BEGIN
	
#define KEY_BUFFERSIZE 320
	
typedef enum MALIB_API KeyCode
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
	KEY_A                      = 65,
	KEY_B                      = 66,
	KEY_C                      = 67,
	KEY_D                      = 68,
	KEY_E                      = 69,
	KEY_F                      = 70,
	KEY_G                      = 71,
	KEY_H                      = 72,
	KEY_I                      = 73,
	KEY_J                      = 74,
	KEY_K                      = 75,
	KEY_L                      = 76,
	KEY_M                      = 77,
	KEY_N                      = 78,
	KEY_O                      = 79,
	KEY_P                      = 80,
	KEY_Q                      = 81,
	KEY_R                      = 82,
	KEY_S                      = 83,
	KEY_T                      = 84,
	KEY_U                      = 85,
	KEY_V                      = 86,
	KEY_W                      = 87,
	KEY_X                      = 88,
	KEY_Y                      = 89,
	KEY_Z                      = 90,
	KEY_LEFTBRACKET	           = 91,
	KEY_BACKSLASH              = 92,
	KEY_RIGHTBRACKET           = 93,
	KEY_CARET                  = 94,
	KEY_UNDERSCORE             = 95,
	KEY_BACKQUOTE              = 96,
	KEY_a                      = 97,
	KEY_b                      = 98,
	KEY_c                      = 99,
	KEY_d                      = 100,
	KEY_e                      = 101,
	KEY_f                      = 102,
	KEY_g                      = 103,
	KEY_h                      = 104,
	KEY_i                      = 105,
	KEY_j                      = 106,
	KEY_k                      = 107,
	KEY_l                      = 108,
	KEY_m                      = 109,
	KEY_n                      = 110,
	KEY_o                      = 111,
	KEY_p                      = 112,
	KEY_q                      = 113,
	KEY_r                      = 114,
	KEY_s                      = 115,
	KEY_t                      = 116,
	KEY_u                      = 117,
	KEY_v                      = 118,
	KEY_w                      = 119,
	KEY_x                      = 120,
	KEY_y                      = 121,
	KEY_z                      = 122,
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

typedef struct MALIB_API KeyInput
{
	KeyInput();

	bool pressed[KEY_BUFFERSIZE];
	bool latched[KEY_BUFFERSIZE];
} KeyInput;

_MALIB_END
#endif