#pragma once
#include "mge/Audio/SoundEffect.hpp"
#include <assert.h>
#include <algorithm>
#include <map>

class AudioManager
{
public:
	static void PlayMusic(const std::string& filePath);
	static void StopMusic();
	static void SetMusicVolume(float volume);
	static void SetMusicPitch(float pitch);
	static void PlaySoundEffect(SFX sfx);
	static void SetSoundEffect(SFX sfx, SoundEffect& soundEffect);
	static SoundEffect& GetSoundEffect(SFX sfx);

private:
	static sf::Music* bgMusic;
	static std::map<SFX, SoundEffect*> soundEffects;
};