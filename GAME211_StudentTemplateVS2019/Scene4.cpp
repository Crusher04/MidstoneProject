#include "Scene4.h"
#include "VMath.h"
//#include "Collider.h"

// See notes about this constructor in Scene1.h.
Scene4::Scene4(SDL_Window* sdlWindow_, GameManager* game_){
	window = sdlWindow_;
    game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;

	/// PHUNG
	//bg = new Body(Vec3(0.0f, 15.0f, 0.0f)); // background position
	bgTexture = nullptr;
	pathTexture = nullptr;

	//tree row 1
	treeTexture0 = nullptr; 
	treeTexture1 = nullptr;
	treeTexture2 = nullptr;
	treeTexture3 = nullptr;
	treeTexture4 = nullptr;
	treeTexture5 = nullptr;
	treeTexture6 = nullptr;
	treeTexture7 = nullptr;

	//tree row 1.1
	treeTexture0_1 = nullptr;
	treeTexture1_1 = nullptr;
	treeTexture2_1 = nullptr;
	treeTexture3_1 = nullptr;
	treeTexture4_1 = nullptr;
	treeTexture5_1 = nullptr;
	treeTexture6_1 = nullptr;
	treeTexture7_1 = nullptr;

	//tree row 2
	treeTexture0_2 = nullptr;
	treeTexture1_2 = nullptr;
	treeTexture2_2 = nullptr;
	treeTexture3_2 = nullptr;
	treeTexture4_2 = nullptr;
	treeTexture5_2 = nullptr;
	treeTexture6_2 = nullptr;
	treeTexture7_2 = nullptr;

	//tree row 3
	treeTexture0_3 = nullptr;
	treeTexture1_3 = nullptr;
	treeTexture2_3 = nullptr;
	treeTexture3_3 = nullptr;
	treeTexture4_3 = nullptr;
	treeTexture5_3 = nullptr;
	treeTexture6_3 = nullptr;
	treeTexture7_3 = nullptr;

	//tree row 4
	treeTexture0_4 = nullptr;
	treeTexture1_4 = nullptr;
	treeTexture2_4 = nullptr;
	treeTexture3_4 = nullptr;
	treeTexture4_4 = nullptr;
	treeTexture5_4 = nullptr;
	treeTexture6_4 = nullptr;
	treeTexture7_4 = nullptr;

	//block
	blockTexture0 = nullptr;
	blockTexture1 = nullptr;

}

Scene4::~Scene4(){
}

