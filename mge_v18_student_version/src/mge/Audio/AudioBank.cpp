#include "AudioBank.hpp"

AudioBank::AudioBank() :
	buttonSFX(SoundEffect()),
	pushSFX(SoundEffect()),
	heartbeatSFX(SoundEffect()),
	switchSFX(SoundEffect()),
	failureSFX(SoundEffect()),
	exitSFX(SoundEffect()),
	dialogueSFX(SoundEffect())
{
	luaAudio = LuaWrapper::InitializeLuaState("LuaGameScripts/Audio.lua");
	initializeSFX();
}

AudioBank::~AudioBank()
{
	LuaWrapper::CloseLuaState(luaAudio);
}

SoundEffect & AudioBank::GetSoundEffect(SFX sfx)
{
	switch (sfx)
	{
	case SFX_BUTTON:
		return buttonSFX;
	case SFX_PUSHBOX:
		return pushSFX;
	case SFX_HEARTBEAT:
		return heartbeatSFX;
	case SFX_DIALOGUE:
		return dialogueSFX;
	case SFX_EXIT:
		return exitSFX;
	case SFX_FAILURE:
		return failureSFX;
	case SFX_SWITCH:
		return switchSFX;
	}
}

void AudioBank::initializeSFX()
{
	loadSFX(buttonSFX, SFX::SFX_BUTTON, "Button");
	loadSFX(pushSFX, SFX::SFX_PUSHBOX, "Push");
	loadSFX(heartbeatSFX, SFX::SFX_HEARTBEAT, "HeartBeat");
	loadSFX(switchSFX, SFX::SFX_SWITCH, "Switch");
	loadSFX(failureSFX, SFX::SFX_FAILURE, "Failure");
	loadSFX(exitSFX, SFX::SFX_EXIT, "Exit");
	loadSFX(dialogueSFX, SFX::SFX_DIALOGUE, "Dialogue");
}

void AudioBank::loadSFX(SoundEffect& soundEffect, SFX sfx, const std::string& variableName)
{
	soundEffect.SetSoundEffect(LuaWrapper::GetString(luaAudio, variableName + "SFX"));
	soundEffect.SetVolume(LuaWrapper::GetNumber<float>(luaAudio, variableName + "Volume"));
	soundEffect.SetPitch(LuaWrapper::GetNumber<float>(luaAudio, variableName + "Pitch"));
	soundEffect.SetSFXType(sfx);
}