#ifndef _MA_LINGUISTICS_H_
#define _MA_LINGUISTICS_H_
_MALIB_BEGIN

#ifndef _INC_STRING
#include <string.h>
#endif

typedef enum PARSE_MODE
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

static const string Punctuation = ",.'`;\"!?";
static const string Operators = "+-*/<>=&|^~";
static const string SpecialChars = "@#$%()[]{}\\:";

bool ParseChar(char ch, uint mode = 0, string compareTo = NULL);
bool ParseStr(string str, uint parseMode, uint terminationMode, string parseCompare = NULL, string terminationCompare = NULL, uint* outTerminatedPosition = NULL);

bool CharInStr(string str, char ch);
bool ReadIntoStr(string read, uint start, uint stop, string output, uint size);
bool ForceUppercase(string str);
uint StrLength(string str);

_MALIB_END
#endif