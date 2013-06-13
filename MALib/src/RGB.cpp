#include "..\main.h"

unsigned int ARGB::CreateARGB(unsigned int a, unsigned int r, unsigned int g, unsigned int b)
{
	return (a << 24) + (r << 16) + (g << 8) + (b);
}
unsigned int ARGB::CreateARGB(unsigned int r, unsigned int g, unsigned int b)
{
	if (r < 0x00) r = 0x00;
	else if (r > 0xFF) r = 0xFF;
	if (g < 0x00) g = 0x00;
	else if (g > 0xFF) g = 0xFF;
	if (b < 0x00) b = 0x00;
	else if (b > 0xFF) b = 0xFF;
	return CreateARGB(0xFF, r, g, b);
}
void ARGB::ExtractColor(unsigned int pixel, unsigned int &a, unsigned int &r, unsigned int &g, unsigned int &b)
{
	a = pixel >> 24;
	r = (pixel << 8) >> 24;
	g = (pixel << 16) >> 24;
	b = (pixel << 24) >> 24;
}
unsigned int ARGB::BlendColor(unsigned int dest, unsigned int src)
{
	unsigned int a1, r1, g1, b1;
	ExtractColor((unsigned int)src, a1, r1, g1, b1);

	unsigned int a2, r2, g2, b2;
	ExtractColor((unsigned int)dest, a2, r2, g2, b2);

	unsigned int a3, r3, g3, b3;
	a3 = a1;
	float pixel_alpha = float(a3) / 255.0f;
			
	r3 = r2 + (unsigned int)(pixel_alpha * ((int)r1 - (int)r2));
	g3 = g2 + (unsigned int)(pixel_alpha * ((int)g1 - (int)g2));
	b3 = b2 + (unsigned int)(pixel_alpha * ((int)b1 - (int)b2));

	return CreateARGB(a2, r3, g3, b3);
}
bool ARGB::IsColorKey(unsigned int color, unsigned int colorKey)
{
	color = color | 0xFF000000;
	colorKey = colorKey | 0xFF000000;

	if(color == colorKey) return true;
	return false;
}
unsigned int ARGB::GetAlpha(unsigned int color)
{
	if (color <= 0) return 0;
	else if (color > 0xFFFFFFFF) return 0xFF;
	return color >> 24;
}
unsigned int ARGB::GetRed(unsigned int color)
{
	if (color <= 0) return 0;
	else if (color > 0xFFFFFFFF) return 0xFF;
	return (color << 8) >> 24;
}
unsigned int ARGB::GetGreen(unsigned int color)
{
	if (color <= 0) return 0;
	else if (color > 0xFFFFFFFF) return 0xFF;
	return (color << 16) >> 24;
}
unsigned int ARGB::GetBlue(unsigned int color)
{
	if (color <= 0) return 0;
	else if (color > 0xFFFFFFFF) return 0xFF;
	return (color << 24) >> 24;
}		
unsigned int ARGB::ModAlpha(unsigned int color, unsigned int n)
{
	unsigned int alpha = GetAlpha(color) + n;
	if (alpha < 0x00) n = 0x00;
	if (alpha > 0xFF) n = 0xFF;
	return CreateARGB(alpha, GetRed(color), GetGreen(color), GetBlue(color));
}
unsigned int ARGB::ModRed(unsigned int color, unsigned int n)
{
	unsigned int red = GetRed(color) + n;
	if (red < 0x00) red = 0x00;
	if (red > 0xFF) red = 0xFF;
	return CreateARGB(GetAlpha(color), red, GetGreen(color), GetBlue(color));
}
unsigned int ARGB::ModGreen(unsigned int color, unsigned int n)
{
	unsigned int green = GetGreen(color) + n;
	if (green < 0x00) green = 0x00;
	if (green > 0xFF) green = 0xFF;
	return CreateARGB(GetAlpha(color), GetRed(color), green, GetBlue(color));
}
unsigned int ARGB::ModBlue(unsigned int color, unsigned int n)
{
	unsigned int blue = GetBlue(color) + n;
	if (blue < 0x00) blue = 0x00;
	if (blue > 0xFF) blue = 0xFF;
	return CreateARGB(GetAlpha(color), GetRed(color), GetGreen(color), blue);
}
unsigned int ARGB::SetAlpha(unsigned int color, unsigned int n)
{
	if (n < 0x00) n = 0x00;
	if (n > 0xFF) n = 0xFF;
	return CreateARGB(n, GetRed(color), GetGreen(color), GetBlue(color));
}
unsigned int ARGB::SetRed(unsigned int color, unsigned int n)
{
	if (n < 0x00) n = 0x00;
	if (n > 0xFF) n = 0xFF;
	return CreateARGB(GetAlpha(color), n, GetGreen(color), GetBlue(color));
}
unsigned int ARGB::SetGreen(unsigned int color, unsigned int n)
{
	if (n < 0x00) n = 0x00;
	if (n > 0xFF) n = 0xFF;
	return CreateARGB(GetAlpha(color), GetRed(color), n, GetBlue(color));
}
unsigned int ARGB::SetBlue(unsigned int color, unsigned int n)
{
	if (n < 0x00) n = 0x00;
	if (n > 0xFF) n = 0xFF;
	return CreateARGB(GetAlpha(color), GetRed(color), GetGreen(color), n);
}

