#ifndef __LOG_H_
#define __LOG_H_

class LOG
{
public:

	static void Initialize();
	static void Unitialize();

	static void Message(const char* str);
	static void Message(const char* prefix, const char* str);
	static void Out1f(const char* prefix, float v0);
	static void Out2f(const char* prefix, float v0, float v1);
	static void Out3f(const char* prefix, float v0, float v1, float v2);
	static void Out4f(const char* prefix, float v0, float v1, float v2, float v3);
	static void Out1i(const char* prefix, int v0);
	static void Out2i(const char* prefix, int v0, int v1);
	static void Out3i(const char* prefix, int v0, int v1, int v2);
	static void Out4i(const char* prefix, int v0, int v1, int v2, int v3);
	static void Out1ptr(const char* prefix, void* v0);
	static void Out2ptr(const char* prefix, void* v0, void* v1);
	static void Out3ptr(const char* prefix, void* v0, void* v1, void* v2);
	static void Out4ptr(const char* prefix, void* v0, void* v1, void* v2, void* v3);
	static void OutBool(const char* prefix, bool v);

	static FILE* file;

private:

	static void Ticks();
};

#endif