#include "..\include\MALib.h"

#ifdef _MA_FILE_H_
_MALIB_BEGIN
	
MALIB_API TEXTFILE::TEXTFILE()
{
	this->data = 0;
	this->size = 0;
}
MALIB_API TEXTFILE::TEXTFILE(char* data, unsigned size)
{
	this->data = data;
	this->size = size;
}
MALIB_API TEXTFILE::~TEXTFILE()
{
	this->lines.zero();
	if (this->data != 0) delete [] this->data;
}

bool MALIB_API ImportTextFile(const char* filepath, TEXTFILE** outFile)
{
	if (filepath == NULL || outFile == NULL) return false;
	
	unsigned size = 0;
	char* buffer = 0;
	FILE* bufferFile = NULL;
	fopen_s(&bufferFile, filepath, "r");
	if (bufferFile == NULL) 
		return false;

	rewind(bufferFile);
	while (fgetc(bufferFile) != EOF)
	{
		size++;
		if (feof(bufferFile) != 0) break;
	}
	if (size < 1)
	{
		fclose(bufferFile);
		return false;
	}
	rewind(bufferFile);

	buffer = new char[size + 1];
	memset((void*)buffer, 0, sizeof(char) * size);

	fread((void*)buffer, 1, size, bufferFile);
	fclose(bufferFile);
	buffer[size] = '\0';

	unsigned lines = 0;
	for (unsigned i = 0; i < size; i++)
	{
		char ch = buffer[i];
		if (ch == '\0') break;
		if (ch == '\n') lines++;
	}
	if (lines < 1) 
		return false;

	char* seperated_lines = new char[size];
	memcpy((void*)seperated_lines, (void*)buffer, sizeof(char) * size);
	TEXTFILE* textFile = new TEXTFILE(buffer, size);
	textFile->lines.resize(lines);
	textFile->lines.add(seperated_lines);
	for (unsigned i = 1; i < lines; i++)
	{
		char* last = strchr(textFile->lines[i - 1], '\n');
		char* line = last + 1;
		*last = '\0';
		textFile->lines.add(line);
	}
	char* end = strchr(textFile->lines[textFile->lines.length() - 1], '\n');
	*end = '\0';

	*outFile = textFile;

	return true;
}

void MALIB_API FreeTextFile(TEXTFILE** file)
{
	delete *file;
	*file = 0;
}

_MALIB_END
#endif