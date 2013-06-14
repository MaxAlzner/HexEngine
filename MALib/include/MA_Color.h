#ifndef _MA_COLOR_H_
#define _MA_COLOR_H_

class MALIB_API COLOR
{
public:
	COLOR();
	COLOR(float a, float r, float g, float b);
	COLOR(float r, float g, float b);
	COLOR(unsigned int argb);
	COLOR(const COLOR& c);
	~COLOR();

	COLOR operator+(const COLOR &c);
	COLOR operator-(const COLOR &c);
	COLOR operator*(const COLOR &c);
	COLOR operator/(const COLOR &c);
	COLOR operator+(float scalar);
	COLOR operator-(float scalar);
	COLOR operator*(float scalar);
	COLOR operator/(float scalar);
	void operator+=(const COLOR &c);
	void operator-=(const COLOR &c);
	void operator*=(const COLOR &c);
	void operator/=(const COLOR &c);
	void operator+=(float scalar);
	void operator-=(float scalar);
	void operator*=(float scalar);
	void operator/=(float scalar);
	
	float a, r, g, b;

	static COLOR CreateColor(float a, float r, float g, float b);
	static COLOR CreateColor(unsigned int argb);
	static COLOR Gray(const COLOR &c);
	static unsigned int ToARGB(const COLOR &c);
	static unsigned int ToRGBA(const COLOR &c);
};

#endif