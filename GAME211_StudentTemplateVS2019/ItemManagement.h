#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_rect.h>
#include "Collider.h"

/*
* Programmer:			Abay Sidhu
* Programmer Assist:	Ahmed Hammoud
* Description:			This class is designed to handle the properties of different item drops
*/


class ItemManagement
{
protected:

	//for image rendering
	SDL_Renderer* renderer;
	SDL_Surface* healthImage;
	SDL_Texture* healthTexture;
	SDL_Surface* goldenGunImage;
	SDL_Texture* goldenGunTexture;
	SDL_Surface* speedBoostImage;
	SDL_Texture* speedBoostTexture;

public:

	///Variables

	//Bools for each different item drop
	bool healthDrop, goldenGunDrop, speedBoostDrop;
	
	//Bools for whether an item has dropped or not and if an item is able to be picked up or not
	bool itemDrop;
	bool itemPickup;
	
	
	int dropChance;
	int item;
	int dropPercentage;


	int dropTimer, dropTimerDelay;

	Collider collider;

	//Constructor
	ItemManagement();

	bool onCreate(SDL_Renderer* renderer_);

	SDL_Surface* getImage() { return healthImage; }



	void RenderHealth(SDL_Renderer* renderer_, float scale, float playerPosX_, float playerPosY_);

	void RenderGoldenGun(SDL_Renderer* renderer_, float scale, float playerPosX_, float playerPosY_);

	void RenderSpeedBoost(SDL_Renderer* renderer_, float scale, float playerPosX_, float playerPosY_);

	//Randomly chooses which drop will be spawned
	void RandomizeDrops();

	//Randomly chooses if a drop will be spawned or not
	void Drops();

	//Increases the drop percentage
	//Can be called at the end of each round or can be called for if a player picks up an item
	void IncreaseDropPercentage();

	void ResetBools();


};


