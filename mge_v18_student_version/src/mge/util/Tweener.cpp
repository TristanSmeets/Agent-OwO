#include "Tweener.hpp"

float Tweener::Lerp(float startValue, float endValue, float percentage)
{
	return (startValue + (endValue - startValue) * percentage);
}

float Tweener::EaseIn(float t)
{
	return t * t;
}

float Tweener::EaseOut(float t)
{
	return Flip(EaseIn(Flip(t)));
}

float Tweener::Flip(float t)
{
	return 1 - t;
}
