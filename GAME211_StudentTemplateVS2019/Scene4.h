#ifndef SCENE4_H
#define SCENE4_H
#include "Body.h"

#include "MMath.h"
#include "Scene.h"

using namespace MATH;
class Scene4 : public Scene {
private:
	float xAxis;	// scene width, in game coords, set in constructor
	float yAxis;	// scene height, in game coords, set in constructor
	SDL_Window* window;		// an SDL window with a SDL renderer
	SDL_Renderer* renderer;	// the renderer associated with SDL window 
	Matrix4 projectionMatrix;	// set in OnCreate()
    Matrix4     inverseProjection;	// set in OnCreate()

	// PHUNG
	SDL_Texture* bgTexture;
	SDL_Texture* pathTexture;

	//tree row 1
	SDL_Texture* treeTexture0;
	SDL_Texture* treeTexture1;
	SDL_Texture* treeTexture2;
	SDL_Texture* treeTexture3;
	SDL_Texture* treeTexture4;
	SDL_Texture* treeTexture5;
	SDL_Texture* treeTexture6;
	SDL_Texture* treeTexture7;

	//tree row 1.1
	SDL_Texture* treeTexture0_1;
	SDL_Texture* treeTexture1_1;
	SDL_Texture* treeTexture2_1;
	SDL_Texture* treeTexture3_1;
	SDL_Texture* treeTexture4_1;
	SDL_Texture* treeTexture5_1;
	SDL_Texture* treeTexture6_1;
	SDL_Texture* treeTexture7_1;

	//tree row 2
	SDL_Texture* treeTexture0_2;
	SDL_Texture* treeTexture1_2;
	SDL_Texture* treeTexture2_2;
	SDL_Texture* treeTexture3_2;
	SDL_Texture* treeTexture4_2;
	SDL_Texture* treeTexture5_2;
	SDL_Texture* treeTexture6_2;
	SDL_Texture* treeTexture7_2;

	//tree row 3
	SDL_Texture* treeTexture0_3;
	SDL_Texture* treeTexture1_3;
	SDL_Texture* treeTexture2_3;
	SDL_Texture* treeTexture3_3;
	SDL_Texture* treeTexture4_3;
	SDL_Texture* treeTexture5_3;
	SDL_Texture* treeTexture6_3;
	SDL_Texture* treeTexture7_3;

	//tree row 4
	SDL_Texture* treeTexture0_4;
	SDL_Texture* treeTexture1_4;
	SDL_Texture* treeTexture2_4;
	SDL_Texture* treeTexture3_4;
	SDL_Texture* treeTexture4_4;
	SDL_Texture* treeTexture5_4;
	SDL_Texture* treeTexture6_4;
	SDL_Texture* treeTexture7_4;

	//other
	SDL_Texture* stumpTexture;

	//block
	SDL_Texture* blockTexture0;
	SDL_Texture* blockTexture1;

	Body* bg;

	SDL_Surface* bgImage;
	SDL_Surface* pathImage;

	//tree row 1
	SDL_Surface* treeImage0;
	SDL_Surface* treeImage1;
	SDL_Surface* treeImage2;
	SDL_Surface* treeImage3;
	SDL_Surface* treeImage4;
	SDL_Surface* treeImage5;
	SDL_Surface* treeImage6;
	SDL_Surface* treeImage7;

	//tree row 1.1
	SDL_Surface* treeImage0_1;
	SDL_Surface* treeImage1_1;
	SDL_Surface* treeImage2_1;
	SDL_Surface* treeImage3_1;
	SDL_Surface* treeImage4_1;
	SDL_Surface* treeImage5_1;
	SDL_Surface* treeImage6_1;
	SDL_Surface* treeImage7_1;

	//tree row 2
	SDL_Surface* treeImage0_2;
	SDL_Surface* treeImage1_2;
	SDL_Surface* treeImage2_2;
	SDL_Surface* treeImage3_2;
	SDL_Surface* treeImage4_2;
	SDL_Surface* treeImage5_2;
	SDL_Surface* treeImage6_2;
	SDL_Surface* treeImage7_2;

	//tree row 3
	SDL_Surface* treeImage0_3;
	SDL_Surface* treeImage1_3;
	SDL_Surface* treeImage2_3;
	SDL_Surface* treeImage3_3;
	SDL_Surface* treeImage4_3;
	SDL_Surface* treeImage5_3;
	SDL_Surface* treeImage6_3;
	SDL_Surface* treeImage7_3;

	//tree row 4
	SDL_Surface* treeImage0_4;
	SDL_Surface* treeImage1_4;
	SDL_Surface* treeImage2_4;
	SDL_Surface* treeImage3_4;
	SDL_Surface* treeImage4_4;
	SDL_Surface* treeImage5_4;
	SDL_Surface* treeImage6_4;
	SDL_Surface* treeImage7_4;

	//block
	SDL_Surface* blockImage0;
	SDL_Surface* blockImage1;

	SDL_Texture* loadImage(const char* textureFile);

	//PHUNG
	SDL_Rect scale(SDL_Texture* objectTexture,
		int start_x = 0, int start_y = 0, float scale = 1.0f);

public:
	// This constructor may be different from what you've seen before
	// Notice the second parameter, and look in GameManager.cpp
	// to see how this constructor is called.
	Scene4(SDL_Window* sdlWindow, GameManager* game_);
	~Scene4();
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
};

#endif
