#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>
#include <functional>
class Music
{
public:
	Music();
	~Music();


	void addMusic(const char* path);

	void playMusic(const int which, int volume);

	void Play_Pause();

	int setMusicVolume(int v);
private:
	void loadMusic();
	std::vector<Mix_Music*> mMusicBank;
	bool m_Paused = false;
	bool m_Playing = false;
};

