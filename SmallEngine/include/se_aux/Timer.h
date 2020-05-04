#ifndef __TIMER_H__
#define __TIMER_H__
#include <ctime>
class Timer
{
public:
	Timer() { }
	~Timer() { }
	
	void init() { lastLoopTime = clock() * 1.0 / CLOCKS_PER_SEC; }
	double getTime() { return clock() * 1.0 / CLOCKS_PER_SEC; }
	float getElapsedTime() 
	{
		double time = getTime();
		float elapsedTime = (float)(time - lastLoopTime);
		lastLoopTime = time;
		return elapsedTime;
	}
	double getLastLoopTime() {
		return lastLoopTime;
	}

private:
	double lastLoopTime;
};

#endif