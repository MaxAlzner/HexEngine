#include "StdAfx.h"

COUNTER::COUNTER()
{
	this->count = 0;
	this->MAX_COUNT = 0;
}
COUNTER::COUNTER(int max)
{
	this->count = 0;
	this->MAX_COUNT = max;
}
bool COUNTER::tick()
{
	this->count++;
	if (this->count > this->MAX_COUNT)
	{
		this->count = 0;
		return true;
	}
	return false;
}
void COUNTER::reset()
{
	this->count = 0;
}
void COUNTER::reset(int newMax)
{
	this->MAX_COUNT = newMax;
	this->reset();
}