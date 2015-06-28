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
	TEXTFILE(string data, uint size);
	~TEXTFILE();

	ARRAY<string> lines;
	string data;
	uint size;
};

bool MALIB_API SplitLines(TEXTFILE* file);
	
bool MALIB_API ImportTextFile(const string filepath, TEXTFILE** outFile);
	
bool MALIB_API ExportTextFile(const string filepath, TEXTFILE* file);

void MALIB_API CreateTextFile(TEXTFILE** file, const string data, uint size);
void MALIB_API FreeTextFile(TEXTFILE** file);

_MALIB_END
#endif