unsigned int RGBA::CreateRGBA(unsigned int a, unsigned int r, unsigned int g, unsigned int b)
{
	return (r << 24) + (g << 16) + (b << 8) + (a);
}
unsigned int RGBA::CreateRGBA(unsigned int r, unsigned int g, unsigned int b)
{
	if (r < 0x00) r = 0x00;
	else if (r > 0xFF) r = 0xFF;
	if (g < 0x00) g = 0x00;
	else if (g > 0xFF) g = 0xFF;
	if (b < 0x00) b = 0x00;
	else if (b > 0xFF) b = 0xFF;
	return CreateRGBA(r, g, b, 0xFF);
}
void RGBA::ExtractColor(unsigned int pixel, unsigned int &a, unsigned int &r, unsigned int &g, unsigned int &b)
{
	r = pixel >> 24;
	g = (pixel << 8) >> 24;
	b = (pixel << 16) >> 24;
	a = (pixel << 24) >> 24;
}
unsigned int RGBA::BlendColor(unsigned int dest, unsigned int src)
{
	unsigned int a1, r1, g1, b1;
	ExtractColor((unsigned int)src, a1, r1, g1, b1);

	unsigned int a2, r2, g2, b2;
	ExtractColor((unsigned int)dest, a2, r2, g2, b2);

	unsigned int a3, r3, g3, b3;
	a3 = a1;
	float pixel_alpha = float(a3) / 255.0f;
			
	r3 = r2 + (unsigned int)(pixel_alpha * ((int)r1 - (int)r2));
	g3 = g2 + (unsigned int)(pixel_alpha * ((int)g1 - (int)g2));
	b3 = b2 + (unsigned int)(pixel_alpha * ((int)b1 - (int)b2));

	return CreateRGBA(a2, r3, g3, b3);
}
bool RGBA::IsColorKey(unsigned int color, unsigned int colorKey)
{
	color = color | 0xFF000000;
	colorKey = colorKey | 0xFF000000;

	if(color == colorKey) return true;
	return false;
}
unsigned int RGBA::GetAlpha(unsigned int color)
{
	if (color <= 0) return 0;
	else if (color > 0xFFFFFFFF) return 0xFF;
	return color >> 24;
}
unsigned int RGBA::GetRed(unsigned int color)
{
	if (color <= 0) return 0;
	else if (color > 0xFFFFFFFF) return 0xFF;
	return (color << 8) >> 24;
}
unsigned int RGBA::GetGreen(unsigned int color)
{
	if (color <= 0) return 0;
	else if (color > 0xFFFFFFFF) return 0xFF;
	return (color << 16) >> 24;
}
unsigned int RGBA::GetBlue(unsigned int color)
{
	if (color <= 0) return 0;
	else if (color > 0xFFFFFFFF) return 0xFF;
	return (color << 24) >> 24;
}		
unsigned int RGBA::ModAlpha(unsigned int color, unsigned int n)
{
	unsigned int alpha = GetAlpha(color) + n;
	if (alpha < 0x00) n = 0x00;
	if (alpha > 0xFF) n = 0xFF;
	return CreateRGBA(alpha, GetRed(color), GetGreen(color), GetBlue(color));
}
unsigned int RGBA::ModRed(unsigned int color, unsigned int n)
{
	unsigned int red = GetRed(color) + n;
	if (red < 0x00) red = 0x00;
	if (red > 0xFF) red = 0xFF;
	return CreateRGBA(GetAlpha(color), red, GetGreen(color), GetBlue(color));
}
unsigned int RGBA::ModGreen(unsigned int color, unsigned int n)
{
	unsigned int green = GetGreen(color) + n;
	if (green < 0x00) green = 0x00;
	if (green > 0xFF) green = 0xFF;
	return CreateRGBA(GetAlpha(color), GetRed(color), green, GetBlue(color));
}
unsigned int RGBA::ModBlue(unsigned int color, unsigned int n)
{
	unsigned int blue = GetBlue(color) + n;
	if (blue < 0x00) blue = 0x00;
	if (blue > 0xFF) blue = 0xFF;
	return CreateRGBA(GetAlpha(color), GetRed(color), GetGreen(color), blue);
}
unsigned int RGBA::SetAlpha(unsigned int color, unsigned int n)
{
	if (n < 0x00) n = 0x00;
	if (n > 0xFF) n = 0xFF;
	return CreateRGBA(n, GetRed(color), GetGreen(color), GetBlue(color));
}
unsigned int RGBA::SetRed(unsigned int color, unsigned int n)
{
	if (n < 0x00) n = 0x00;
	if (n > 0xFF) n = 0xFF;
	return CreateRGBA(GetAlpha(color), n, GetGreen(color), GetBlue(color));
}
unsigned int RGBA::SetGreen(unsigned int color, unsigned int n)
{
	if (n < 0x00) n = 0x00;
	if (n > 0xFF) n = 0xFF;
	return CreateRGBA(GetAlpha(color), GetRed(color), n, GetBlue(color));
}
unsigned int RGBA::SetBlue(unsigned int color, unsigned int n)
{
	if (n < 0x00) n = 0x00;
	if (n > 0xFF) n = 0xFF;
	return CreateRGBA(GetAlpha(color), GetRed(color), GetGreen(color), n);
}