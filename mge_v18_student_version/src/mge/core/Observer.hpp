#pragma once

#include <iostream>

struct EventInfo
{

};

class Observer
{
public:
	Observer();
	virtual ~Observer();
	virtual void OnNotify(const EventInfo& eventInfo) = 0;
};