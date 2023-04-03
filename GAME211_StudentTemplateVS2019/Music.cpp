#include "Music.h"



void Music::addAudio(const char* path)
{
	Mix_Music* tmpMusic = Mix_LoadMUS(path);

	if (tmpMusic != nullptr) {
		mMusicBank.push_back(tmpMusic);
		std::cout << (mMusicBank.size() - 1) << ", sound loaded, path: " << path << std::endl;
	}
	else {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't init audio %s", Mix_GetError());
	}
}

void Music::playAudio(const int which, int volume)
{
	if (which > mMusicBank.size() - 1) {
		std::cout << "Music out of range. \n";
		return;
	}
	Mix_VolumeMusic(setMusicVolume(volume));
	Mix_PlayMusic(mMusicBank[which], -1);
	m_Playing = true;
	std::cout << "Played Sound: " << which << std::endl;
}

void Music::Play_Pause()
{
	if (m_Playing && !m_Paused) {
		Mix_PausedMusic();
		m_Paused = true;
	}
	else if (m_Playing && m_Paused) {
		Mix_ResumeMusic();
		m_Paused = false;
	}
	else {
		return;
	}

}

int Music::setMusicVolume(int v)
{
	int volume;
	volume = (MIX_MAX_VOLUME * v) / 100;
	std::cout << "Volume of music " << volume << std::endl;
	return volume;
}

void Music::loadAudio()
{
	addAudio("Audio/BackGround Music/Menu music/ES_As Light Returns - Walt Adams.mp3");//0
	addAudio("Audio/BackGround Music/Menu music/ES_Quiet Waters - Walt Adams.mp3");//1
}
