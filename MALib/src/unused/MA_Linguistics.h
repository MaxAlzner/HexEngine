#ifndef __LINGUISTICS_H_
#define __LINGUISTICS_H_

enum PARSE_MODE
{
	MODE_NONE =                0x0000, 
	MODE_IS_NUMBER =           0x0001, 
	MODE_NOT_NUMBER =          0x0002, 
	MODE_IS_LETTER =           0x0004, 
	MODE_NOT_LETTER =          0x0008, 
	MODE_UPPERCASE =           0x0010, 
	MODE_LOWERCASE =           0x0020, 
	MODE_PUNCTUATION =         0x0040, 
	MODE_OPERATOR =            0x0080, 
	MODE_SPECIAL_CHAR =        0x0100, 
};

static const char* Punctuation = ",.'`;\"!?";
static const char* Operators = "+-*/<>=&|^~";
static const char* SpecialChars = "@#$%()[]{}\\:";

bool ParseChar(char ch, unsigned int mode = 0, char* compareTo = NULL);
bool ParseStr(char* str, unsigned int parseMode, unsigned int terminationMode, char* parseCompare = NULL, char* terminationCompare = NULL, unsigned int* outTerminatedPosition = NULL);

bool CharInStr(char* str, char ch);
bool ReadIntoStr(char* read, unsigned int start, unsigned int stop, char* output, unsigned int size);
bool ForceUppercase(char* str);
unsigned int StrLength(char* str);

#endif