#include "SoundEffect.h"



void SoundEffect::loadAudio()
{
	addAudio("Audio/Sound effect/Weapon SFX/game-gun-shot-1662.mp3");
	addAudio("C:/Users/nktri/Documents/GitHub/MidstoneProject/GAME211_StudentTemplateVS2019/Audio/Sound effect/Weapon SFX/game-gun-shot-1662.mp3");
}

void SoundEffect::addAudio(const char* path)
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

void SoundEffect::playAudio(const int which) const
{
	if (which > mSoundEffectBank.size() - 1) {
		std::cout << "Sound out of range. \n";
		return;
	}

	Mix_PlayChannel(-1, mSoundEffectBank[which], 0);

	std::cout << "Played Sound: " << which << std::endl;
}
