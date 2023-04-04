#ifndef ZOMBIESPAWNER_H
#define ZOMBIESPAWNER_H


#include <stdio.h>
#include "Body.h"
#include "GameManager.h"
#include <vector>
#include "EntityHealth.h"
#include "Collider.h"

class ZombieSpawner : public Body
{
protected:

	//Variables
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
	Collider collider;

	//Constructors
	ZombieSpawner() : Body{}
	{
		game = nullptr;
		initZombFlag = true;
	}

	ZombieSpawner( GameManager* game_) : Body{} ,game{ game_ } {}

	/// <summary>
	/// Initialize variables and scene param in OnCreate
	/// </summary>
	/// <param name="texture_"></param>
	bool OnCreate();

	/// <summary>
	/// Render Zombies
	/// </summary>
	void Render(float scale = 1.0f);

	/// <summary>
	/// Handle Events for Zombies if needed
	/// </summary>
	void HandleEvents(const SDL_Event& event);

	/// <summary>
	/// Update zombies / body using deltaTime
	/// </summary>
	void Update(float deltaTime);

	/// <summary>
	/// Set zomobie texture
	/// </summary>
	void setTexture(SDL_Texture* texture_) { texture = texture_; }

	/// <summary>
	/// Set zombie amount to be rendered
	/// </summary>
	void setZombieAmount();

	/// <summary>
	/// get zombie remaining
	/// </summary>
	int getZombiesRemaining();

	//Never Used?
	void zombieArrPushBack(ZombieSpawner zombie_);
	void setZombieGame(GameManager* game_);

};

#endif