#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>
#include "Audio.h"

class Music : public Audio
{
public:
	Music() : Audio() { loadAudio(); }

	void addAudio(const char* path);

	void playAudio(const int which, int volume);

	void Play_Pause();

	int setMusicVolume(int v);
private:
	void loadAudio();
	std::vector<Mix_Music*> mMusicBank;
	bool m_Paused = false;
	bool m_Playing = false;
};

