#include "AudioBank.hpp"

AudioBank::AudioBank()
{
	initializeSFX();
	luaAudio = LuaWrapper::InitializeLuaState("LuaGameScripts/Audio.lua");
}

AudioBank::~AudioBank()
{
	std::cout << "GC running on:AudioBank.\n";

	LuaWrapper::CloseLuaState(luaAudio);
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

}