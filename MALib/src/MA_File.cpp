#include "..\include\MALib.h"

#ifdef _MA_FILE_H_
_MALIB_BEGIN
	
MALIB_API TEXTFILE::TEXTFILE()
{
	this->data = 0;
	this->size = 0;
}
MALIB_API TEXTFILE::TEXTFILE(string data, uint size)
{
	this->data = data;
	this->size = size;
}
MALIB_API TEXTFILE::~TEXTFILE()
{
	//if (this->lines.pointer() != 0) delete [] this->lines.pointer();
	this->lines.clear();
	if (this->data != 0) delete [] this->data;
}

bool MALIB_API SplitLines(TEXTFILE* file)
{
	if (file == NULL) return false;
	
	if (file->lines.pointer() != 0) delete [] file->lines.pointer();
	file->lines.clear();

	uint lines = 1;
	for (uint i = 0; i < file->size; i++)
	{
		char ch = file->data[i];
		if (ch == '\n') lines++;
		if (ch == '\0') break;
	}
	if (lines < 1) 
		return false;
	
	string seperated_lines = new char[file->size + 1];
	memcpy((void*)seperated_lines, (void*)file->data, sizeof(char) * file->size);
	seperated_lines[file->size] = '\0';
	
	file->lines.resize(lines);
	file->lines.add(seperated_lines);
	for (uint i = 1; i < lines; i++)
	{
		string last = strchr(file->lines[i - 1], '\n');
		string line = last + 1;
		*last = '\0';
		file->lines.add(line);
	}
	string end = strchr(file->lines[file->lines.length() - 1], '\n');
	//if (end != 0) *end = '\0';

	return true;
}

bool MALIB_API ImportTextFile(const string filepath, TEXTFILE** outFile)
{
	if (filepath == NULL || outFile == NULL) return false;
	
	uint size = 0;
	string buffer = 0;
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

	size += 1;
	buffer = new char[size];
	memset((void*)buffer, 0, sizeof(char) * size);

	fread((void*)buffer, 1, size - 1, bufferFile);
	fclose(bufferFile);
	//buffer[size - 2] = '\n';
	buffer[size - 1] = '\0';

	TEXTFILE* textFile = new TEXTFILE(buffer, size);

	*outFile = textFile;

	if (!SplitLines(textFile)) return false;

	return true;
}

bool MALIB_API ExportTextFile(const string filepath, TEXTFILE* file)
{
	if (file == NULL) return false;

	FILE* outFile = NULL;
	fopen_s(&outFile, filepath, "w");
	if (outFile == NULL) 
		return false;
	
	for (uint i = 0; i < file->lines.length(); i++)
	{
		fprintf(outFile, "%s\n", file->lines[i]);
	}

	fclose(outFile);

	return true;
}

void MALIB_API CreateTextFile(TEXTFILE** file, const string data, uint size)
{
	*file = new TEXTFILE(data, size);
}
void MALIB_API FreeTextFile(TEXTFILE** file)
{
	delete *file;
	*file = 0;
}

_MALIB_END
#endif