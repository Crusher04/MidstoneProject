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
	//class ZombieSpawner zombies2;
	
	class Bullet* bullet;

public:
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

	//Get Round Class
	Round* getRound() { return round; }

	//Zombie Spawn Locations
	std::vector<Vec3> zombieSpawnLocations;
	void compileZombieSpawnLocations();

	void RenderZombie(float scale = 1.0f);
	ZombieSpawner getZombie();

	std::vector<ZombieSpawner> zombieSpawnerArr2;



	std::vector<Vec3> bulletSpawnLocations;
	void compileBulletSpawnLocations();
	Bullet getBullet();
	bool fired;
	void RenderBullet(float scale = 1.0f);
	float bulletSpeed;
	int bulletSelection;
	std::vector<Bullet> bullets;
};
#endif


