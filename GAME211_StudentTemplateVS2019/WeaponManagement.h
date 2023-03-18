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
	bool pistolEnabled, rifleEnabled, reloadStarted, isReloading;
	Uint32 pistolMagSize, rifleMagSize;
	int pistolTimer, pistolTimerDelay, rifleTimer, rifleTimerDelay;

	//Constructor
	WeaponManagement();

	void onCreate();
	bool reloading();
};

