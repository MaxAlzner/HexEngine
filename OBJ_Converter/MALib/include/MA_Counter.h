#ifndef _MA_COUNTER_H_
#define _MA_COUNTER_H_
_MALIB_BEGIN

class MALIB_API COUNTER
{
public:
	COUNTER();
	COUNTER(const int max);
	bool tick();
	void reset();
	void reset(int newMax);

	int count, MAX_COUNT;
};

_MALIB_END
#endif