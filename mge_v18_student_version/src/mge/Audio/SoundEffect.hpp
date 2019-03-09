#pragma once
#include "SFML/Audio.hpp"
#include <iostream>

enum SFX {SFX_PUSHBOX, SFX_SWITCH, SFX_FAILURE, SFX_EXIT, SFX_HEARTBEAT, SFX_DIALOGUE, SFX_BUTTON};

class SoundEffect
{
public:
	SoundEffect();
	~SoundEffect();
	void SetSoundEffect(const std::string& filePath);
	sf::Sound& GetSound();
	void SetVolume(float volume);
	float GetVolume();
	void PlaySoundEffect();
	void SetPitch(float pitch);
	void SetSFXType(SFX sfxType);
	SFX GetSFXType();

private:
	sf::SoundBuffer buffer;
	sf::Sound sound;
	SFX sfxType;
};