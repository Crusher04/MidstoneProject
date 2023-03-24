#include "SoundEffect.h"

enum MyEnum
{
	CH_PLAYER,
	CH_ENEMY
};

void SoundEffect::loadAudio()
{
	addAudio("Audio/Sound effect/Weapon SFX/game-gun-shot-1662.mp3");
	addAudio("C:/Users/nktri/Documents/GitHub/MidstoneProject/GAME211_StudentTemplateVS2019/Audio/Sound effect/Weapon SFX/heavymachinegun-6998.wav");
	addAudio("Audio/Sound effect/Weapon SFX/heavymachinegun-6998.wav");
	addAudio("Audio/Sound effect/Weapon SFX/HitSFX/dirt-hit-83900.wav");
	addAudio("Audio/Sound effect/Weapon SFX/HitSFX/dirt-hit-slow-83900.wav");
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

	Mix_PlayChannel(CH_PLAYER, mSoundEffectBank[which], 0);

	std::cout << "Played Sound: " << which << std::endl;
}

void SoundEffect::PistolAudio(bool fired) const
{
	if (fired == true) {
		Mix_PlayChannel(CH_PLAYER, mSoundEffectBank[0], 0);
	}
	else {
		Mix_Pause(CH_PLAYER);
	}
}

void SoundEffect::MachineGunAudio(bool fired) const
{
	if (fired == true) {
		Mix_PlayChannel(CH_PLAYER, mSoundEffectBank[2], -1);
	}
	else {
		Mix_Pause(CH_PLAYER);
	}
}

void SoundEffect::WalkingAudio(bool walking) const
{
	if (walking == true) {
		Mix_PlayChannel(CH_PLAYER, mSoundEffectBank[4], -1);
	}
	else {
		Mix_Pause(CH_PLAYER);
	}
}

void SoundEffect::SprintingAudio(bool sprinting) const
{
	if (sprinting == true) {
		Mix_PlayChannel(CH_PLAYER, mSoundEffectBank[3], -1);
	}
	else {
		Mix_Pause(CH_PLAYER);
	}
}
