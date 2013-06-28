#ifndef _MA_FILE_H_
#define _MA_FILE_H_
_MALIB_BEGIN

#ifndef _INC_STDIO
#include <stdio.h>
#endif
#ifndef _INC_STRING
#include <string.h>
#endif

struct MALIB_API TEXTFILE
{
	TEXTFILE();
	TEXTFILE(char* data, unsigned size);
	~TEXTFILE();

	ARRAY<char*> lines;
	char* data;
	unsigned size;
};
	
bool MALIB_API ImportTextFile(const char* filepath, TEXTFILE** outFile);

void MALIB_API FreeTextFile(TEXTFILE** file);

_MALIB_END
#endif