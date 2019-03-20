#pragma once
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/util/Tweener.hpp"
#include "mge/util/LuaScripting/LuaWrapper.hpp"
#include "mge/util/EventQueue/EventQueue.hpp"
#include "mge/Audio/AudioLocator.hpp"

class HeartbeatBehaviour : public AbstractBehaviour, public Observer<GeneralEvent>
{
public:
	HeartbeatBehaviour(int level);
	~HeartbeatBehaviour();
	void update(float pStep);
	void OnNotify(const GeneralEvent& info);

private:
	//Variables used for playing the sound effect.
	float maxTime;
	float minTime;
	float currentThresshold;
	float counter = 0;
	void updateCurrentThresshold();

	//Steps
	int totalSteps;
	int stepsLeft;
	bool isUnlimited = false;
	bool isOver = false;
	bool isPaused = false;
};