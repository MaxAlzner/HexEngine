#include "..\include\HexMain.h"

#ifdef _HEX_TEXT_H_
HEX_BEGIN

/*FT_Library FontLibrary;
FT_Face FontFace;*/

TTF_Font* font = 0;

HEX_API void InitializeFont()
{
	/*FT_Error error = 0;
	error = FT_Init_FreeType(&FontLibrary);
	if (error != 0)
	{
		MALib::LOG_Message("Unable to initialize FreeType.");
	}
	error = FT_New_Face(FontLibrary, "data/upheavtt.ttf", 0, &FontFace);
	if (error != 0)
	{
		MALib::LOG_Message("Could not load font file.", "data/upheavtt.ttf");
	}
	error = FT_Set_Char_Size(FontFace, 8 * 64, 8 * 64, 96, 96);

	FT_Glyph glyph;*/

	font = TTF_OpenFont("data/upheavtt.ttf", 24);
}
HEX_API void UninitializeFont()
{
	TTF_CloseFont(font);
	TTF_Quit();
}

HEX_API void DrawString(const char* str, float x, float y)
{
	static SDL_Color color = {255, 255, 255, 255};
	//SDL_FillRect(ScreenSurface, 0, 0x221122);
	SDL_Surface* text = TTF_RenderText_Solid(font, str, color);
	SDL_Rect textRect = text->clip_rect;
	int result = SDL_BlitSurface(text, 0, RenderSurface, 0);
	SDL_FreeSurface(text);
	SDL_Flip(RenderSurface);
}
	
HEX_END
#endif