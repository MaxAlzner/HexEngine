#ifndef __COUNTER_H_
#define __COUNTER_H_

class COUNTER
{
public:
	COUNTER();
	COUNTER(const int max);
	bool tick();
	void reset();
	void reset(int newMax);

	int count, MAX_COUNT;
};

#endif