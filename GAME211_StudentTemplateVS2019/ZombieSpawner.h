#ifndef ZOMBIESPAWNER_H
#define ZOMBIESPAWNER_H


#include <stdio.h>
#include "Body.h"
#include "GameManager.h"
#include <vector>
#include "EntityHealth.h"


class ZombieSpawner : public Body
{
protected:

	class GameManager* game;
	int sprintZombCounter;
	int tankZombCounter;
	int regZombCounter;
	int nextRoundUpgrades;

public:
	
	//Variables
	bool spawned, initZombFlag, tankSpawned, sprintZombSpawned;
	float orientation, zombieIncreasedSpeed;
	class EntityHealth health;
	int currentRound, regZomb, tankZomb, sprintZomb, spitZomb;

	//Constructors
	ZombieSpawner() : Body{}
	{
		game = nullptr;
		initZombFlag = true;
	}

	ZombieSpawner( GameManager* game_) : Body{} ,game{ game_ } {}

	bool OnCreate();
	void Render(float scale = 1.0f);
	void HandleEvents(const SDL_Event& event);
	void Update(float deltaTime);
	void setTexture(SDL_Texture* texture_) { texture = texture_; }
	void setZombieAmount();
	int getZombiesRemaining();
	void zombieArrPushBack(ZombieSpawner zombie_);
	void setZombieGame(GameManager* game_);

};

#endif