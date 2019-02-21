#pragma once

#include <iostream>

struct EventInfo
{
	int switchState = 0;
};

class Observer
{
public:
	Observer();
	virtual ~Observer();
	virtual void OnNotify(const EventInfo& eventInfo) = 0;
};