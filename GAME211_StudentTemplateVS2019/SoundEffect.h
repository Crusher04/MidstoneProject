#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>
#include "Audio.h"
enum MyEnum
{
	CH_PLAYER,
	CH_WEAPON,
	CH_ENEMY,
	CH_MENU,
	CH_ITEM,
};
class SoundEffect : public Audio
{
public:
	SoundEffect();
	// Add the Audio to the vector
	void addAudio(const char* path);

	// Manualy play audio of a specific sound effect
	void playAudio(const int which) const;

	//Play Pistol sound
	void PistolAudio(bool fired) const;

	//Play MachineGun sound in a loop
	void MachineGunAudio(bool fired) const;

	//Play Walking sound in a loop
	void WalkingAudio(bool walking);

	//Play Sprinting sound in a loop
	void SprintingAudio(bool sprinting);

	//Play Empty Magazine sound
	void EmptyMag() const;

	//Convert SoundEffect volume from percentage
	void setSoundVolume(int v);

	int ConvertVolume(int v);

	//Play Reload sound
	void ReloadAudio() const;

	//Play Menu click sound
	void MenuClick() const;

	//Play Menu open and close sound
	void MenuOpenClose() const;

	//Play Zombies hit SFX
	void ZombiesHit();

	//Play Player hit SFX
	void PlayerHit();

	//Play Health Pickup SFX
	void HealthPickup();

	//Play Pickup SFX
	void Pickup();

	//Play Zombies
	void Zombies();

	//Change Volume by Channel
	void ChangeChannelVolume(MyEnum channel, int volume);
private:
	int Volume;
	float ZombieTimer = SDL_GetTicks();
	bool isWalking = false;
	bool isSprinting = false;
	void loadAudio();
	std::vector<Mix_Chunk*> mSoundEffectBank;
};

