#ifndef __CORE_RGB_H_
#define __CORE_RGB_H_

#define RGBA_WHITE             0xFFFFFFFF
#define RGBA_GRAY_LIGHT        0xCCCCCCFF
#define RGBA_GRAY_MEDIUM       0x888888FF
#define RGBA_GRAY_DARK         0x444444FF
#define RGBA_BLACK             0x000000FF

#define RGBA_PINK              0xFF0088FF
#define RGBA_RED               0xFF0000FF
#define RGBA_ORANGE            0xFF8800FF
#define RGBA_YELLOW            0xFFFF00FF
#define RGBA_YELLOWGREEN       0x88FF00FF
#define RGBA_GREEN             0x00FF00FF
#define RGBA_TURQUIOSE         0x00FF88FF
#define RGBA_CYAN              0x00FFFFFF
#define RGBA_BLUEGREEN         0x0088FFFF
#define RGBA_BLUE              0x0000FFFF
#define RGBA_VIOLET            0x8800FFFF
#define RGBA_MAGENTA           0xFF00FFFF

class ARGB
{
public:
	static unsigned int CreateARGB(unsigned int a, unsigned int r, unsigned int g, unsigned int b);
	static unsigned int CreateARGB(unsigned int r, unsigned int g, unsigned int b);
	static void ExtractColor(unsigned int pixel, unsigned int &a, unsigned int &r, unsigned int &g, unsigned int &b);
	static unsigned int BlendColor(unsigned int dest, unsigned int src);
	static bool IsColorKey(unsigned int color, unsigned int colorKey);
	static unsigned int GetAlpha(unsigned int color);
	static unsigned int GetRed(unsigned int color);
	static unsigned int GetGreen(unsigned int color);
	static unsigned int GetBlue(unsigned int color);
	static unsigned int ModAlpha(unsigned int color, unsigned int n);
	static unsigned int ModRed(unsigned int color, unsigned int n);
	static unsigned int ModGreen(unsigned int color, unsigned int n);
	static unsigned int ModBlue(unsigned int color, unsigned int n);
	static unsigned int SetAlpha(unsigned int color, unsigned int n);
	static unsigned int SetRed(unsigned int color, unsigned int n);
	static unsigned int SetGreen(unsigned int color, unsigned int n);
	static unsigned int SetBlue(unsigned int color, unsigned int n);
};
class RGBA
{
public:
	static unsigned int CreateRGBA(unsigned int a, unsigned int r, unsigned int g, unsigned int b);
	static unsigned int CreateRGBA(unsigned int r, unsigned int g, unsigned int b);
	static void ExtractColor(unsigned int pixel, unsigned int &a, unsigned int &r, unsigned int &g, unsigned int &b);
	static unsigned int BlendColor(unsigned int dest, unsigned int src);
	static bool IsColorKey(unsigned int color, unsigned int colorKey);
	static unsigned int GetAlpha(unsigned int color);
	static unsigned int GetRed(unsigned int color);
	static unsigned int GetGreen(unsigned int color);
	static unsigned int GetBlue(unsigned int color);
	static unsigned int ModAlpha(unsigned int color, unsigned int n);
	static unsigned int ModRed(unsigned int color, unsigned int n);
	static unsigned int ModGreen(unsigned int color, unsigned int n);
	static unsigned int ModBlue(unsigned int color, unsigned int n);
	static unsigned int SetAlpha(unsigned int color, unsigned int n);
	static unsigned int SetRed(unsigned int color, unsigned int n);
	static unsigned int SetGreen(unsigned int color, unsigned int n);
	static unsigned int SetBlue(unsigned int color, unsigned int n);
};

#endif