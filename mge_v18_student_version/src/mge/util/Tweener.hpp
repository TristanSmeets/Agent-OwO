#pragma once

class Tweener
{
public:
	static float Lerp(float startValue, float endValue, float percentage);
	static float EaseIn(float t);
	static float EaseOut(float t);
	static float Flip(float t);
};