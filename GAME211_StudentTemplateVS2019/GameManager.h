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
#include "NumbersUI.h"
#include "ItemManagement.h"
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
	float speed;
	void Run();
	void handleEvents();
	void LoadScene( int i );
    bool ValidateCurrentScene();
	bool isMoving;

	//Zombie Spawn Locations
	std::vector<Vec3> zombieSpawnLocations;
	Vec3 getZombieSpawnLocations();

	void RenderZombie(float scale = 1.0f);
	ZombieSpawner getZombie();

	std::vector<ZombieSpawner> zombieSpawnerArr2;

	bool isSprinting;

	

	/////////////////////////////////////
	//ALL Variables go down here - MUST BE CATEGORIZED, LABELED AND NAMED PROPERLY
	////////////////////////////////////
	
	//Bullet Variables
	

	//Weapon Management
	WeaponManagement weaponManagement;
	Bullet bulletHolder;
	std::vector <Bullet> bullets;
	bool outOfAmmo;
	
	

	//Round UI
	NumbersUI RoundUI;

	//HealthUI
	NumbersUI HealthUI;

	//ZombieCounterUI
	NumbersUI ZombieCounterUI;

	/////////////////////////////////////
	//ALL FUNCTIONS GO DOWN HERE
	////////////////////////////////////

	/// <summary>
	/// Renders the bullet
	/// </summary>
	/// <param name="scale"></param>
	void RenderBullet(int i);

	/// <summary>
	/// Renders the out of ammo UI for when out of ammo
	/// </summary>
	void RenderOutOfAmmo();

	/// <summary>
	/// Renders the UI for displaying current round number
	/// </summary>
	void RenderRoundUI();

	/// <summary>
	/// Renders UI for Health
	/// </summary>
	void RenderHealthUI();

	/// <summary>
	/// Renders UI for Zombie Count
	/// </summary>
	void RenderZombieCountUI();
	
	/// <summary>
	/// gets the round
	/// </summary>
	/// <returns></returns>
	Round* getRound() { return round; }

	void zombieArrayInit();



	//Item Management
	ItemManagement itemManagement;

	/// <summary>
	/// Renders Items
	/// </summary>
	void RenderItem();

	//Temporary Zombie Location;
	Vec3 tempZombieLocation;

	/// <summary>
	/// Applies Drop Effect
	/// </summary>
	void DropEffects();



};
#endif


