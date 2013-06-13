#include "main.h"

FILE* LOG::file = NULL;

void LOG::Initialize()
{
	LOG::file = fopen("output.log", "a");
	LOG::Message("START");
}
void LOG::Unitialize()
{
	LOG::Message("END");
	fclose(LOG::file);
}

void LOG::Message(const char* str)
{
	if (LOG::file == NULL) return;
	LOG::Ticks();
	fprintf(LOG::file, " %s\n", str);
}
void LOG::Message(const char* prefix, const char* str)
{
	if (LOG::file == NULL) return;
	LOG::Ticks();
	if (prefix != NULL) fprintf(LOG::file, " %s", prefix);
	fprintf(LOG::file, " %s\n", str);
}
void LOG::Out1f(const char* prefix, float v0)
{
	if (LOG::file == NULL) return;
	LOG::Ticks();
	if (prefix != NULL) fprintf(LOG::file, " %s", prefix);
	fprintf(LOG::file, " %f\n", v0);
}
void LOG::Out2f(const char* prefix, float v0, float v1)
{
	if (LOG::file == NULL) return;
	LOG::Ticks();
	if (prefix != NULL) fprintf(LOG::file, " %s", prefix);
	fprintf(LOG::file, " %f, %f\n", v0, v1);
}
void LOG::Out3f(const char* prefix, float v0, float v1, float v2)
{
	if (LOG::file == NULL) return;
	LOG::Ticks();
	if (prefix != NULL) fprintf(LOG::file, " %s", prefix);
	fprintf(LOG::file, " %f, %f, %f\n", v0, v1, v2);
}
void LOG::Out4f(const char* prefix, float v0, float v1, float v2, float v3)
{
	if (LOG::file == NULL) return;
	LOG::Ticks();
	if (prefix != NULL) fprintf(LOG::file, " %s", prefix);
	fprintf(LOG::file, " %f, %f, %f, %f\n", v0, v1, v2, v3);
}
void LOG::Out1i(const char* prefix, int v0)
{
	if (LOG::file == NULL) return;
	LOG::Ticks();
	if (prefix != NULL) fprintf(LOG::file, " %s", prefix);
	fprintf(LOG::file, " %d\n", v0);
}
void LOG::Out2i(const char* prefix, int v0, int v1)
{
	if (LOG::file == NULL) return;
	LOG::Ticks();
	if (prefix != NULL) fprintf(LOG::file, " %s", prefix);
	fprintf(LOG::file, " %d, %d\n", v0, v1);
}
void LOG::Out3i(const char* prefix, int v0, int v1, int v2)
{
	if (LOG::file == NULL) return;
	LOG::Ticks();
	if (prefix != NULL) fprintf(LOG::file, " %s", prefix);
	fprintf(LOG::file, " %d, %d, %d\n", v0, v1, v2);
}
void LOG::Out4i(const char* prefix, int v0, int v1, int v2, int v3)
{
	if (LOG::file == NULL) return;
	LOG::Ticks();
	if (prefix != NULL) fprintf(LOG::file, " %s", prefix);
	fprintf(LOG::file, " %d, %d, %d, %d\n", v0, v1, v2, v3);
}
void LOG::Out1ptr(const char* prefix, void* v0)
{
	if (LOG::file == NULL) return;
	LOG::Ticks();
	if (prefix != NULL) fprintf(LOG::file, " %s", prefix);
	fprintf(LOG::file, " %p\n", v0);
}
void LOG::Out2ptr(const char* prefix, void* v0, void* v1)
{
	if (LOG::file == NULL) return;
	LOG::Ticks();
	if (prefix != NULL) fprintf(LOG::file, " %s", prefix);
	fprintf(LOG::file, " %p, %p\n", v0, v1);
}
void LOG::Out3ptr(const char* prefix, void* v0, void* v1, void* v2)
{
	if (LOG::file == NULL) return;
	LOG::Ticks();
	if (prefix != NULL) fprintf(LOG::file, " %s", prefix);
	fprintf(LOG::file, " %p, %p, %p\n", v0, v1, v2);
}
void LOG::Out4ptr(const char* prefix, void* v0, void* v1, void* v2, void* v3)
{
	if (LOG::file == NULL) return;
	LOG::Ticks();
	if (prefix != NULL) fprintf(LOG::file, " %s", prefix);
	fprintf(LOG::file, " %p, %p, %p, %p\n", v0, v1, v2, v3);
}
void LOG::OutBool(const char* prefix, bool v)
{
	if (LOG::file == NULL) return;
	LOG::Ticks();
	if (prefix != NULL) fprintf(LOG::file, " %s", prefix);
	if (v) fprintf(LOG::file, " true\n");
	else fprintf(LOG::file, " false\n");
}

void LOG::Ticks()
{
	clock_t ticks = clock();
	fprintf(LOG::file, "[%8u]", (unsigned)ticks);
}