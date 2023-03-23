#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_rect.h>

/*
* Programmer:		Ahmed Hammoud
* Description:		This class is designed to handle the properties of different weapons
*/


class WeaponManagement
{
protected:

	//for image rendering
	SDL_Surface* image;
	SDL_Renderer* renderer;
	SDL_Texture* texture;

public:
	//Variables
	bool pistolEnabled, rifleEnabled, reloadStarted, isReloading, shotDelayFlag;
	Uint32 pistolMagSize, rifleMagSize;
	int pistolTimer, pistolTimerDelay, rifleTimer, rifleTimerDelay;
	int pistolTimeBetweenShots, rifleTimeBetweenShots, shotDelay;

	//Constructor
	WeaponManagement();

	bool onCreate(SDL_Renderer* renderer_);
	bool reloading();

	bool delayShots();

	void renderOutOfAmmo(SDL_Renderer* renderer_, float scale, float playerPosX_, float playerPosY_);
};


