#ifndef ZOMBIESPAWNER_H
#define ZOMBIESPAWNER_H


#include <stdio.h>
#include "Body.h"
#include "GameManager.h"
#include <vector>



class ZombieSpawner : public Body
{
protected:

	class GameManager* game;
	
public:
	
	
	std::vector<ZombieSpawner> zombieSpawnerArr;

	ZombieSpawner() : Body{}
	{
		game = nullptr;
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

	float orientation;
};

#endif