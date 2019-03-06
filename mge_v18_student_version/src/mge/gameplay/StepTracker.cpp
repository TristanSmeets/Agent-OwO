#include "StepTracker.hpp"

StepTracker::StepTracker(int level) : Observer<GeneralEvent>()
{
	std::cout << "Creating StepTracker.\n";
	lua_State* levelInfo = LuaWrapper::InitializeLuaState("LuaGameScripts/Level/Level_info.lua");
	lua_getglobal(levelInfo, "AmountOfSteps");
	totalSteps = LuaWrapper::GetTableNumber(levelInfo, "Level_" + std::to_string(level));
	stepsLeft = totalSteps;
	isUnlimited = stepsLeft == -1;
	EventQueue::AddObserver(this);
}

StepTracker::~StepTracker()
{
	std::cout << "GC running on:StepTracker.\n";
	EventQueue::RemoveObserver(this);
}

void StepTracker::OnNotify(const GeneralEvent & info)
{
	if (info.resetLevel)
	{
		stepsLeft = totalSteps;
		sendEvent = false;
	}

	if (!isUnlimited)
	{
		stepsLeft -= info.stepsTaken;

		if (!isUnlimited && stepsLeft <= 0)
		{
			if (sendEvent == false)
			{
				std::cout << "You're out of steps!\n";
				GeneralEvent info = GeneralEvent();
				info.showGameOver = true;
				EventQueue::QueueEvent(info);
				sendEvent = true;
			}
		}
	}
}
