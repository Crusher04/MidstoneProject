#ifndef SCENE2_H
#define SCENE2_H

#include "MMath.h"
#include "Scene.h"

using namespace MATH;
class Scene2 : public Scene {
private:
	float xAxis;	// scene width, in game coords, set in constructor
	float yAxis;	// scene height, in game coords, set in constructor
	SDL_Window* window;		// an SDL window with a SDL renderer
	SDL_Renderer* renderer;	// the renderer associated with SDL window 
	Matrix4 projectionMatrix;	// set in OnCreate()
    Matrix4     inverseProjection;	// set in OnCreate()

/// <summary>
/// MAP STUFF
/// </summary>

	// TEXTURE
	SDL_Texture* pathTexture;

	//UI
	SDL_Texture* hbEmptyTexture;
	SDL_Texture* hbFullTexture;
	SDL_Texture* zombieIconTexture;

	//IMAGE
	SDL_Surface* pathImage;

	//UI
	SDL_Surface* hbEmptyImage;
	SDL_Surface* hbFullImage;
	SDL_Surface* zombieIconImage;

	//Pause Menu
	SDL_Surface* pauseMenuImage;
	SDL_Texture* pauseMenuTexture;

	//Menu Button
	SDL_Surface* menuButtonImage;
	SDL_Texture* menuButtonTexture;
	Collider menuButtonColl;

	//Quit Button
	SDL_Surface* quitButtonImage;
	SDL_Texture* quitButtonTexture;
	Collider quitButtonColl;

	//Restart Button
	SDL_Surface* restartButtonImage;
	SDL_Texture* restartButtonTexture;
	Collider restartButtonColl;

	//Death Background
	SDL_Surface* deathBannerBackgroundImage;
	SDL_Texture* deathBannerBackgroundTexture;
	
	//Defeat Text
	SDL_Surface* deathBannerImage;
	SDL_Texture* deathBannerTexture;

	//Death Restart Icon
	SDL_Surface* deathRestartImage;
	SDL_Texture* deathRestartTexture;

	//Death Menu Icon
	SDL_Surface* deathMenuImage;
	SDL_Texture* deathMenuTexture;

	//Health & Ammo backround
	SDL_Surface* healthHUDImage;
	SDL_Texture* healthHUDTexture;

	SDL_Surface* healthAmmoBGImage;
	SDL_Texture* healthAmmoBGTexture;

	SDL_Surface* healthAmmoBGDividerImage;
	SDL_Texture* healthAmmoBGDividerTexture;

	SDL_Surface* ammoHUDImage;
	SDL_Texture* ammoHUDTexture;

	//UI Damage Effect
	SDL_Surface* playerDamageEffectImage;
	SDL_Texture* playerDamageEffectTexture;
	
	//Tree Images and Vars
	SDL_Surface* treeOneImage;
	SDL_Texture* treeOneTexture;
	
	SDL_Surface* treeTwoImage;
	SDL_Texture* treeTwoTexture;

	SDL_Surface* treeThreeImage;
	SDL_Texture* treeThreeTexture;

	SDL_Surface* treeFourImage;
	SDL_Texture* treeFourTexture;
	
	SDL_Surface* treeFiveImage;
	SDL_Texture* treeFiveTexture;

	Collider treeColl;
	std::vector<Collider> treeCollArr;
	std::vector<SDL_Texture*> treeTextureArr;

	int treeLocCounter;

	int mouseX, mouseY;
	int playerDamageEffectOpacity;

	//PHUNG
	SDL_Rect scale(SDL_Texture* objectTexture,
		int start_x = 0, int start_y = 0, float scaleX = 1.0f, float scaleY = 1.0f);

public:
	// This constructor may be different from what you've seen before
	// Notice the second parameter, and look in GameManager.cpp
	// to see how this constructor is called.
	Scene2(SDL_Window* sdlWindow, GameManager* game_);
	~Scene2();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
    void HandleEvents(const SDL_Event &event);
	float getxAxis() { return xAxis; }
	float getyAxis() { return yAxis; }
	SDL_Window* getWindow() { return window; }
    Matrix4 getProjectionMatrix() { return projectionMatrix; }
	Matrix4 getInverseMatrix() { return inverseProjection; }
	
	//Our Functions
	void buildMap();		//This runs in OnCreate for the Scene2 to build the map.
	void initMapVar();		//This initializes the variables for our map.
	void renderMap();		//This renders our map
	void RenderPauseMenu();
	void RenderDeathScreen();
	void RenderHealthBackground();
	void RenderUIDamageEffect();
	void RenderTrees();

	//Variables - ADD HERE WITH DESCRIPTION!! 
	
	Vec3 updatedGunPos;
	int zombieSpawnTime;
	int zombieSelection;

	int zombieTimeBetweenSpawn;
	
	int roundEndTimer;
	bool roundEnded;
	


};

#endif
