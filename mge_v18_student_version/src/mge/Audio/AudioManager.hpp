#pragma once
#include "mge/Audio/IAudio.hpp"
#include "mge/Audio/AudioBank.hpp"
#include <assert.h>
#include <algorithm>
#include <map>

class AudioManager : public IAudio
{
public:
	AudioManager();
	~AudioManager();
	void PlayMusic(const std::string& filePath);
	void StopMusic();
	void SetMusicType(MusicType musicType);
	MusicType GetMusicType();
	void SetMusicVolume(float volume);
	void SetMusicPitch(float pitch);
	void PlaySoundEffect(SFX sfx);
	SoundEffect& GetSoundEffect(SFX sfx);

private:
	AudioBank audioBank;
	sf::Music* bgMusic;
	MusicType musicType;
};