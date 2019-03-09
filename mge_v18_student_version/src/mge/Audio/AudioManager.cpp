#include "AudioManager.hpp"

AudioManager::AudioManager() : audioBank(AudioBank())
{
	bgMusic = new sf::Music();
}

AudioManager::~AudioManager()
{
	std::cout << "GC running on:AudioManager.\n";
	delete bgMusic;
}

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

void AudioManager::SetMusicType(MusicType musicType)
{
	this->musicType = musicType;
}

MusicType AudioManager::GetMusicType()
{
	return musicType;
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
	audioBank.GetSoundEffect(sfx).PlaySoundEffect();
}

SoundEffect & AudioManager::GetSoundEffect(SFX sfx)
{
	return audioBank.GetSoundEffect(sfx);
}
