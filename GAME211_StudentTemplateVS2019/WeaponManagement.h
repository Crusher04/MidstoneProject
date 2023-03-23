#pragma once
#include <SDL.h>
/*
* Programmer:		Ahmed Hammoud
* Description:		This class is designed to handle the properties of different weapons
*/

class WeaponManagement
{
public:
	//Variables
	bool pistolEnabled, rifleEnabled, reloadStarted, isReloading, shotDelayFlag;
	Uint32 pistolMagSize, rifleMagSize;
	int pistolTimer, pistolTimerDelay, rifleTimer, rifleTimerDelay;
	int pistolTimeBetweenShots, rifleTimeBetweenShots, shotDelay;

	//Constructor
	WeaponManagement();

	void onCreate();
	bool reloading();

	bool delayShots();

};


