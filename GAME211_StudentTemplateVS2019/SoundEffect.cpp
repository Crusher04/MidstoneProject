#include "SoundEffect.h"

enum MyEnum
{
	CH_PLAYER,
	CH_WEAPON,
	CH_ENEMY
};
SoundEffect::SoundEffect() : Audio() { 
	loadAudio(); 
	setSoundVolume(100);
}

void SoundEffect::loadAudio()
{
	addAudio("Audio/Sound effect/Weapon SFX/game-gun-shot-1662.mp3"); //0
	//addAudio("C:/Users/nktri/Documents/GitHub/MidstoneProject/GAME211_StudentTemplateVS2019/Audio/Sound effect/Weapon SFX/heavymachinegun-6998.wav");
	addAudio("Audio/Sound effect/Weapon SFX/heavymachinegun-6998.wav"); //1
	addAudio("Audio/Sound effect/Weapon SFX/HitSFX/dirt-hit-83900.wav"); //2
	addAudio("Audio/Sound effect/Weapon SFX/HitSFX/dirt-hit-slow-83900.wav"); //3
	addAudio("Audio/Sound effect/Weapon SFX/Empty-gun-sound-72163.wav"); //4
	addAudio("Audio/Sound effect/Weapon SFX/pistol-cock-6014.wav"); //5
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
	// Manualy play audio of a specific sound effect
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
		Mix_Volume(CH_WEAPON, Volume);
		Mix_PlayChannel(CH_WEAPON, mSoundEffectBank[0], 0);
	}
	else {
		Mix_Pause(CH_WEAPON);
	}
}

void SoundEffect::MachineGunAudio(bool fired) const
{
	if (fired == true) {
		Mix_Volume(CH_WEAPON, Volume);
		Mix_PlayChannel(CH_WEAPON, mSoundEffectBank[1], -1);
	}
	else {
		Mix_Pause(CH_WEAPON);
	}
}

void SoundEffect::WalkingAudio(bool walking) 
{

	if (walking == true) {
		if (isWalking == false) {
			Mix_Volume(CH_PLAYER, Volume);
			Mix_PlayChannel(CH_PLAYER, mSoundEffectBank[3], -1);
			isWalking = true;
		}
	}
	else {
		Mix_Pause(CH_PLAYER);
		isWalking = false;
	}
}

void SoundEffect::SprintingAudio(bool sprinting)
{
	if (sprinting == true) {
		if (isSprinting == false) {
			Mix_Volume(CH_PLAYER, Volume);
			Mix_PlayChannel(CH_PLAYER, mSoundEffectBank[2], -1);
			isSprinting = true;
		}
	}
	else {
		Mix_Pause(CH_PLAYER);
		isSprinting = false;
	}
}

void SoundEffect::EmptyMag() const
{
	Mix_Volume(CH_WEAPON, Volume);
	Mix_PlayChannel(CH_WEAPON, mSoundEffectBank[4], 0);
}

void SoundEffect::setSoundVolume(int v)
{
	int volume;
	volume = (MIX_MAX_VOLUME * v) / 100;
	std::cout << "Volume of sound effect " << volume << std::endl;
	Volume = volume;
}

void SoundEffect::ReloadAudio() const
{
	Mix_PlayChannel(CH_WEAPON, mSoundEffectBank[5], 0);
}
