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
	//Variables
	bool healthDrop, bigHealthDrop;
	
	bool itemDrop;
	
	int dropChance;
	int item;
	int dropPercentage;


	//Constructor
	ItemManagement();

	bool onCreate(SDL_Renderer* renderer_);




	void Render(SDL_Renderer* renderer_, float scale, float playerPosX_, float playerPosY_);

	
	void RandomizeDrops();

	void Drops();





};


