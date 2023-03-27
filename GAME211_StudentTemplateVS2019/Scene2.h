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
	SDL_Texture* bgTexture;
	SDL_Texture* pathTexture;

	//tree
	SDL_Texture* treeTexture0;
	SDL_Texture* treeTexture1;
	SDL_Texture* treeTexture2;

	//other Texture
	SDL_Texture* wellTexture;
	SDL_Texture* otherTexture0;
	SDL_Texture* otherTexture1;
	SDL_Texture* logTexture0;


	//block
	/*SDL_Texture* blockTexture0;
	SDL_Texture* blockTexture1;
	SDL_Texture* blockTexture2;
	SDL_Texture* blockTexture3;*/

	//rock
	SDL_Texture* rockTexture0;
	SDL_Texture* rockTexture1;
	SDL_Texture* rockTexture2;
	SDL_Texture* rockTexture3;

	//UI
	SDL_Texture* hbEmptyTexture;
	SDL_Texture* hbFullTexture;
	SDL_Texture* zombieIconTexture;

	//_____________________________________IMAGE
	Body* bg;

	SDL_Surface* bgImage;
	SDL_Surface* pathImage;

	//tree
	SDL_Surface* treeImage0;
	SDL_Surface* treeImage1;
	SDL_Surface* treeImage2;

	//block
	SDL_Surface* blockImage0;
	SDL_Surface* blockImage1;
	SDL_Surface* blockImage2;

	//other
	SDL_Surface* wellImage;
	SDL_Surface* otherImage0;
	SDL_Surface* otherImage1;
	SDL_Surface* logImage0;

	//rock
	SDL_Surface* rockImage0;
	SDL_Surface* rockImage1;
	SDL_Surface* rockImage2;

	//UI
	SDL_Surface* hbEmptyImage;
	SDL_Surface* hbFullImage;
	SDL_Surface* zombieIconImage;

	SDL_Surface* pauseMenuImage;
	SDL_Texture* pauseMenuTexture;

	SDL_Surface* menuButtonImage;
	SDL_Texture* menuButtonTexture;
	Collider menuButtonColl;

	SDL_Surface* quitButtonImage;
	SDL_Texture* quitButtonTexture;
	Collider quitButtonColl;

	int mouseX, mouseY;

	SDL_Texture* loadImage(const char* textureFile);

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

	//Variables - ADD HERE WITH DESCRIPTION!! 
	
	Vec3 updatedGunPos;
	int zombieSpawnTime;
	int zombieSelection;

	int zombieTimeBetweenSpawn;
	
	int roundEndTimer;
	bool roundEnded;
	


};

#endif
