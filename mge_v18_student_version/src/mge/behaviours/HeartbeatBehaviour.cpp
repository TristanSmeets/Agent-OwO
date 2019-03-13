#include "HeartbeatBehaviour.hpp"

HeartbeatBehaviour::HeartbeatBehaviour(int level) : Observer<GeneralEvent>(), AbstractBehaviour()
{
	lua_State* luaLevelInfo = LuaWrapper::InitializeLuaState("LuaGameScripts/Level/Level_info.lua");
	lua_getglobal(luaLevelInfo, "AmountOfSteps");
	totalSteps = LuaWrapper::GetTableNumber(luaLevelInfo, "Level_" + std::to_string(level));
	
	stepsLeft = totalSteps;
	isUnlimited = totalSteps == -1;

	lua_State* luaAudio = LuaWrapper::InitializeLuaState("LuaGameScripts/Audio.lua");
	maxTime = LuaWrapper::GetNumber<float>(luaAudio, "HeartBeatMaxTime");
	minTime = LuaWrapper::GetNumber<float>(luaAudio, "HeartBeatMinTime");

	updateCurrentThresshold();

	EventQueue::AddObserver(this);
	LuaWrapper::CloseLuaState(luaLevelInfo);
	LuaWrapper::CloseLuaState(luaAudio);
}

HeartbeatBehaviour::~HeartbeatBehaviour()
{
	EventQueue::RemoveObserver(this);
}

void HeartbeatBehaviour::update(float pStep)
{
	if (isUnlimited == false && isPaused == false)
	{
		counter += pStep;
		if (counter >= currentThresshold && isOver == false)
		{
			AudioLocator::GetAudio()->PlaySoundEffect(SFX_HEARTBEAT);
			counter = 0;
		}
	}
}

void HeartbeatBehaviour::OnNotify(const GeneralEvent & info)
{
	if (info.resetLevel)
	{
		stepsLeft = totalSteps;
		updateCurrentThresshold();
		isOver = false;
	}
	if (!isUnlimited)
	{
		stepsLeft -= info.stepsTaken;
		updateCurrentThresshold();
	}
	if (info.showGameOver)
	{
		isOver = true;
	}
	if (info.showPauseScreen || info.showEndDialogue)
		isPaused = true;
	if (info.closePauseScreen || info.isDialogueCompleted)
		isPaused = false;
}

void HeartbeatBehaviour::updateCurrentThresshold()
{
	currentThresshold = Tweener::Lerp(maxTime, minTime, Tweener::EaseIn(Tweener::Flip((float)stepsLeft / (float)totalSteps)));
}

