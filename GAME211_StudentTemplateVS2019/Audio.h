#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>
class Audio
{
public:
	Audio();
	virtual ~Audio();
	virtual void addAudio();
	virtual void playAudio();
	virtual void loadAudio();

};

