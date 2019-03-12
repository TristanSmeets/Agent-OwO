#include "StepTracker.hpp"

StepTracker::StepTracker(int level) : Observer<GeneralEvent>()
{
	lua_State* levelInfo = LuaWrapper::InitializeLuaState("LuaGameScripts/Level/Level_info.lua");
	lua_getglobal(levelInfo, "AmountOfSteps");
	totalSteps = LuaWrapper::GetTableNumber(levelInfo, "Level_" + std::to_string(level));
	stepsLeft = totalSteps;
	isUnlimited = stepsLeft == -1;
	EventQueue::AddObserver(this);
	LuaWrapper::CloseLuaState(levelInfo);
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

		if (!isUnlimited && stepsLeft < 0)
		{
			if (sendEvent == false)
			{
				lua_State* luaAudio = LuaWrapper::InitializeLuaState("LuaGameScripts/Audio.lua");
				float pitch = LuaWrapper::GetNumber<float>(luaAudio, "FailurePitch");
				AudioLocator::GetAudio()->GetSoundEffect(SFX_FAILURE).SetPitch(pitch);
				AudioLocator::GetAudio()->PlaySoundEffect(SFX_FAILURE);
				LuaWrapper::CloseLuaState(luaAudio);

				GeneralEvent info = GeneralEvent();
				info.showGameOver = true;
				EventQueue::QueueEvent(info);
				sendEvent = true;
			}
		}
	}
}
