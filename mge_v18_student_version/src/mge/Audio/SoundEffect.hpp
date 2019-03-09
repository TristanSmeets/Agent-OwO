#pragma once
#include "SFML/Audio.hpp"
#include <iostream>
#include "mge/Audio/AudioEnums.hpp"

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