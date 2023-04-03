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
	addAudio("Audio/Sound effect/ES_Button Push 4 - SFX Producer.wav"); //9

	//Zombies hit SFX
	addAudio("Audio/Sound effect/Enemy SFX/ES_Bullet Impact Flesh 1 - SFX Producer.wav"); //10

	//Player hit SFX
	addAudio("Audio/Sound effect/Weapon SFX/HitSFX/Player-hit-47201.wav"); //11

	//Health pickup SFX
	addAudio("Audio/Sound effect/health-pickup-6860.wav"); //12

	//Pickup SFX
	addAudio("Audio/Sound effect/coin-pickup-98269.wav"); //13

	//Zombie SFX
	addAudio("Audio/Sound effect/Enemy SFX/zombie-attack-104988.mp3"); //14

	//More Zombies Hit SFX
	addAudio("Audio/Sound effect/Enemy SFX/ES_Bullet Impact Flesh 5 - SFX Producer.wav"); //15
	addAudio("Audio/Sound effect/Enemy SFX/ES_Bullet Impact Flesh 4 - SFX Producer.wav"); //16

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
	std::cout << "Volume of sound effect " << v << std::endl;
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
	std::srand((unsigned int)time(NULL));
	int location = (rand() % 15) + 1;
	while(location != 10 && location != 16 && location != 15)
		location = (rand() % 15) + 10;

	Mix_PlayChannel(CH_ENEMY, mSoundEffectBank[location], 0);
}

void SoundEffect::PlayerHit()
{
	Mix_PlayChannel(CH_PLAYER, mSoundEffectBank[11], 0);
}

void SoundEffect::HealthPickup()
{
	Mix_PlayChannel(CH_ITEM, mSoundEffectBank[12], 0);
}

void SoundEffect::Pickup()
{
	Mix_PlayChannel(CH_ITEM, mSoundEffectBank[13], 0);
}

void SoundEffect::Zombies()
{
	/*if (ZombieTimer <= SDL_GetTicks()) {
		ZombieTimer = SDL_GetTicks() + 5000;
		Mix_PlayChannel(CH_ENEMY, mSoundEffectBank[14], 0);
	}*/
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


	case CH_ITEM:
		Mix_Volume(CH_ITEM, ConvertVolume(volume));
		std::cout << "CH_ITEM has set at " << volume << "% volume." << std::endl;
		break;
	}
}

