#ifndef SCENE3_H
#define SCENE3_H

#include "MMath.h"
#include "Scene.h"
#include "Collider.h"

using namespace MATH;
class Scene3 : public Scene {
private:
	float xAxis;	// scene width, in game coords, set in constructor
	float yAxis;	// scene height, in game coords, set in constructor
	SDL_Window* window;		// an SDL window with a SDL renderer
	SDL_Renderer* renderer;	// the renderer associated with SDL window 
	Matrix4 projectionMatrix;	// set in OnCreate()
    Matrix4     inverseProjection;	// set in OnCreate()
	
	//Background Image
	SDL_Surface* backgroundImage;
	SDL_Texture* backgroundTexture;

	//StartMenuImage
	SDL_Surface* startMenuImage;
	SDL_Texture* startMenuTexture;
	
	//Play Button
	SDL_Surface* playButtonImage;
	SDL_Texture* playButtonTexture;

	//Quit Button
	SDL_Surface* quitButtonImage;
	SDL_Texture* quitButtonTexture;

	//About Us Button
	SDL_Surface* aboutButtonImage;
	SDL_Texture* aboutButtonTexture;

	//Back Button
	SDL_Surface* backButtonImage;
	SDL_Texture* backButtonTexture;

	//Back Button
	SDL_Surface* aboutUsPageImage;
	SDL_Texture* aboutUsPageTexture;

	int mouseX, mouseY;
	float screenX, screenY;
	bool aboutUSOn;

public:
	// This constructor may be different from what you've seen before
	// Notice the second parameter, and look in GameManager.cpp
	// to see how this constructor is called.
	Scene3(SDL_Window* sdlWindow, GameManager* game_);
	~Scene3();
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

	void RenderStartMenuBackground();
	void RenderStartMenu();
	void RenderPlayButton();
	void RenderQuitButton();
	void RenderAboutButton();
	void RenderBackButton();
	void RenderAboutUsPage();

	Collider playButtonColl;
	Collider quitButtonColl;
	Collider aboutButtonColl;
	Collider backButtonColl;
};

#endif
