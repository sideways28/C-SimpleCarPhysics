#include "GameTime.h"


GameTime::GameTime()
{

}


GameTime::~GameTime()
{

}

void GameTime::StartTimer()
{
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&tick1);
}

void GameTime::StopTimer()
{
	QueryPerformanceCounter(&tick2);
	elapsedTime = (tick2.QuadPart - tick1.QuadPart) * 1000.0f / frequency.QuadPart;
}