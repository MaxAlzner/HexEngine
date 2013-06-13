#include "..\main.h"

bool ParseChar(char ch, unsigned int mode, char* compareTo)
{
	if (compareTo == NULL && mode & MODE_NONE) return false;

	if (CharInStr(compareTo, ch)) 
		return true;
	if (mode & MODE_IS_NUMBER && ch >= '0' && ch <= '9') 
		return true;
	if (mode & MODE_NOT_NUMBER && ch < '0' && ch > '9') 
		return true;
	if (mode & MODE_IS_LETTER && (ParseChar(ch, MODE_UPPERCASE) || ParseChar(ch, MODE_LOWERCASE))) 
		return true;
	if (mode & MODE_NOT_LETTER && (!ParseChar(ch, MODE_UPPERCASE) && !ParseChar(ch, MODE_LOWERCASE))) 
		return true;
	if (mode & MODE_UPPERCASE && ch >= 'A' && ch <= 'Z') 
		return true;
	if (mode & MODE_LOWERCASE && ch >= 'a' && ch <= 'z') 
		return true;
	if (mode & MODE_PUNCTUATION && CharInStr((char*)Punctuation, ch)) 
		return true;
	if (mode & MODE_OPERATOR && CharInStr((char*)Operators, ch)) 
		return true;
	if (mode & MODE_SPECIAL_CHAR && CharInStr((char*)SpecialChars, ch)) 
		return true;

	return false;
}
bool ParseStr(char* str, unsigned int parseMode, unsigned int terminationMode, char* parseCompare, char* terminationCompare, unsigned int* outTerminatedPosition)
{
	if (str == NULL) return false;
	
	unsigned int i = 0;
	while (true)
	{
		char read = *str;
		if (read == '\0') break;
		if (!ParseChar(read, parseMode, parseCompare)) return false;
		if (ParseChar(read, terminationMode, terminationCompare)) return false;
		str++;
		i++;
	}
	if (outTerminatedPosition != NULL) *outTerminatedPosition = i;
	return true;
}

bool CharInStr(char* str, char ch)
{
	if (str == NULL) return false;

	while (true)
	{
		char read = *str;
		if (read == '\0') break;
		if (read == ch) return true;
		str++;
	}
	return false;
}
bool ReadIntoStr(char* read, unsigned int start, unsigned int stop, char* output, unsigned int size)
{
	if (read == NULL || output == NULL || start >= stop || size < 1) return false;

	unsigned int i = start;
	unsigned int r = 0;
	while (true)
	{
		if (read[i] == '\0') break;
		if (i >= stop) break;
		if (r >= size) break;
		output[r] = read[i];
		r++;
		i++;
	}
	return true;
}
bool ForceUppercase(char* str)
{
	if (str == NULL) return false;
	
	char delta = 'A' - 'a';
	while (true)
	{
		char read = *str;
		if (read == '\0') break;
		if (ParseChar(read, MODE_LOWERCASE)) *str += delta;
		str++;
	}
	return true;
}
unsigned int StrLength(char* str)
{
	if (str == NULL) return 0;
	
	unsigned int i = 0;
	while (true)
	{
		char read = *str;
		if (read == '\0') break;
		str++;
		i++;
	}
	return i;
}