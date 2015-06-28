#include "..\include\MALib.h"

unsigned int BitMask(unsigned int bytesize, unsigned int bit)
{
	while (bit > bytesize) bit -= bytesize;
	return ((unsigned int)1) << bit;
}
void ClearBit(void* data, unsigned int bytesize, unsigned int bit)
{
	if (data == NULL) return;
	unsigned int* n = (unsigned int*)data;
	unsigned int m = BitMask(bytesize, bit);
	*n &= ~m;
}
void ToggleBit(void* data, unsigned int bytesize, unsigned int bit)
{
	if (data == NULL) return;
	unsigned int* n = (unsigned int*)data;
	unsigned int m = BitMask(bytesize, bit);
	*n ^= m;
}
void SetBit(void* data, unsigned int bytesize, unsigned int bit)
{
	if (data == NULL) return;
	unsigned int* n = (unsigned int*)data;
	unsigned int m = BitMask(bytesize, bit);
	*n |= m;
}
bool CheckBit(void* data, unsigned int bytesize, unsigned int bit)
{
	if (data == NULL) return false;
	unsigned int n = *(unsigned int*)data;
	unsigned int m = BitMask(bytesize, bit);
	if (n & m) 
		return true;
	return false;
}

unsigned int GetDigitValue(const char* base, char digit)
{
	if (base == NULL) return 0;
	unsigned int l = strlen(base);
	for (unsigned i = 0; i < l; i++)
	{
		if (base[i] == digit) 
			return i;
	}
	return 0;
}
char GetDigitSymbol(const char* base, unsigned int symbol)
{
	if (base == NULL) return '\0';
	unsigned int l = strlen(base);
	if (symbol < 0) return '\0';
	if (symbol >= l) return '\0';
	return base[symbol];
}
unsigned int GetNumericValue(const char* base, const char* str)
{
	return GetNumericValue(base, str, 0, strlen(str));
}
unsigned int GetNumericValue(const char* base, const char* str, unsigned int start, unsigned int end)
{
	if (end <= start) return 0;
	if (base == NULL || str == NULL) return 0;
	unsigned int b = strlen(base);
	unsigned int l = strlen(str);
	if (end > l) end = l - 1;

	unsigned int n = 0;
	for (unsigned int i = start; i < end; i++)
	{
		unsigned int digit = (end - i) - 1;
		unsigned int v = (unsigned int)powf(float(b), float(digit));
		n += v * GetDigitValue(base, str[i]);
	}
	return n;
}
unsigned int GetNumericValues(const char* base, const char* str, unsigned int wordLength, unsigned int* buffer, unsigned int bufferSize)
{
	if (base == NULL || str == NULL || buffer == NULL) return 0;
	if (wordLength < 1 || bufferSize < 1) return 0;
	unsigned int l = strlen(str);
	if (wordLength > l) wordLength = l;
	if (bufferSize < l / wordLength) return 0;

	unsigned int start = 0;
	unsigned int end = wordLength;
	unsigned int i = 0;
	while (true)
	{
		if (i >= bufferSize) {i--;break;}
		buffer[i] = GetNumericValue(base, str, start, end);
		start += wordLength;
		end += wordLength;
		i++;
		if (end >= l) end = l;
		if (start >= l) break;
	}
	return i;
}
void GetEncoding(const char* base, unsigned int number, char* resultBuffer, unsigned int bufferSize)
{
	if (base == NULL || resultBuffer == NULL) return;
	char* scratch = new char[bufferSize];
	unsigned int l = strlen(base);
	unsigned int v = 0;
	unsigned int i = 0;

	while (true)
	{
		v = number % l;
		scratch[i] = GetDigitSymbol(base, v);
		i++;
		number = number / l;
		if (number <= 0) break;
	}

	unsigned n = 0;
	for (unsigned m = i; m >= 1; m--)
	{
		resultBuffer[n] = scratch[m - 1];
		resultBuffer[n + 1] = '\0';
		n++;
	}

	delete [] scratch;
}
bool GetEncoding(const char* base, unsigned int number, unsigned int decodeDigits, char* resultBuffer, unsigned int bufferSize)
{
	if (base == NULL || resultBuffer == NULL) return false;
	if (decodeDigits < 1) return false;
	unsigned int l = strlen(base);
	unsigned int v = 0;
	int i = decodeDigits - 1;

	while (true)
	{
		v = number % l;
		resultBuffer[i] = GetDigitSymbol(base, v);
		i--;
		number = number / l;
		if (i < 0) break;
		if (number <= 0) break;
	}

	while (i >= 0)
	{
		resultBuffer[i] = GetDigitSymbol(base, 0);
		i--;
	}

	return true;
}

unsigned int Encrypt(unsigned int x, unsigned int* key, unsigned int n)
{
	for (unsigned i = 0; i < n; i++) x ^= key[i];
	return x;
}
unsigned int Decrypt(unsigned int x, unsigned int* key, unsigned int n)
{
	for (unsigned i = n; i > 0; i--) x ^= key[i - 1];
	return x;
}