#ifndef _MA_COUNTER_H_
#define _MA_COUNTER_H_
_MALIB_BEGIN

struct MALIB_API COUNTER
{
	COUNTER();
	COUNTER(const uint max);
	bool tick();
	void reset();
	void reset(uint newMax);

	uint count;
	uint MAX_COUNT;
};

_MALIB_END
#endif