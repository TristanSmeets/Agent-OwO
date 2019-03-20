#pragma once

#include "mge/Audio/IAudio.hpp"

class AudioLocator
{
public:
	static IAudio* GetAudio();
	static void Provide(IAudio* service);
private:
	static IAudio* iService;
};