#include "SoundEffect.hpp"

SoundEffect::SoundEffect()
{
}

SoundEffect::~SoundEffect()
{
	std::cout << "GC running on:SoundEffect.\n";
}

void SoundEffect::SetSoundEffect(const std::string & filePath)
{
	buffer.loadFromFile(filePath);
	sound.setBuffer(buffer);
}

sf::Sound & SoundEffect::GetSound()
{
	return sound;
}

void SoundEffect::SetVolume(float volume)
{
	sound.setVolume(volume);
}

float SoundEffect::GetVolume()
{
	return sound.getVolume();
}

void SoundEffect::PlaySoundEffect()
{
	sound.play();
}

void SoundEffect::SetPitch(float pitch)
{
	sound.setPitch(pitch);
}

void SoundEffect::SetSFXType(SFX sfxType)
{
	this->sfxType = sfxType;
}

SFX SoundEffect::GetSFXType()
{
	return sfxType;
}

