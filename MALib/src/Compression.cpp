#include "..\main.h"

unsigned int CheckLength(char* input, unsigned int readPosition)
{
	if (input == NULL) return 0;

	char read = input[readPosition];
	unsigned int runLength = 1;
	while (input[readPosition + runLength] == read)
	{
		runLength++;
	}
	return runLength;
}
bool CheckLength(char* input, unsigned int readPosition, unsigned int checkPosition, 
	unsigned int* outLength, unsigned int* outPosition, unsigned int windowSize)
{
	if (input == NULL || outLength == NULL || outPosition == NULL) return false;
	
	*outLength = 0;
	*outPosition = checkPosition;
	if (checkPosition >= readPosition) return false;
	while (input[checkPosition] == input[readPosition])
	{
		checkPosition++;
		readPosition++;
		(*outLength)++;
	}

	return true;
}
bool CheckLength(char* input, unsigned int readPosition, 
	unsigned int* outLength, unsigned int* outPosition, unsigned int windowSize)
{
	if (input == NULL || outLength == NULL || outPosition == NULL) return false;
	
	unsigned int checkPosition = readPosition - windowSize;
	if (readPosition < windowSize) checkPosition = 0;
	*outLength = 0;
	*outPosition = 0;
	while (true)
	{
		unsigned int candidateLength = 0;
		unsigned int candidatePosition = checkPosition;
		CheckLength(input, readPosition, checkPosition, &candidateLength, &candidatePosition);

		if (candidateLength == 0) checkPosition++;
		checkPosition += candidateLength;
		if (candidateLength > *outLength)
		{
			*outLength = candidateLength;
			*outPosition = candidatePosition;
		}
		if (checkPosition >= readPosition) break;
	}

	return true;
}

unsigned int ReadPosition(char* input, unsigned int size, char read)
{
	if (input == NULL) return 0;

	for (unsigned i = 0; i < size; i++)
	{
		if (input[i] == read) 
			return i;
	}
	return 0;
}
bool ReadInto(char* input, char* output, unsigned int size, unsigned int readPosition, unsigned int readLength)
{
	if (input == NULL || output == NULL || size < 1) return false;
	
	unsigned int length = strlen(input);
	if (readPosition >= length) return false;
	//if (readPosition + readLength >= length) return false;
	unsigned int writePosition = 0;
	for (unsigned int i = 0; i < readLength; i++)
	{
		char read = input[i + readPosition];
		if (read == '\0') 
			read = input[length - 1];
		WriteOutput(output, size, &writePosition, read);
	}
	return true;
}

bool WriteOutput(char* output, unsigned int size, unsigned int* outWritePosition, char* str)
{
	if (output == NULL || outWritePosition == NULL || str == NULL || size < 1) return false;

	unsigned int length = strlen(str);
	for (unsigned int i = 0; i < length; i++) 
		WriteOutput(output, size, outWritePosition, str[i]);
	return true;
}
bool WriteOutput(char* output, unsigned int size, unsigned int* outWritePosition, char ch)
{
	if (output == NULL || outWritePosition == NULL || size < 1) return false;

	output[*outWritePosition] = ch;
	(*outWritePosition)++;
	output[*outWritePosition] = '\0';
	return true;
}

bool CompressRLE(char* input, char* output, unsigned int size)
{
	if (input == NULL || output == NULL || size < 1) return false;

	unsigned int length = strlen(input);
	unsigned int readPosition = 0;
	unsigned int writePosition = 0;
	char* code = new char[16];
	while (true)
	{
		if (readPosition >= length) break;
		char read = input[readPosition];
		unsigned int runLength = CheckLength(input, readPosition);
		if (runLength > 5)
		{
			ZeroMemory(code, sizeof(char) * 16);
			sprintf(code, "~%d:%c;", runLength, read);
			WriteOutput(output, size, &writePosition, code);
			readPosition += runLength;
		}
		else
		{
			if (read == '~') 
				WriteOutput(output, size, &writePosition, "~;");
			else 
				WriteOutput(output, size, &writePosition, read);
			readPosition++;
		}
	}
	delete [] code;

	return true;
}
bool CompressDEFLATE(char* input, char* output, unsigned int size)
{
	if (input == NULL || output == NULL || size < 1) return false;

	unsigned int length = strlen(input);
	unsigned int readPosition = 0;
	unsigned int writePosition = 0;
	char* code = new char[16];
	while (true)
	{
		if (readPosition >= length) break;
		char read = input[readPosition];
		unsigned int resultLength = 0;
		unsigned int resultPosition = 0;
		CheckLength(input, readPosition, &resultLength, &resultPosition);
		if (resultLength > 4)
		{
			ZeroMemory(code, sizeof(char) * 16);
			sprintf(code, "~%d:%d;", resultPosition, resultLength);
			WriteOutput(output, size, &writePosition, code);
			readPosition += resultLength;
		}
		else
		{
			if (read == '~') 
				WriteOutput(output, size, &writePosition, "~;");
			else 
				WriteOutput(output, size, &writePosition, read);
			readPosition++;
		}
	}
	delete [] code;

	return true;
}

bool DecompressRLE(char* input, char* output, unsigned int size)
{
	if (input == NULL || output == NULL || size < 1) return false;
	
	unsigned int length = strlen(input);
	unsigned int readPosition = 0;
	unsigned int writePosition = 0;
	while (true)
	{
		if (readPosition >= length) break;
		char read = input[readPosition];
		if (read == '~')
		{
			unsigned int endPosition = ReadPosition(input, length - readPosition, ';');
			unsigned int num = 0;
			char letter = ' ';
			sscanf_s(input + readPosition, "~%d:%c;", &num, &letter);
			for (unsigned i = 0; i < num; i++) 
				WriteOutput(output, size, &writePosition, letter);
			readPosition += endPosition + 1;
		}
		else
		{
			WriteOutput(output, size, &writePosition, read);
			readPosition++;
		}
	}

	return true;
}
bool DecompressDEFLATE(char* input, char* output, unsigned int size)
{
	if (input == NULL || output == NULL || size < 1) return false;
	
	unsigned int length = strlen(input);
	unsigned int readPosition = 0;
	unsigned int writePosition = 0;
	char* code = new char[size];
	while (true)
	{
		if (readPosition >= length) break;
		char read = input[readPosition];
		if (read == '~')
		{
			ZeroMemory(code, sizeof(code) * length);
			unsigned int endPosition = ReadPosition(input + readPosition, length - readPosition, ';');
			unsigned int compressPosition = 0;
			unsigned int compressLength = 0;
			sscanf_s(input + readPosition, "~%d:%d;", &compressPosition, &compressLength);
			ReadInto(output, code, length, compressPosition, compressLength);
			WriteOutput(output, size, &writePosition, code);
			readPosition += endPosition + 1;
		}
		else
		{
			WriteOutput(output, size, &writePosition, read);
			readPosition++;
		}
	}
	delete [] code;

	return true;
}

bool Compress(char* input, char* output, unsigned int size, COMPRESSION_TYPE type)
{
	switch (type)
	{
	case COMPRESSION_RLE:
		return CompressRLE(input, output, size);
		break;
	case COMPRESSION_DEFLATE:
		return CompressDEFLATE(input, output, size);
		break;
	default:
		break;
	}
	return false;
}
bool Decompress(char* input, char* output, unsigned int size, COMPRESSION_TYPE type)
{
	switch (type)
	{
	case COMPRESSION_RLE:
		return DecompressRLE(input, output, size);
		break;
	case COMPRESSION_DEFLATE:
		return DecompressDEFLATE(input, output, size);
		break;
	default:
		break;
	}
	return false;
}