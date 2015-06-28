#include "..\include\MALib.h"

#ifdef _MA_COUNTER_H_
_MALIB_BEGIN

MALIB_API COUNTER::COUNTER()
{
	this->count = 0;
	this->MAX_COUNT = 0;
}
MALIB_API COUNTER::COUNTER(uint max)
{
	this->count = 0;
	this->MAX_COUNT = max;
}
MALIB_API bool COUNTER::tick()
{
	this->count++;
	if (this->count > this->MAX_COUNT)
	{
		this->count = 0;
		return true;
	}
	return false;
}
MALIB_API void COUNTER::reset()
{
	this->count = 0;
}
MALIB_API void COUNTER::reset(uint newMax)
{
	this->MAX_COUNT = newMax;
	this->reset();
}

_MALIB_END
#endif