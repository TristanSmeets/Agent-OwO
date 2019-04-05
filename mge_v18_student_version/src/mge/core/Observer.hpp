#pragma once

#include <iostream>

template <typename T> class Observer
{
public:
	Observer() {};
	virtual ~Observer() 
	{
	};
	virtual void OnNotify(const T& eventInfo) = 0;
};