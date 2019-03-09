#pragma once
#include "mge/Audio/SoundEffect.hpp"

class IAudio
{
public:
	virtual ~IAudio() {}
	virtual void PlayMusic(const std::string& filePath) = 0;
	virtual void StopMusic() = 0;
	virtual void SetMusicVolume(float volume) = 0;
	virtual void SetMusicPitch(float pitch) = 0;
	virtual void PlaySoundEffect(SFX sfx) = 0;
	virtual SoundEffect& GetSoundEffect(SFX sfx) = 0;
};