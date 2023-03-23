#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <SDL.h>
#include <iostream>
#include "Window.h"
#include "Timer.h"
#include "Scene.h"
#include "PlayerBody.h"
#include "Round.h"
#include <vector>
#include "ZombieSpawner.h"
#include "Bullet.h"
#include "WeaponManagement.h"

class GameManager {
private:
	/// These are called "forward declarations" The idea is that a pointer is 
	/// really just an unsigned int, so to create a pointer to it you really only
	/// need to tell the compiler that there is a class called Window and I need
	/// a pointer to it, thus the "class Window*" means trust me, there is a class 
	/// called Window, I just need a pointer to it.

	/// If that was too much for your brain, just #include "Window.h" and declare
	/// Window *ptr and don't use the word "class"  This is a second semester C++
	/// topic anyway
	class Window *windowPtr;
	class Timer *timer;
	bool isRunning;
	class Scene *currentScene;

	// This might be unfamiliar
    class PlayerBody *player;
	class Round	*round;	
	class ZombieSpawner *zombies;	
	class Bullet* bullet;

public:

	//Contstructors with onCreate/Destroy

	GameManager();
	~GameManager();
	bool OnCreate();
	void OnDestroy();

	

	// These might be unfamiliar
	float getSceneHeight();
	float getSceneWidth();
	Matrix4 getProjectionMatrix();
    PlayerBody* getPlayer(){ return player; }
	void RenderPlayer(float scale = 1.0f);
	SDL_Renderer* getRenderer();
	bool w;
	float speed;
	bool e;
	void Run();
	void handleEvents();
	void LoadScene( int i );
    bool ValidateCurrentScene();
	bool isMoving;
	bool reload;

	

	//Zombie Spawn Locations
	std::vector<Vec3> zombieSpawnLocations;
	Vec3 compileZombieSpawnLocations();

	void RenderZombie(float scale = 1.0f);
	ZombieSpawner getZombie();

	std::vector<ZombieSpawner> zombieSpawnerArr2;

	float ammoCount;

	bool isSprinting;


	bool bulletRendered;


	int i[7];

	bool bulletFired;

	bool zombieSpawned;
	bool zombieRender[5];

	/////////////////////////////////////
	//ALL Variables go down here - MUST BE CATEGORIZED, LABELED AND NAMED PROPERLY
	////////////////////////////////////
	
	//Bullet Variables
	bool fired;
	bool fired1;
	bool fired2;
	bool fired3;
	bool fired4;
	bool fired5;
	bool fired6;
	bool fired7;
	bool fired8;
	float bulletSpeed;
	int bulletSelection = 0;
	std::vector<Bullet> bullets;

	//Weapon Management
	WeaponManagement weaponManagement;
	bool outOfAmmo;

	/////////////////////////////////////
	//ALL FUNCTIONS GO DOWN HERE
	////////////////////////////////////

	/// <summary>
	/// Renders the bullet
	/// </summary>
	/// <param name="scale"></param>
	void RenderBullet(float scale = 1.0f);

	/// <summary>
	/// Renders the out of ammo UI for when out of ammo
	/// </summary>
	void RenderOutOfAmmo();

	/// <summary>
	/// returns bullet class
	/// </summary>
	/// <returns></returns>
	Bullet* getBullet() { return bullet; }
	
	/// <summary>
	/// gets the round
	/// </summary>
	/// <returns></returns>
	Round* getRound() { return round; }

	void zombieArrayInit();

};
#endif


