#include "..\include\MALib.h"

#ifdef _MA_LOG_H_
_MALIB_BEGIN

FILE* LOG_FILE = NULL;

MALIB_API void LOG_Initialize(bool cleanFile)
{
	if (LOG_FILE != NULL) fclose(LOG_FILE);
	if (cleanFile) fopen_s(&LOG_FILE, "output.log", "w");
	else fopen_s(&LOG_FILE, "output.log", "a");
	LOG_Message("START");
}
MALIB_API void LOG_Unitialize()
{
	if (LOG_FILE == NULL) return;
	LOG_Message("END");
	fclose(LOG_FILE);
}

MALIB_API void LOG_Message(const string str)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	fprintf(LOG_FILE, " %s\n", str);
}
MALIB_API void LOG_Message(const string prefix, const string str)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	fprintf(LOG_FILE, " %s\n", str);
}
MALIB_API void LOG_Out1f(const string prefix, float v0)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	fprintf(LOG_FILE, " %f\n", v0);
}
MALIB_API void LOG_Out2f(const string prefix, float v0, float v1)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	fprintf(LOG_FILE, " %f, %f\n", v0, v1);
}
MALIB_API void LOG_Out3f(const string prefix, float v0, float v1, float v2)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	fprintf(LOG_FILE, " %f, %f, %f\n", v0, v1, v2);
}
MALIB_API void LOG_Out4f(const string prefix, float v0, float v1, float v2, float v3)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	fprintf(LOG_FILE, " %f, %f, %f, %f\n", v0, v1, v2, v3);
}
MALIB_API void LOG_Outvf(const string prefix, float* v, uint size)
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
MALIB_API void LOG_Out1i(const string prefix, int v0)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	fprintf(LOG_FILE, " %d\n", v0);
}
MALIB_API void LOG_Out2i(const string prefix, int v0, int v1)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	fprintf(LOG_FILE, " %d, %d\n", v0, v1);
}
MALIB_API void LOG_Out3i(const string prefix, int v0, int v1, int v2)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	fprintf(LOG_FILE, " %d, %d, %d\n", v0, v1, v2);
}
MALIB_API void LOG_Out4i(const string prefix, int v0, int v1, int v2, int v3)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	fprintf(LOG_FILE, " %d, %d, %d, %d\n", v0, v1, v2, v3);
}
MALIB_API void LOG_Outvi(const string prefix, int* v, uint size)
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
MALIB_API void LOG_Out1ch(const string prefix, char v0)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	fprintf(LOG_FILE, " %c\n", v0);
}
MALIB_API void LOG_Out2ch(const string prefix, char v0, char v1)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	fprintf(LOG_FILE, " %c, %c\n", v0, v1);
}
MALIB_API void LOG_Out3ch(const string prefix, char v0, char v1, char v2)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	fprintf(LOG_FILE, " %c, %c, %c\n", v0, v1, v2);
}
MALIB_API void LOG_Out4ch(const string prefix, char v0, char v1, char v2, char v3)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	fprintf(LOG_FILE, " %c, %c, %c, %c\n", v0, v1, v2, v3);
}
MALIB_API void LOG_Outvch(const string prefix, string v, uint size)
{
	if (LOG_FILE == NULL || v == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	for (unsigned i = 0; i < size; i++)
	{
		fprintf(LOG_FILE, " %c", v[i]);
		if (i < size - 1) fprintf(LOG_FILE, ",");
	}
	fprintf(LOG_FILE, "\n");
}
MALIB_API void LOG_Out1ptr(const string prefix, void* v0)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	fprintf(LOG_FILE, " %p\n", v0);
}
MALIB_API void LOG_Out2ptr(const string prefix, void* v0, void* v1)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	fprintf(LOG_FILE, " %p, %p\n", v0, v1);
}
MALIB_API void LOG_Out3ptr(const string prefix, void* v0, void* v1, void* v2)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	fprintf(LOG_FILE, " %p, %p, %p\n", v0, v1, v2);
}
MALIB_API void LOG_Out4ptr(const string prefix, void* v0, void* v1, void* v2, void* v3)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	fprintf(LOG_FILE, " %p, %p, %p, %p\n", v0, v1, v2, v3);
}
MALIB_API void LOG_Outvptr(const string prefix, void** v, uint size)
{
	if (LOG_FILE == NULL || v == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	for (unsigned i = 0; i < size; i++)
	{
		fprintf(LOG_FILE, " %p", v[i]);
		if (i < size - 1) fprintf(LOG_FILE, ",");
	}
	fprintf(LOG_FILE, "\n");
}
MALIB_API void LOG_Out1Bool(const string prefix, bool v0)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	if (v0) fprintf(LOG_FILE, " true\n");
	else fprintf(LOG_FILE, " false\n");
}
MALIB_API void LOG_Out2Bool(const string prefix, bool v0, bool v1)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	if (v0) fprintf(LOG_FILE, " true\n");
	else fprintf(LOG_FILE, " false\n");
	if (v1) fprintf(LOG_FILE, " true\n");
	else fprintf(LOG_FILE, " false\n");
}
MALIB_API void LOG_Out3Bool(const string prefix, bool v0, bool v1, bool v2)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	if (v0) fprintf(LOG_FILE, " true\n");
	else fprintf(LOG_FILE, " false\n");
	if (v1) fprintf(LOG_FILE, " true\n");
	else fprintf(LOG_FILE, " false\n");
	if (v2) fprintf(LOG_FILE, " true\n");
	else fprintf(LOG_FILE, " false\n");
}
MALIB_API void LOG_Out4Bool(const string prefix, bool v0, bool v1, bool v2, bool v3)
{
	if (LOG_FILE == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	if (v0) fprintf(LOG_FILE, " true\n");
	else fprintf(LOG_FILE, " false\n");
	if (v1) fprintf(LOG_FILE, " true\n");
	else fprintf(LOG_FILE, " false\n");
	if (v2) fprintf(LOG_FILE, " true\n");
	else fprintf(LOG_FILE, " false\n");
	if (v3) fprintf(LOG_FILE, " true\n");
	else fprintf(LOG_FILE, " false\n");
}
MALIB_API void LOG_OutvBool(const string prefix, bool* v, uint size)
{
	if (LOG_FILE == NULL || v == NULL) return;
	fprintf(LOG_FILE, "[%8u]", (unsigned)clock());
	if (prefix != NULL) fprintf(LOG_FILE, " %s", prefix);
	for (unsigned i = 0; i < size; i++)
	{
		if (v[i]) fprintf(LOG_FILE, " true\n");
		else fprintf(LOG_FILE, " false\n");
		if (i < size - 1) fprintf(LOG_FILE, ",");
	}
	fprintf(LOG_FILE, "\n");
}

MALIB_API void LOG_File(TEXTFILE* file)
{
	if (file == NULL) return;
	for (uint i = 0; i < file->lines.length(); i++)
	{
		LOG_Message(file->lines[i]);
	}
}

_MALIB_END
#endif