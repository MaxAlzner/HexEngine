#ifndef _MA_MOUSE_H_
#define _MA_MOUSE_H_
_MALIB_BEGIN
	
typedef enum MALIB_API MouseButton
{
	BUTTON_LEFT                = 0, 
	BUTTON_MIDDLE              = 1, 
	BUTTON_RIGHT               = 2, 
} MouseButton;

typedef struct MALIB_API MouseInput
{
	MouseInput();

	struct
	{
		uint x;
		uint y;
	} position;
	struct
	{
		int x;
		int y;
	} delta;
	struct
	{
		float x;
		float y;
	} scalar;

	bool left;
	bool right;
	bool middle;
	bool active;
} MouseInput;

_MALIB_END
#endif