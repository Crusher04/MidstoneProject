/*
* Progammer:	Ahmed Hammoud
* Date:			March 24/2023
*/

#ifndef Bullet_H
#define Bullet_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Body.h"
#include "Collider.h"

class Bullet : public Body
{
protected:
	
	//for image rendering
	SDL_Renderer* renderer;
	SDL_Surface* image;
	SDL_Texture* texture;
	int mouse_X, mouse_Y, ammo;
	

public:
	//variable
	bool fired;
	bool chamberRelease;
	bool active;
	bool pushedBack;
	Collider collider;
	int bulletDamage;

	//Functions
	Bullet();
	void OnCreate(SDL_Renderer* renderer_);
	void Render(float scale, float playerX, float playerY);
	void Shoot(float deltaTime, float playerX, float playerY, float bulletSpeed);
	void Update(float deltaTime);

};

#endif /* PLAYERBODY_H */
