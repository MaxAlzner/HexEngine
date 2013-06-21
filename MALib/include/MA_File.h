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
	TEXTFILE()
	{
		this->data = 0;
		this->size = 0;
	}
	TEXTFILE(char* data, unsigned size)
	{
		this->data = data;
		this->size = size;
	}
	~TEXTFILE()
	{
		this->lines.zero();
		if (this->data != 0) delete [] this->data;
	}

	ARRAY<char*> lines;
	char* data;
	unsigned size;
};
	
bool MALIB_API ImportTextFile(const char* filepath, TEXTFILE** outFile);
bool MALIB_API FreeTextFile(TEXTFILE* file);

_MALIB_END
#endif