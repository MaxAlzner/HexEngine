#ifndef __ENCODING_H_
#define __ENCODING_H_

static char Base2[] = {'0', '1', '\0'};
static char Base8[] = {'0', '1', '2', '3', '4', '5', '6', '7', '\0'};
static char Base10[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '\0'};
static char Base16[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', '\0'};
static char BaseText[] = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

unsigned int BitMask(unsigned int bytesize, unsigned int bit);
void ClearBit(void* data, unsigned int bytesize, unsigned int bit);
void ToggleBit(void* data, unsigned int bytesize, unsigned int bit);
void SetBit(void* data, unsigned int bytesize, unsigned int bit);
bool CheckBit(void* data, unsigned int bytesize, unsigned int bit);

unsigned int GetDigitValue(const char* base, char digit);
char GetDigitSymbol(const char* base, unsigned int symbol);
unsigned int GetNumericValue(const char* base, const char* str);
unsigned int GetNumericValue(const char* base, const char* str, unsigned int start, unsigned int end);
unsigned int GetNumericValues(const char* base, const char* str, unsigned int wordLength, unsigned int* buffer, unsigned int bufferSize);
void GetEncoding(const char* base, unsigned int number, char* resultBuffer, unsigned int bufferSize);
bool GetEncoding(const char* base, unsigned int number, unsigned int decodeDigits, char* resultBuffer, unsigned int bufferSize);

unsigned int Encrypt(unsigned int x, unsigned int* key, unsigned int n);
unsigned int Decrypt(unsigned int x, unsigned int* key, unsigned int n);

#endif