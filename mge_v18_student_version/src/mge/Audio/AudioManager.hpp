#pragma once
#include "mge/Audio/SoundEffect.hpp"
#include <assert.h>
#include <algorithm>
#include <map>

class AudioManager
{
public:
	static void PlaySoundEffect(SFX sfx);
	static void SetSoundEffect(SFX sfx, SoundEffect& soundEffect);
	static SoundEffect& GetSoundEffect(SFX sfx);

private:
	static std::map<SFX, SoundEffect&> soundEffects;
};