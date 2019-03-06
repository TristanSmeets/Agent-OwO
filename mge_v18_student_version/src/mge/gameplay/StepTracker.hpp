#pragma once

#include "mge/util/EventQueue/EventQueue.hpp"
#include "mge/util/LuaScripting/LuaWrapper.hpp"

class StepTracker : Observer<GeneralEvent>
{
public:
	StepTracker(int level);
	virtual ~StepTracker();
	void OnNotify(const GeneralEvent& info);

private:
	int totalSteps;
	int stepsLeft;
	bool isUnlimited;
	bool sendEvent = false;
};