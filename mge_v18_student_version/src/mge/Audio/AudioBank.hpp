#pragma once

#include "mge/Audio/AudioLocator.hpp"
#include "mge/Audio/SoundEffect.hpp"
#include "mge/util/LuaScripting/LuaWrapper.hpp"

class AudioBank
{
public:
	AudioBank();
	~AudioBank();
	SoundEffect& GetSoundEffect(SFX sfx);
private:
	void initializeSFX();
	void loadSFX(SoundEffect& soundEffect, SFX sfx, const std::string& variableName);
	lua_State* luaAudio;
	SoundEffect buttonSFX;
	SoundEffect pushSFX;
	SoundEffect heartbeatSFX;
	SoundEffect switchSFX;
	SoundEffect failureSFX;
	SoundEffect exitSFX;
	SoundEffect dialogueSFX;
};