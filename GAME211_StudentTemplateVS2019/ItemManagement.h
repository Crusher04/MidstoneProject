#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_rect.h>

/*
* Programmer:		Abay Sidhu
* Description:		This class is designed to handle the properties of different item drops
*/


class ItemManagement
{
protected:

	//for image rendering
	SDL_Surface* image;
	SDL_Renderer* renderer;
	SDL_Texture* texture;



public:

	///Variables

	//Bools for each different item drop
	bool healthDrop, bigHealthDrop;
	
	//Bools for whether an item has dropped or not and if an item is able to be picked up or not
	bool itemDrop;
	bool itemPickup;
	
	
	int dropChance;
	int item;
	int dropPercentage;

	

	int dropTimer, dropTimerDelay;


	class Collider* col;

	//Constructor
	ItemManagement();

	bool onCreate(SDL_Renderer* renderer_);

	SDL_Surface* getImage() { return image; }


	void Render(SDL_Renderer* renderer_, float scale, float playerPosX_, float playerPosY_);

	//Randomly chooses which drop will be spawned
	void RandomizeDrops();

	//Randomly chooses if a drop will be spawned or not
	void Drops();

	//Increases the drop percentage
	//Can be called at the end of each round or can be called for if a player picks up an item
	void IncreaseDropPercentage();




};


