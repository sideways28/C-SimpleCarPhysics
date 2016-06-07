#pragma once
#include <Windows.h>

class GameTime
{
public:
	GameTime();
	~GameTime();

	void StartTimer();
	void StopTimer();
	double elapsedTime;

private:
	LARGE_INTEGER frequency;//ticks per second
	LARGE_INTEGER tick1;//tick
	LARGE_INTEGER tick2;//tick
};

