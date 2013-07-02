#ifndef _HEX_TEXT_H_
#define _HEX_TEXT_H_
HEX_BEGIN

HEX_API extern void InitializeFont();
HEX_API extern void UninitializeFont();

HEX_API extern void DrawString(const char* str, float x, float y);
	
HEX_END
#endif