#pragma once

#include <iostream>

template <typename T> class Observer
{
public:
	Observer() {};
	virtual ~Observer() 
	{
		std::cout << "GC running on:Observer\n";
	};
	virtual void OnNotify(const T& eventInfo) = 0;
};