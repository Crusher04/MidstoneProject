/*
* Programmer:		Ahmed Hammoud
*/
#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class NumbersUI
{
protected:

	
	//for image rendering
	SDL_Renderer* renderer;

	SDL_Surface* imageOne;
	SDL_Surface* imageTwo;
	SDL_Surface* imageThree;
	SDL_Surface* imageFour;
	SDL_Surface* imageFive;
	SDL_Surface* imageSix;
	SDL_Surface* imageSeven;
	SDL_Surface* imageEight;
	SDL_Surface* imageNine;
	SDL_Surface* imageZero;
	
	SDL_Texture* textureOne;
	SDL_Texture* textureTwo;
	SDL_Texture* textureThree;
	SDL_Texture* textureFour;
	SDL_Texture* textureFive;
	SDL_Texture* textureSix;
	SDL_Texture* textureSeven;
	SDL_Texture* textureEight;
	SDL_Texture* textureNine;
	SDL_Texture* textureZero;

public:

	//For Categorizing the numbers
	int ones, tens, hundreds, thousands;
	float screenX, screenY;

	NumbersUI();

	/// <summary>
	/// Initializes our values and graphics rendering
	/// </summary>
	/// <returns></returns>
	void OnCreate(SDL_Renderer* renderer_);

	/// <summary>
	/// Renders the numbers on screen
	/// </summary>
	/// <param name="renderer_"></param>
	/// <param name="scale"></param>
	void Render(SDL_Renderer* renderer_, float scale, int currentRound);
};

