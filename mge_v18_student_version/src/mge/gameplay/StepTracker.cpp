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
	if (info.ResetLevel)
		stepsLeft = totalSteps;

	if (!isUnlimited)
	{
		stepsLeft -= info.stepsTaken;
		std::cout << "Steps Left: " << stepsLeft << std::endl;

		if (!isUnlimited && stepsLeft <= 0)
		{
			std::cout << "You're out of steps!\n";
		}
	}
	else
		std::cout << "Unlimited steps.\n";
}
