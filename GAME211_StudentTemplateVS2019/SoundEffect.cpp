#include "SoundEffect.h"

SoundEffect::SoundEffect()
{
	// init sound
	SDL_Init(SDL_INIT_AUDIO);

	int audio_rate = 44100;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 2048;

	if (Mix_OpenAudio(audio_rate, MIX_DEFAULT_FORMAT, audio_channels, audio_buffers) != 0){
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't init audio %s", Mix_GetError());
		exit(-1);
	}
	loadSoundEffect();
}

SoundEffect::~SoundEffect()
{
	SDL_Quit();
}

void SoundEffect::loadSoundEffect()
{
	addSoundEffect("Audio/Sound effect/Weapon SFX/game-gun-shot-1662.mp3");
	addSoundEffect("C:/Users/nktri/Documents/GitHub/MidstoneProject/GAME211_StudentTemplateVS2019/Audio/Sound effect/Weapon SFX/game-gun-shot-1662.mp3");
}

void SoundEffect::addSoundEffect(const char* path)
{
	Mix_Chunk* tmpChunk = Mix_LoadWAV(path);

	if (tmpChunk != nullptr) {
		mSoundEffectBank.push_back(tmpChunk);
		std::cout << (mSoundEffectBank.size() - 1) << ", sound loaded, path: " << path << std::endl;
	}
	else {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't init audio %s", Mix_GetError());
	}
}

void SoundEffect::playSoundEffect(const int which) const
{
	if (which > mSoundEffectBank.size() - 1) {
		std::cout << "Sound out of range. \n";
		return;
	}

	Mix_PlayChannel(-1, mSoundEffectBank[which], 0);

	std::cout << "Played Sound: " << which << std::endl;
}
