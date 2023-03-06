#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>
#include "Audio.h"
class SoundEffect : public Audio
{
public:
	SoundEffect() : Audio() { loadAudio(); }
	void addAudio(const char* path);

	void playAudio(const int which) const;
	void PistolAudio(bool fired) const;
	void MachineGunAudio(bool fired) const;
	void WalkingAudio(bool walking) const;
private:
	void loadAudio();
	std::vector<Mix_Chunk*> mSoundEffectBank;
};

