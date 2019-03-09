#include "AudioManager.hpp"

std::map<SFX, SoundEffect&> AudioManager::soundEffects;

void AudioManager::PlaySoundEffect(SFX sfx)
{
	soundEffects[sfx].PlaySoundEffect();
}

void AudioManager::SetSoundEffect(SFX sfx, SoundEffect & soundEffect)
{
	soundEffects[sfx] = soundEffect;
}

SoundEffect & AudioManager::GetSoundEffect(SFX sfx)
{
	return soundEffects[sfx];
}
