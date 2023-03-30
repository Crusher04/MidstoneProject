#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>
#include "Audio.h"
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

	//Play Reload sound
	void ReloadAudio() const;

	//Play Menu click sound
	void MenuClick() const;

	//Play Menu open and close sound
	void MenuOpenClose() const;
private:
	int Volume;
	bool isWalking = false;
	bool isSprinting = false;
	void loadAudio();
	std::vector<Mix_Chunk*> mSoundEffectBank;
};

