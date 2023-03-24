#include "Audio.h"

Audio::Audio()
{
	SDL_Init(SDL_INIT_AUDIO);

	int audio_rate = 44100;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 1024;

	if (Mix_OpenAudio(audio_rate, MIX_DEFAULT_FORMAT, audio_channels, audio_buffers) != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't init audio %s", Mix_GetError());
		exit(-1);
	}
}

Audio::~Audio()
{
	SDL_Quit;
}

void Audio::addAudio()
{
}

void Audio::playAudio()
{
}

void Audio::loadAudio()
{
}