bool Scene4::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	
	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	// Set images
	/*SDL_Surface* bg;
	SDL_Texture* bg_texture;*/


	bgImage = IMG_Load("Assets/background/bg_green1.png");
	bgTexture = SDL_CreateTextureFromSurface(renderer, bgImage);

	pathImage = IMG_Load("Assets/background/bg_path.png");
	pathTexture = SDL_CreateTextureFromSurface(renderer, pathImage);

	//tree row 1
	treeImage0 = IMG_Load("Assets/organic/bush1.png");
	treeTexture0 = SDL_CreateTextureFromSurface(renderer, treeImage0);

	treeImage1 = IMG_Load("Assets/organic/bush.png");
	treeTexture1 = SDL_CreateTextureFromSurface(renderer, treeImage1);

	treeImage2 = IMG_Load("Assets/organic/bush.png");
	treeTexture2 = SDL_CreateTextureFromSurface(renderer, treeImage2);

	treeImage3 = IMG_Load("Assets/organic/bush1.png");
	treeTexture3 = SDL_CreateTextureFromSurface(renderer, treeImage3);

	treeImage4 = IMG_Load("Assets/organic/bush.png");
	treeTexture4 = SDL_CreateTextureFromSurface(renderer, treeImage4);

	treeImage5 = IMG_Load("Assets/organic/bush1.png");
	treeTexture5 = SDL_CreateTextureFromSurface(renderer, treeImage5);

	treeImage6 = IMG_Load("Assets/organic/bush1.png");
	treeTexture6 = SDL_CreateTextureFromSurface(renderer, treeImage6);

	treeImage7 = IMG_Load("Assets/organic/bush.png");
	treeTexture7 = SDL_CreateTextureFromSurface(renderer, treeImage7);

	//tree row 1.1
	treeImage0_1 = IMG_Load("Assets/organic/bush1.png");
	treeTexture0_1 = SDL_CreateTextureFromSurface(renderer, treeImage0_1);

	treeImage1_1 = IMG_Load("Assets/organic/bush1.png");
	treeTexture1_1 = SDL_CreateTextureFromSurface(renderer, treeImage1_1);

	treeImage2_1 = IMG_Load("Assets/organic/bush.png");
	treeTexture2_1 = SDL_CreateTextureFromSurface(renderer, treeImage2_1);

	treeImage3_1 = IMG_Load("Assets/organic/bush.png");
	treeTexture3_1 = SDL_CreateTextureFromSurface(renderer, treeImage3_1);

	treeImage4_1 = IMG_Load("Assets/organic/bush1.png");
	treeTexture4_1 = SDL_CreateTextureFromSurface(renderer, treeImage4_1);

	treeImage5_1 = IMG_Load("Assets/organic/bush.png");
	treeTexture5_1 = SDL_CreateTextureFromSurface(renderer, treeImage5_1);

	treeImage6_1 = IMG_Load("Assets/organic/bush1.png");
	treeTexture6_1 = SDL_CreateTextureFromSurface(renderer, treeImage6_1);

	treeImage7_1 = IMG_Load("Assets/organic/bush.png");
	treeTexture7_1 = SDL_CreateTextureFromSurface(renderer, treeImage7_1);

	//tree row 2
	treeImage0_2 = IMG_Load("Assets/organic/bush1.png");
	treeTexture0_2 = SDL_CreateTextureFromSurface(renderer, treeImage0_2);

	treeImage1_2 = IMG_Load("Assets/organic/bush1.png");
	treeTexture1_2 = SDL_CreateTextureFromSurface(renderer, treeImage1_2);

	treeImage2_2 = IMG_Load("Assets/organic/bush.png");
	treeTexture2_2 = SDL_CreateTextureFromSurface(renderer, treeImage2_2);

	treeImage3_2 = IMG_Load("Assets/organic/bush.png");
	treeTexture3_2 = SDL_CreateTextureFromSurface(renderer, treeImage3_2);

	treeImage4_2 = IMG_Load("Assets/organic/bush1.png");
	treeTexture4_2 = SDL_CreateTextureFromSurface(renderer, treeImage4_2);

	treeImage5_2 = IMG_Load("Assets/organic/bush.png");
	treeTexture5_2 = SDL_CreateTextureFromSurface(renderer, treeImage5_2);

	treeImage6_2 = IMG_Load("Assets/organic/bush1.png");
	treeTexture6_2 = SDL_CreateTextureFromSurface(renderer, treeImage6_2);

	treeImage7_2 = IMG_Load("Assets/organic/bush1.png");
	treeTexture7_2 = SDL_CreateTextureFromSurface(renderer, treeImage7_2);

	//tree row 3
	treeImage0_3 = IMG_Load("Assets/organic/bush.png");
	treeTexture0_3 = SDL_CreateTextureFromSurface(renderer, treeImage0_3);

	treeImage1_3 = IMG_Load("Assets/organic/bush.png");
	treeTexture1_3 = SDL_CreateTextureFromSurface(renderer, treeImage1_3);

	treeImage2_3 = IMG_Load("Assets/organic/bush1.png");
	treeTexture2_3 = SDL_CreateTextureFromSurface(renderer, treeImage2_3);

	treeImage3_3 = IMG_Load("Assets/organic/bush.png");
	treeTexture3_3 = SDL_CreateTextureFromSurface(renderer, treeImage3_3);

	treeImage4_3 = IMG_Load("Assets/organic/bush1.png");
	treeTexture4_3 = SDL_CreateTextureFromSurface(renderer, treeImage4_3);

	treeImage5_3 = IMG_Load("Assets/organic/bush.png");
	treeTexture5_3 = SDL_CreateTextureFromSurface(renderer, treeImage5_3);

	treeImage6_3 = IMG_Load("Assets/organic/bush1.png");
	treeTexture6_3 = SDL_CreateTextureFromSurface(renderer, treeImage6_3);

	treeImage7_3 = IMG_Load("Assets/organic/bush.png");
	treeTexture7_3 = SDL_CreateTextureFromSurface(renderer, treeImage7_3);

	//tree row 4
	treeImage0_4 = IMG_Load("Assets/organic/bush1.png");
	treeTexture0_4 = SDL_CreateTextureFromSurface(renderer, treeImage0_4);

	treeImage1_4 = IMG_Load("Assets/organic/bush1.png");
	treeTexture1_4 = SDL_CreateTextureFromSurface(renderer, treeImage1_4);

	treeImage2_4 = IMG_Load("Assets/organic/bush.png");
	treeTexture2_4 = SDL_CreateTextureFromSurface(renderer, treeImage2_4);

	treeImage3_4 = IMG_Load("Assets/organic/bush.png");
	treeTexture3_4 = SDL_CreateTextureFromSurface(renderer, treeImage3_4);

	treeImage4_4 = IMG_Load("Assets/organic/bush.png");
	treeTexture4_4 = SDL_CreateTextureFromSurface(renderer, treeImage4_4);

	treeImage5_4 = IMG_Load("Assets/organic/bush1.png");
	treeTexture5_4 = SDL_CreateTextureFromSurface(renderer, treeImage5_4);

	treeImage6_4 = IMG_Load("Assets/organic/bush.png");
	treeTexture6_4 = SDL_CreateTextureFromSurface(renderer, treeImage6_4);

	treeImage7_4 = IMG_Load("Assets/organic/bush.png");
	treeTexture7_4 = SDL_CreateTextureFromSurface(renderer, treeImage7_4);

	//block
	blockImage0 = IMG_Load("Assets/organic/block1.png");
	blockTexture0 = SDL_CreateTextureFromSurface(renderer, blockImage0);

	blockImage1 = IMG_Load("Assets/organic/block3.1.png"); 
	blockTexture1 = SDL_CreateTextureFromSurface(renderer, blockImage1);

	//SDL_QueryTexture(bgTexture, nullptr, nullptr, &star1Width, nullptr);
	/*bg = IMG_Load("Assets/background/bg_grass.png");
	bg_texture = SDL_CreateTextureFromSurface(renderer, bg);
	game->getPlayer()->setImage(bg);
	game->getPlayer()->setTexture(bg_texture);*/

	return true;
}

