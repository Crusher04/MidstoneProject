#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>
class SoundEffect
{
public:
	SoundEffect();
	~SoundEffect();
	

	void addSoundEffect(const char* path);

	void playSoundEffect(const int which) const;

private:
	void loadSoundEffect();
	std::vector<Mix_Chunk*> mSoundEffectBank;
};

