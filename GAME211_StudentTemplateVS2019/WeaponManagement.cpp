#include "WeaponManagement.h"

WeaponManagement::WeaponManagement() {}

void WeaponManagement::onCreate()
{
	pistolEnabled = true;
	rifleEnabled, reloadStarted, isReloading, shotDelayFlag = false;
	pistolMagSize = 7;
	rifleMagSize = 10;
	pistolTimer, pistolTimerDelay, rifleTimer, rifleTimerDelay = 0;
	pistolTimeBetweenShots = 1000;
	rifleTimeBetweenShots = 200;
	shotDelay = 0;
}

bool WeaponManagement::reloading()
{
	if (!isReloading)
	{
		isReloading = true;
		pistolTimer = SDL_GetTicks();
		pistolTimerDelay = pistolTimer + 1000;
	}
	else
	{
		if (SDL_GetTicks() > pistolTimerDelay)
			isReloading = false;
	}
	

	return isReloading;
}

bool WeaponManagement::delayShots()
{
	
	if (shotDelay > (SDL_GetTicks() + pistolTimeBetweenShots))
		shotDelayFlag = true;
	else
		shotDelayFlag = false;

	return shotDelayFlag;
}
