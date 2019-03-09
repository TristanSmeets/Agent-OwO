#include "AudioLocator.hpp"

IAudio* AudioLocator::iService;

IAudio* AudioLocator::GetAudio()
{
	return iService;
}

void AudioLocator::Provide(IAudio* service)
{
	iService = service;
}