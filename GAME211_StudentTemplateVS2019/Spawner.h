#pragma once
#include "EnemyBody.h"
#include "GameManager.h"
#include <vector>
#include <iostream>
using namespace std;


class Spawner

{

public:
	
	Spawner();

	Spawner(Vec3 pos_);

	void EnemySpawn(float enemyType);

	float enemy;
	SDL_Surface* enemyImage;
	SDL_Texture* enemyTexture;
	SDL_Surface* enemyImage2;
	SDL_Texture* enemyTexture2;
	SDL_Surface* enemyImage3;
	SDL_Texture* enemyTexture3;
	int randomize;
	Vec3 pos;
	
	



};

