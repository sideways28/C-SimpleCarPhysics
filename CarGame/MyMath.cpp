#include "MyMath.h"


MyMath::MyMath()
{
}


MyMath::~MyMath()
{
}

float MyMath::Lerp(float value, float finalValue, float rate)
{
	if (value > finalValue)
	{
		value = finalValue;
	}
	else
	{
		value += rate;
	}

	return value;
}

float MyMath::Clamp(float value, float minValue, float maxValue, float rate)
{
	if (value > maxValue)
	{
		value = maxValue;
	}

	if (value < minValue)
	{
		value = minValue;
	}

	value += rate;

	return value;
}

float MyMath::PingPong(float value, float minValue, float maxValue, float rate)
{
	if (value < minValue)
	{
		value = minValue;
	}

	if (value > maxValue)
	{
		value = maxValue;
	}

	static bool valueIncreasing = true;

	if (value <= minValue)
		valueIncreasing = true;
	else if (value >= maxValue)
		valueIncreasing = false;

	if (valueIncreasing)
	{
		value += rate;
	}
	else
	{
		value -= rate;
	}

	return value;
}
