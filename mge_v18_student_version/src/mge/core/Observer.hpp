#pragma once

#include <iostream>

struct EventInfo
{
	int activeSwitch = 0;
	int stepTaken = 0;
};

class Observer
{
public:
	Observer();
	virtual ~Observer();
	virtual void OnNotify(const EventInfo& eventInfo) = 0;
};