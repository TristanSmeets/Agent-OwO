#include "AudioManager.hpp"

std::map<SFX, SoundEffect*> AudioManager::soundEffects;
sf::Music* AudioManager::bgMusic;

void AudioManager::PlayMusic(const std::string & filePath)
{
	bgMusic->openFromFile(filePath);
	bgMusic->setLoop(true);
	bgMusic->play();
}

void AudioManager::StopMusic()
{
	bgMusic->stop();
}

void AudioManager::SetMusicVolume(float volume)
{
	bgMusic->setVolume(volume);
}

void AudioManager::SetMusicPitch(float pitch)
{
	bgMusic->setPitch(pitch);
}

void AudioManager::PlaySoundEffect(SFX sfx)
{
	soundEffects[sfx]->PlaySoundEffect();
}

void AudioManager::SetSoundEffect(SFX sfx, SoundEffect & soundEffect)
{
	soundEffects[sfx] = &soundEffect;
}

SoundEffect & AudioManager::GetSoundEffect(SFX sfx)
{
	return *soundEffects[sfx];
}