SDL_Texture* Scene4::loadImage(const char* textureFile)
{
	return nullptr;
}

SDL_Rect Scene4::scale(SDL_Texture* objectTexture, int start_x, int start_y, float scale) {

	// Get the size of the input texture
	SDL_Point size;
	SDL_QueryTexture(objectTexture, nullptr, nullptr, &size.x, &size.y);
	SDL_Rect dest = { start_x, start_y, size.x * scale, size.y * scale };
	return dest;
}

void Scene4::OnDestroy() {}

void Scene4::Update(const float deltaTime) {

	// Update player
	game->getPlayer()->Update(deltaTime);
}

void Scene4::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	//bg and path
	Vec3 bg_screenCoords = projectionMatrix * Vec3(0.0f, 15.0f, 0.0f);
	Vec3 path_screenCoords = projectionMatrix * Vec3(0.0f, 8.0f, 0.0f);

	// tree row 1
	Vec3 tree_screenCoords0 = projectionMatrix * Vec3(-1.0f,14.2f, 0.0f);
	Vec3 tree_screenCoords1 = projectionMatrix * Vec3(2.0f, 15.3f, 0.0f);
	Vec3 tree_screenCoords2 = projectionMatrix * Vec3(5.0f, 14.3f, 0.0f);
	Vec3 tree_screenCoords3 = projectionMatrix * Vec3(9.0f, 15.3f, 0.0f);
	Vec3 tree_screenCoords4 = projectionMatrix * Vec3(11.5f, 15.0f, 0.0f);
	Vec3 tree_screenCoords5 = projectionMatrix * Vec3(14.0f, 15.3f, 0.0f);
	Vec3 tree_screenCoords6 = projectionMatrix * Vec3(19.0f, 15.5f, 0.0f);
	Vec3 tree_screenCoords7 = projectionMatrix * Vec3(22.0f, 15.2f, 0.0f);
	
	// tree row 1.1
	Vec3 tree_screenCoords0_1 = projectionMatrix * Vec3(0.6f, 12.2f, 0.0f);
	Vec3 tree_screenCoords1_1 = projectionMatrix * Vec3(4.1f, 13.7f, 0.0f);
	Vec3 tree_screenCoords2_1 = projectionMatrix * Vec3(6.4f, 14.1f, 0.0f);
	Vec3 tree_screenCoords3_1 = projectionMatrix * Vec3(9.2f, 12.0f, 0.0f);
	Vec3 tree_screenCoords4_1 = projectionMatrix * Vec3(13.7f, 14.1f, 0.0f);
	Vec3 tree_screenCoords5_1 = projectionMatrix * Vec3(15.3f, 11.35f, 0.0f);
	Vec3 tree_screenCoords6_1 = projectionMatrix * Vec3(17.0f, 13.55f, 0.0f);
	Vec3 tree_screenCoords7_1 = projectionMatrix * Vec3(19.5f, 11.01f, 0.0f);

	// tree row 2
	Vec3 tree_screenCoords0_2 = projectionMatrix * Vec3(-2.0f, 12.0f, 0.0f);
	Vec3 tree_screenCoords1_2 = projectionMatrix * Vec3(1.0f, 11.3f, 0.0f);
	Vec3 tree_screenCoords2_2 = projectionMatrix * Vec3(4.0f, 11.3f, 0.0f);
	Vec3 tree_screenCoords3_2 = projectionMatrix * Vec3(7.0f, 9.3f, 0.0f);
	Vec3 tree_screenCoords4_2 = projectionMatrix * Vec3(10.5f, 10.0f, 0.0f);
	Vec3 tree_screenCoords5_2 = projectionMatrix * Vec3(13.0f, 9.7f, 0.0f);
	Vec3 tree_screenCoords6_2 = projectionMatrix * Vec3(17.5f, 12.5f, 0.0f);
	Vec3 tree_screenCoords7_2 = projectionMatrix * Vec3(23.0f, 10.2f, 0.0f);

	// tree row 3
	Vec3 tree_screenCoords0_3 = projectionMatrix * Vec3(-1.5f, 6.0f, 0.0f);
	Vec3 tree_screenCoords1_3 = projectionMatrix * Vec3(3.0f, 4.3f, 0.0f);
	Vec3 tree_screenCoords2_3 = projectionMatrix * Vec3(4.5f, 3.3f, 0.0f);
	Vec3 tree_screenCoords3_3 = projectionMatrix * Vec3(6.2f, 5.0f, 0.0f);
	Vec3 tree_screenCoords4_3 = projectionMatrix * Vec3(12.5f, 3.8f, 0.0f);
	Vec3 tree_screenCoords5_3 = projectionMatrix * Vec3(15.0f, 4.7f, 0.0f);
	Vec3 tree_screenCoords6_3 = projectionMatrix * Vec3(18.25f, 5.5f, 0.0f);
	Vec3 tree_screenCoords7_3 = projectionMatrix * Vec3(22.8f, 3.2f, 0.0f);

	// tree row 4
	Vec3 tree_screenCoords0_4 = projectionMatrix * Vec3(-1.5f, 6.0f, 0.0f);
	Vec3 tree_screenCoords1_4 = projectionMatrix * Vec3(3.0f, 4.3f, 0.0f);
	Vec3 tree_screenCoords2_4 = projectionMatrix * Vec3(4.5f, 3.3f, 0.0f);
	Vec3 tree_screenCoords3_4 = projectionMatrix * Vec3(6.2f, 5.0f, 0.0f);
	Vec3 tree_screenCoords4_4 = projectionMatrix * Vec3(12.5f, 3.8f, 0.0f);
	Vec3 tree_screenCoords5_4 = projectionMatrix * Vec3(15.0f, 4.7f, 0.0f);
	Vec3 tree_screenCoords6_4 = projectionMatrix * Vec3(18.25f, 5.5f, 0.0f);
	Vec3 tree_screenCoords7_4 = projectionMatrix * Vec3(22.8f, 3.2f, 0.0f);

	//block
	Vec3 block_screenCoords0 = projectionMatrix * Vec3(0.0f, 1.0f, 0.0f);
	Vec3 block_screenCoords1 = projectionMatrix * Vec3(0.0f, 5.0f, 0.0f);
	
	// tree row 1
	SDL_Rect dest = scale(bgTexture, bg_screenCoords.x, bg_screenCoords.y, 0.4f);
	SDL_RenderCopy(renderer, bgTexture, nullptr, &dest);

	dest = scale(pathTexture, path_screenCoords.x, path_screenCoords.y, 0.6f);
	SDL_RenderCopy(renderer, pathTexture, nullptr, &dest);

	dest = scale(treeTexture0, tree_screenCoords0.x, tree_screenCoords0.y, 0.8f); //bush1
	SDL_RenderCopy(renderer, treeTexture0, nullptr, &dest);

	dest = scale(treeTexture1, tree_screenCoords1.x, tree_screenCoords1.y, 0.85f); //bush2
	SDL_RenderCopy(renderer, treeTexture1, nullptr, &dest);

	dest = scale(treeTexture2, tree_screenCoords2.x, tree_screenCoords2.y, 0.9f); //bush0 
	SDL_RenderCopy(renderer, treeTexture2, nullptr, &dest);

	dest = scale(treeTexture3, tree_screenCoords3.x, tree_screenCoords3.y, 0.85f); //bush
	SDL_RenderCopy(renderer, treeTexture3, nullptr, &dest);

	dest = scale(treeTexture4, tree_screenCoords4.x, tree_screenCoords4.y, 0.9f); //bush2
	SDL_RenderCopy(renderer, treeTexture4, nullptr, &dest);

	dest = scale(treeTexture5, tree_screenCoords5.x, tree_screenCoords5.y, 0.7f); //bush1
	SDL_RenderCopy(renderer, treeTexture5, nullptr, &dest);

	dest = scale(treeTexture6, tree_screenCoords6.x, tree_screenCoords6.y, 0.6f); //bush1
	SDL_RenderCopy(renderer, treeTexture6, nullptr, &dest);

	dest = scale(treeTexture7, tree_screenCoords7.x, tree_screenCoords7.y, 1.0f); //bush
	SDL_RenderCopy(renderer, treeTexture7, nullptr, &dest);

	// tree row 1.1
	dest = scale(treeTexture0_1, tree_screenCoords0_1.x, tree_screenCoords0_1.y, 0.7f); //bush1
	SDL_RenderCopy(renderer, treeTexture0_1, nullptr, &dest);

	dest = scale(treeTexture1_1, tree_screenCoords1_1.x, tree_screenCoords1_1.y, 0.85f); //bush2
	SDL_RenderCopy(renderer, treeTexture1_1, nullptr, &dest);

	dest = scale(treeTexture2_1, tree_screenCoords2_1.x, tree_screenCoords2_1.y, 0.9f); //bush0 
	SDL_RenderCopy(renderer, treeTexture2_1, nullptr, &dest);

	dest = scale(treeTexture3_1, tree_screenCoords3_1.x, tree_screenCoords3_1.y, 0.85f); //bush
	SDL_RenderCopy(renderer, treeTexture3_1, nullptr, &dest);

	dest = scale(treeTexture4_1, tree_screenCoords4_1.x, tree_screenCoords4_1.y, 0.9f); //bush2
	SDL_RenderCopy(renderer, treeTexture4_1, nullptr, &dest);

	dest = scale(treeTexture5_1, tree_screenCoords5_1.x, tree_screenCoords5_1.y, 0.6f); //bush1
	SDL_RenderCopy(renderer, treeTexture5_1, nullptr, &dest);

	dest = scale(treeTexture6_1, tree_screenCoords6_1.x, tree_screenCoords6_1.y, 0.8f); //bush1
	SDL_RenderCopy(renderer, treeTexture6_1, nullptr, &dest);

	dest = scale(treeTexture7_1, tree_screenCoords7_1.x, tree_screenCoords7_1.y, 1.0f); //bush
	SDL_RenderCopy(renderer, treeTexture7_1, nullptr, &dest);

	//tree row 2
	dest = scale(treeTexture0_2, tree_screenCoords0_2.x, tree_screenCoords0_2.y, 0.65f); //bush1
	SDL_RenderCopy(renderer, treeTexture0_2, nullptr, &dest);

	dest = scale(treeTexture1_2, tree_screenCoords1_2.x, tree_screenCoords1_2.y, 0.85f); //bush2
	SDL_RenderCopy(renderer, treeTexture1_2, nullptr, &dest);

	dest = scale(treeTexture2_2, tree_screenCoords2_2.x, tree_screenCoords2_2.y, 0.9f); //bush0 
	SDL_RenderCopy(renderer, treeTexture2_2, nullptr, &dest);

	dest = scale(treeTexture3_2, tree_screenCoords3_2.x, tree_screenCoords3_2.y, 0.85f); //bush
	SDL_RenderCopy(renderer, treeTexture3_2, nullptr, &dest);

	dest = scale(treeTexture4_2, tree_screenCoords4_2.x, tree_screenCoords4_2.y, 0.9f); //bush2
	SDL_RenderCopy(renderer, treeTexture4_2, nullptr, &dest);

	dest = scale(treeTexture5_2, tree_screenCoords5_2.x, tree_screenCoords5_2.y, 0.72f); //bush1
	SDL_RenderCopy(renderer, treeTexture5_2, nullptr, &dest);

	dest = scale(treeTexture6_2, tree_screenCoords6_2.x, tree_screenCoords6_2.y, 0.81f); //bush1
	SDL_RenderCopy(renderer, treeTexture6_2, nullptr, &dest);

	dest = scale(treeTexture7_2, tree_screenCoords7_2.x, tree_screenCoords7_2.y, 0.74f); //bush
	SDL_RenderCopy(renderer, treeTexture7_2, nullptr, &dest);

	//tree row 3
	dest = scale(treeTexture0_3, tree_screenCoords0_3.x, tree_screenCoords0_3.y, 0.65f); //bush1
	SDL_RenderCopy(renderer, treeTexture0_3, nullptr, &dest);

	dest = scale(treeTexture1_3, tree_screenCoords1_3.x, tree_screenCoords1_3.y, 0.85f); //bush2
	SDL_RenderCopy(renderer, treeTexture1_3, nullptr, &dest);

	dest = scale(treeTexture2_3, tree_screenCoords2_3.x, tree_screenCoords2_3.y, 0.9f); //bush0 
	SDL_RenderCopy(renderer, treeTexture2_3, nullptr, &dest);

	dest = scale(treeTexture3_3, tree_screenCoords3_3.x, tree_screenCoords3_3.y, 0.85f); //bush
	SDL_RenderCopy(renderer, treeTexture3_3, nullptr, &dest);

	dest = scale(treeTexture4_3, tree_screenCoords4_3.x, tree_screenCoords4_3.y, 0.9f); //bush2
	SDL_RenderCopy(renderer, treeTexture4_3, nullptr, &dest);

	dest = scale(treeTexture5_3, tree_screenCoords5_3.x, tree_screenCoords5_3.y, 0.73f); //bush1
	SDL_RenderCopy(renderer, treeTexture5_3, nullptr, &dest);

	dest = scale(treeTexture6_3, tree_screenCoords6_3.x, tree_screenCoords6_3.y, 0.62f); //bush1
	SDL_RenderCopy(renderer, treeTexture6_3, nullptr, &dest);

	dest = scale(treeTexture7_3, tree_screenCoords7_3.x, tree_screenCoords7_3.y, 1.0f); //bush
	SDL_RenderCopy(renderer, treeTexture7_3, nullptr, &dest);

	//tree row 4
	dest = scale(treeTexture0_4, tree_screenCoords0_4.x, tree_screenCoords0_4.y, 0.73f); //bush1
	SDL_RenderCopy(renderer, treeTexture0_4, nullptr, &dest);

	dest = scale(treeTexture1_4, tree_screenCoords1_4.x, tree_screenCoords1_4.y, 0.85f); //bush2
	SDL_RenderCopy(renderer, treeTexture1_4, nullptr, &dest);

	dest = scale(treeTexture2_4, tree_screenCoords2_4.x, tree_screenCoords2_4.y, 0.9f); //bush0 
	SDL_RenderCopy(renderer, treeTexture2_4, nullptr, &dest);

	dest = scale(treeTexture3_4, tree_screenCoords3_4.x, tree_screenCoords3_4.y, 0.85f); //bush
	SDL_RenderCopy(renderer, treeTexture3_4, nullptr, &dest);

	dest = scale(treeTexture4_4, tree_screenCoords4_4.x, tree_screenCoords4_4.y, 0.9f); //bush2
	SDL_RenderCopy(renderer, treeTexture4_4, nullptr, &dest);

	dest = scale(treeTexture5_4, tree_screenCoords5_4.x, tree_screenCoords5_4.y, 0.66f); //bush1
	SDL_RenderCopy(renderer, treeTexture5_4, nullptr, &dest);

	dest = scale(treeTexture6_4, tree_screenCoords6_4.x, tree_screenCoords6_4.y, 0.72f); //bush1
	SDL_RenderCopy(renderer, treeTexture6_4, nullptr, &dest);

	dest = scale(treeTexture7_4, tree_screenCoords7_4.x, tree_screenCoords7_4.y, 1.0f); //bush
	SDL_RenderCopy(renderer, treeTexture7_4, nullptr, &dest);

	//block
	/*dest = scale(blockTexture0, block_screenCoords0.x, block_screenCoords0.y, 0.5f);
	SDL_RenderCopy(renderer, blockTexture0, nullptr, &dest);

	dest = scale(blockTexture1, block_screenCoords1.x, block_screenCoords1.y, 0.5f);
	SDL_RenderCopy(renderer, blockTexture1, nullptr, &dest);*/

	// render the player
	//game->RenderPlayer(0.10f);

	SDL_RenderPresent(renderer);
}

void Scene4::HandleEvents(const SDL_Event& event)
{
	// send events to player as needed
	game->getPlayer()->HandleEvents(event);
}