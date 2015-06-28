#ifndef __COMPRESSION_H_
#define __COMPRESSION_H_

enum COMPRESSION_TYPE 
{
	COMPRESSION_NONE =    0x0000, 
	COMPRESSION_RLE =     0x0001, 
	COMPRESSION_DEFLATE = 0x0010, 
};

unsigned int CheckLength(char* input, unsigned int readPosition);
bool CheckLength(char* input, unsigned int readPosition, unsigned int checkPosition, 
	unsigned int* outLength, unsigned int* outPosition, unsigned int windowSize = 1024);
bool CheckLength(char* input, unsigned int readPosition, 
	unsigned int* outLength, unsigned int* outPosition, unsigned int windowSize = 1024);

unsigned int ReadPosition(char* input, unsigned int size, char read);

bool WriteOutput(char* output, unsigned int size, unsigned int* outWritePosition, char* str);
bool WriteOutput(char* output, unsigned int size, unsigned int* outWritePosition, char ch);

bool CompressRLE(char* input, char* output, unsigned int size);
bool CompressDEFLATE(char* input, char* output, unsigned int size);

bool DecompressRLE(char* input, char* output, unsigned int size);
bool DecompressDEFLATE(char* input, char* output, unsigned int size);

bool Compress(char* input, char* output, unsigned int size, COMPRESSION_TYPE type = COMPRESSION_NONE);
bool Decompress(char* input, char* output, unsigned int size, COMPRESSION_TYPE type = COMPRESSION_NONE);

#endif