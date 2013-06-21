#include "..\include\MALib.h"

#ifdef _MA_LOG_H_
_MALIB_BEGIN

MALIB_API FILE* LOG_FILE = NULL;

MALIB_API void LOG_Initialize()
{
	if (LOG_FILE != NULL) fclose(LOG_FILE);
	fopen_s(&LOG_FILE, "output.log", "a");
	LOG_Message("START");
}
MALIB_API void LOG_Unitialize()
{
	if (LOG_FILE == NULL) return;
	LOG_Message("END");
	fclose(LOG_FILE);
}

MALIB_API void LOG_Message(const char* str)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	fprintf(LOG_FILE, " %s\n", str);
}
MALIB_API void LOG_Message(const char* prefix, const char* str)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	fprintf(LOG_FILE, " %s\n", str);
}
MALIB_API void LOG_Out1f(const char* prefix, float v0)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	fprintf(LOG_FILE, " %f\n", v0);
}
MALIB_API void LOG_Out2f(const char* prefix, float v0, float v1)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	fprintf(LOG_FILE, " %f, %f\n", v0, v1);
}
MALIB_API void LOG_Out3f(const char* prefix, float v0, float v1, float v2)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	fprintf(LOG_FILE, " %f, %f, %f\n", v0, v1, v2);
}
MALIB_API void LOG_Out4f(const char* prefix, float v0, float v1, float v2, float v3)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	fprintf(LOG_FILE, " %f, %f, %f, %f\n", v0, v1, v2, v3);
}
MALIB_API void LOG_Outfv(const char* prefix, float* v, unsigned size)
{
	if (LOG_FILE == NULL || v == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	for (unsigned i = 0; i < size; i++)
	{
		fprintf(LOG_FILE, " %f", v[i]);
		if (i < size - 1) fprintf(LOG_FILE, ",");
	}
	fprintf(LOG_FILE, "\n");
}
MALIB_API void LOG_Out1i(const char* prefix, int v0)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	fprintf(LOG_FILE, " %d\n", v0);
}
MALIB_API void LOG_Out2i(const char* prefix, int v0, int v1)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	fprintf(LOG_FILE, " %d, %d\n", v0, v1);
}
MALIB_API void LOG_Out3i(const char* prefix, int v0, int v1, int v2)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	fprintf(LOG_FILE, " %d, %d, %d\n", v0, v1, v2);
}
MALIB_API void LOG_Out4i(const char* prefix, int v0, int v1, int v2, int v3)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	fprintf(LOG_FILE, " %d, %d, %d, %d\n", v0, v1, v2, v3);
}
MALIB_API void LOG_Outiv(const char* prefix, int* v, unsigned size)
{
	if (LOG_FILE == NULL || v == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	for (unsigned i = 0; i < size; i++)
	{
		fprintf(LOG_FILE, " %d", v[i]);
		if (i < size - 1) fprintf(LOG_FILE, ",");
	}
	fprintf(LOG_FILE, "\n");
}
MALIB_API void LOG_Out1ptr(const char* prefix, void* v0)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	fprintf(LOG_FILE, " %p\n", v0);
}
MALIB_API void LOG_Out2ptr(const char* prefix, void* v0, void* v1)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	fprintf(LOG_FILE, " %p, %p\n", v0, v1);
}
MALIB_API void LOG_Out3ptr(const char* prefix, void* v0, void* v1, void* v2)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	fprintf(LOG_FILE, " %p, %p, %p\n", v0, v1, v2);
}
MALIB_API void LOG_Out4ptr(const char* prefix, void* v0, void* v1, void* v2, void* v3)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	fprintf(LOG_FILE, " %p, %p, %p, %p\n", v0, v1, v2, v3);
}
MALIB_API void LOG_OutBool(const char* prefix, bool v)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	if (v) fprintf(LOG_FILE, " true\n");
	else fprintf(LOG_FILE, " false\n");
}

_MALIB_END
#endif