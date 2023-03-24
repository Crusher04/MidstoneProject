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
	int pistolTimer, pistolTimerDelay, rifleTimer, rifleTimerDelay, ammoRemaining;
	int pistolTimeBetweenShots, rifleTimeBetweenShots, shotDelay;
	float bulletSpeed;

	//Default Constructor
	WeaponManagement();

	/// <summary>
	/// Sets default variables for our class
	/// </summary>
	/// <param name="renderer_"></param>
	/// <returns></returns>
	bool onCreate(SDL_Renderer* renderer_);

	/// <summary>
	/// Reloads the weapon
	/// </summary>
	/// <returns></returns>
	bool reloading();

	/// <summary>
	/// Checks for that delay for reloading is done
	/// </summary>
	/// <returns></returns>
	bool delayShots();

	/// <summary>
	/// Renders out of ammo UI
	/// </summary>
	/// <param name="renderer_"></param>
	/// <param name="scale"></param>
	/// <param name="playerPosX_"></param>
	/// <param name="playerPosY_"></param>
	void renderOutOfAmmo(SDL_Renderer* renderer_, float scale, float playerPosX_, float playerPosY_);
};


