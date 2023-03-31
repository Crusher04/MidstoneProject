#include "SoundEffect.h"


SoundEffect::SoundEffect() : Audio() { 
	loadAudio(); 
	setSoundVolume(100);
}

void SoundEffect::loadAudio()
{
	addAudio("Audio/Sound effect/Weapon SFX/game-gun-shot-1662.mp3"); //0
	addAudio("Audio/Sound effect/Weapon SFX/heavymachinegun-6998.wav"); //1
	addAudio("Audio/Sound effect/Weapon SFX/HitSFX/dirt-hit-83900.wav"); //2
	addAudio("Audio/Sound effect/Weapon SFX/HitSFX/dirt-hit-slow-83900.wav"); //3
	addAudio("Audio/Sound effect/Weapon SFX/Empty-gun-sound-72163.wav"); //4
	addAudio("Audio/Sound effect/Weapon SFX/pistol-cock-6014.wav"); //5

	//New Pistol Audio
	addAudio("Audio/Sound effect/Weapon SFX/ES_9mm Gun Firing - SFX Producer.wav"); //6

	//Walking SFX
	addAudio("Audio/Sound effect/WalkingSFX/ES_Video Game Footsteps 1 - SFX Producer.wav"); //7

	//Menu open and close SFX
	addAudio("Audio/Sound effect/Menu SFX/menu-open-close-104314.wav"); //8

	//Menu click
	addAudio("Audio/Sound effect/Menu SFX/click-button-140881.wav"); //9

	//Zombies hit SFX
	addAudio("Audio/Sound effect/Enemy SFX/zombie-death-sound.mp3"); //10
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
void SoundEffect::setSoundVolume(int v)
{
	Volume = ConvertVolume(v);
}

int SoundEffect::ConvertVolume(int v)
{
	int volume;
	volume = (MIX_MAX_VOLUME * v) / 100;
	std::cout << "Volume of sound effect " << volume << std::endl;
	return volume;
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

		Mix_PlayChannel(CH_WEAPON, mSoundEffectBank[6], 0);
	}
	else {
		Mix_Pause(CH_WEAPON);
	}
}

void SoundEffect::MachineGunAudio(bool fired) const
{
	if (fired == true) {
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
			Mix_PlayChannel(CH_PLAYER, mSoundEffectBank[7], -1);
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
	Mix_PlayChannel(CH_WEAPON, mSoundEffectBank[4], 0);
}


void SoundEffect::ReloadAudio() const
{
	Mix_PlayChannel(CH_WEAPON, mSoundEffectBank[5], 0);
}

void SoundEffect::MenuClick() const
{
	Mix_PlayChannel(CH_MENU, mSoundEffectBank[9], 0);
}

void SoundEffect::MenuOpenClose() const
{
	Mix_PlayChannel(CH_MENU, mSoundEffectBank[8], 0);
}

void SoundEffect::ZombiesHit() 
{
	Mix_Volume(CH_ENEMY, ConvertVolume(30));
	Mix_PlayChannel(CH_ENEMY, mSoundEffectBank[10], 0);
}

void SoundEffect::ChangeChannelVolume(MyEnum channel, int volume)
{
	switch (channel) {
	case CH_PLAYER:
		Mix_Volume(CH_PLAYER, ConvertVolume(volume));
		std::cout << "CH_PLAYER has set at " << volume << "% volume." << std::endl;
		break;


	case CH_WEAPON:
		Mix_Volume(CH_WEAPON, ConvertVolume(volume));
		std::cout << "CH_WEAPON has set at " << volume << "% volume." << std::endl;
		break;


	case CH_ENEMY:
		Mix_Volume(CH_ENEMY, ConvertVolume(volume));
		std::cout << "CH_ENEMY has set at " << volume << "% volume." << std::endl;
		break;


	case CH_MENU:
		Mix_Volume(CH_MENU, ConvertVolume(volume));
		std::cout << "CH_MENU has set at " << volume << "% volume." << std::endl;
		break;
	}
}
